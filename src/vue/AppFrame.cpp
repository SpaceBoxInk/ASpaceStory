/*
 * AppFrame.cpp
 *
 *  Created on: 15 déc. 2017
 *      Author: lordofkawaiii
 */

#include "AppFrame.hpp"

#include <wx/gtk/button.h>
#include <wx/chartype.h>
#include <wx/defs.h>
#include <wx/event.h>
#include <wx/gdicmn.h>
#include <wx/generic/panelg.h>
#include <wx/sizer.h>
#include <wx/gbsizer.h>
#include <wx/string.h>
#include <wx/utils.h>
#include <iostream>
#include <sstream>
#include <string>

#include "../editor/tools/utils.hpp"
#include "../model/MCoordonnees.hpp"
#include "../model/MEvents.hpp"
#include "../model/MParameters.hpp"
#include "../model/MPartieCouche.hpp"
#include "VEnigma.hpp"
#include "VPlayerInventory.hpp"

AppFrame::AppFrame(wxString const & title, wxPoint const & pos, wxSize const & size,
                   int tailleTexture, MCoordonnees taille) :
    wxFrame(NULL, wxNewId(), title, pos, size, wxMAXIMIZE | wxDEFAULT_FRAME_STYLE),

    _canvas(
        new Canvas(
            this,
            wxNewId(),
            wxPoint(-1, -1),
            wxSize(MParameters::getNbTuileX() * tailleTexture,
                   MParameters::getNbTuileY() * tailleTexture),
            tailleTexture)),
    _panel2(new wxPanel(this, wxID_ANY, wxPoint(-1, -1), wxSize(-1, -1))),
    tailleInventory(taille)
{
//  getCaneva()->Connect(getCaneva()->GetId(), wxEVT_SIZE,
//                       wxSizeEventHandler(Canvas::onResize),
//                       getCaneva());
  wxBoxSizer* hbox = new wxBoxSizer(wxVERTICAL);
  wxBoxSizer* hbox2 = new wxBoxSizer(wxHORIZONTAL);
  wxPanel* middlePanel = new wxPanel(_panel2, wxNewId(), wxPoint(-1, -1));
  wxPanel* dialogPanel = new wxPanel(_panel2, wxNewId(), wxPoint(-1, -1));
  wxBoxSizer* middleSizer = new wxBoxSizer(wxVERTICAL);
  wxBoxSizer* dialogueSizer = new wxBoxSizer(wxHORIZONTAL);
  persoDireImage = new wxImagePanelP(dialogPanel,
                                     MParameters::getRootPath() + "/pictures/nothing.png",
                                     wxBITMAP_TYPE_PNG);
  wxBoxSizer* direZoneSizer = new wxBoxSizer(wxVERTICAL);

//  VPlayerInventaireInterface* interF = new VPlayerInventory(taille);

//  middleSizer->Add(new wxGauge(middlePanel, wxNewId(), 100, wxPoint(-1, -1), wxSize(-1, -1)),
//                   3, wxEXPAND);
//  middleSizer->Add(new wxGauge(middlePanel, wxNewId(), 100, wxPoint(-1, -1), wxSize(-1, -1)),
//                   3, wxEXPAND);
//  middleSizer->Add(new wxPanel(middlePanel, wxNewId(), wxPoint(-1, -1), wxSize(-1, -1)), 1,
//                   wxEXPAND);

  middlePanel->SetSizer(middleSizer);
  hbox->Add(_canvas, 1, wxEXPAND);
  hbox->Add(_panel2, 0, wxEXPAND);

  cursorloc = new wxTextCtrl(_panel2, wxNewId(), "", wxPoint(-1, -1), wxSize(-1, -1),
  wxTE_READONLY | wxTE_CENTER);
  dialogBox = new wxTextCtrl(dialogPanel, wxNewId(), "", wxPoint(-1, -1), wxSize(-1, 50),
  wxTE_READONLY | wxTE_MULTILINE);

  wxButton* okButton = new wxButton(dialogPanel, wxNewId(), "Suivant >");
  hbox2->Add(cursorloc, 2, wxEXPAND);
  hbox2->Add(middlePanel, 4, wxEXPAND);
  hbox2->Add(dialogPanel, 3, wxEXPAND);

  dialogueSizer->Add(persoDireImage, 1, wxEXPAND);
  dialogueSizer->Add(direZoneSizer, 5, wxEXPAND);
  direZoneSizer->Add(dialogBox, 5, wxEXPAND);
  direZoneSizer->Add(okButton, 4, wxEXPAND);
  dialogPanel->SetSizer(dialogueSizer);

  _panel2->SetSizer(hbox2);
  this->SetSizer(hbox);

//  Connect(this->GetId(), wxEVT_CHAR_HOOK, wxKeyEventHandler(AppFrame::onKey));
  this->Bind(wxEVT_CHAR_HOOK, &AppFrame::onKey, this);
  okButton->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AppFrame::onNext, this);

  // bind for close the game :)
  Bind(wxEVT_CLOSE_WINDOW, [this](wxCloseEvent)
  {
    // FIXME : change the exit with notifyObservers
       setChanged();
       notifyObservers(MUserEvents::EXIT);
       exit(0);
     });

  ////////////////////////////////////////////////////////////////////////////////
  // Probably due to some RTTI, IDE is getting confused by this dynamic call
  // and doesn't understand the correct Bind overload. Causes non sequitur errors
  // to display in the inspector. Suppress.
  //
  // Dynamic binding is cleanest here, since we don't want to hook up our resize
  // handler until our dependencies (Canvas namely) have finished their initialization
  ////////////////////////////////////////////////////////////////////////////////
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wint-conversion"
#pragma clang diagnostic pop
  ////////////////////////////////////////////////////////////////////////////////
}

void AppFrame::loadFileIntoGround(int const * idList, std::string texture, MTypeCouche level,
                                  int tailleTexture)
{
  getCaneva()->loadFileIntoGround(idList, texture, (int)level, tailleTexture);
}

void AppFrame::addEntite(std::string name, std::string file)
{
  getCaneva()->addEntite(name, file);
}

Canvas* AppFrame::getCaneva()
{
  return this->_canvas;
}

void AppFrame::onResize(wxSizeEvent& event)
{
}

void AppFrame::onKey(wxKeyEvent& event)
{
  wxChar uc = event.GetUnicodeKey();
  if (uc != WXK_NONE && waitNextParler.try_lock())
  {
    waitNextParler.unlock();
    setChanged();
    std::stringstream str;
    std::wstring ws;
    ws = uc;
    str << ws;
    printLog(str.str() + " pressed", LogType::INFO);
    notifyObservers(MUserEvents::KEY_PRESSED, str.str()[0]);
  }
}

void AppFrame::onFocus(wxFocusEvent& event)
{
}

wxPanel* AppFrame::getPanel()
{
  return this->_panel2;
}

void AppFrame::move(std::string entityName, MCoordonnees const& offset, Mouvement direction)
{
  _canvas->move(entityName, offset, direction);
}

void AppFrame::setPositionOf(std::string entityName, MCoordonnees const& position,
                             Mouvement direction)
{
  _canvas->setPositionOf(entityName, position, direction);
}

void AppFrame::showEnigma(std::string title, std::string file, std::string textInside)
{
  VEnigma *custom = new VEnigma(title, file, textInside);
  custom->Show(true);
}

AppFrame::~AppFrame()
{
  delete _canvas;
  delete _panel2;
}

void AppFrame::onNext(wxCommandEvent& event)
{
  effacerParler();
  waitNextParler.try_lock();
  waitNextParler.unlock();
//  notifyObservers(MUserEvents::NEXT_DIALOG);
}

void AppFrame::parler(std::string entityTexture, std::string parole)
{
  waitNextParler.try_lock();
  persoDireImage->LoadImage(entityTexture);
  persoDireImage->paintNow();
  Refresh();
  dialogBox->Clear();
  dialogBox->CallAfter([this, parole]
  {
    dialogBox->AppendText(wxString(parole.c_str(), wxConvUTF8));
  });
  waitNextParler.lock();
  waitNextParler.unlock();
}

void AppFrame::effacerParler()
{
  persoDireImage->LoadImage(MParameters::getRootPath() + "/pictures/nothing.png");
  persoDireImage->paintNow();
  Refresh();
  dialogBox->Clear();
  dialogBox->AppendText("");
}
