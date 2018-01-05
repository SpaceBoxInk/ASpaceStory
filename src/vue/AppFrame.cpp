/*
 * AppFrame.cpp
 *
 *  Created on: 15 déc. 2017
 *      Author: lordofkawaiii
 */

#include "AppFrame.hpp"
#include "../model/MParameters.hpp"
#include "../editor/tools/utils.hpp"
#include "../model/MEvents.hpp"
#include "VEnigma.hpp"

#include <sstream>


AppFrame::AppFrame(wxString const & title, wxPoint const & pos, wxSize const & size,
                   int tailleTexture) :
    wxFrame(NULL, wxID_ANY, title, pos, size),

    _canvas(
        new Canvas(
            this,
            wxNewId(),
            wxPoint(-1, -1),
            wxSize(MParameters::getNbTuileX() * tailleTexture,
                   MParameters::getNbTuileY() * tailleTexture))),
    _panel2(new wxPanel(this, wxID_ANY, wxPoint(-1, -1), wxSize(-1, -1)))
{
  this->SetMinSize(size);

//  getCaneva()->Connect(getCaneva()->GetId(), wxEVT_SIZE,
//                       wxSizeEventHandler(Canvas::onResize),
//                       getCaneva());

  wxBoxSizer* hbox = new wxBoxSizer(wxVERTICAL);
  wxBoxSizer* hbox2 = new wxBoxSizer(wxHORIZONTAL);

  hbox->Add(_canvas, 9, wxEXPAND);
  hbox->Add(_panel2, 1, wxEXPAND);
  hbox2->Add(new wxButton(_panel2, wxID_ADD, wxT("Sert a rien"), wxPoint(-1, -1)), 1,
             wxEXPAND);
  this->SetSizer(hbox);
//  Connect(this->GetId(), wxEVT_CHAR_HOOK, wxKeyEventHandler(AppFrame::onKey));
  this->Bind(wxEVT_CHAR_HOOK, &AppFrame::onKey, this);

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
  std::cout << "resize" << std::endl;
}

void AppFrame::onKey(wxKeyEvent& event)
{
  wxChar uc = event.GetUnicodeKey();
  if (uc != WXK_NONE)
  {
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

void AppFrame::move(std::string entityName, MCoordonnees const& offset)
{
  _canvas->move(entityName, offset);
}

void AppFrame::setPositionOf(std::string entityName, MCoordonnees const& position)
{
  _canvas->setPositionOf(entityName, position);
}

void AppFrame::showEnigma(std::string title, std::string file, std::string textInside)
{
  VEnigma *custom = new VEnigma(title, file, textInside);
  custom->Show(true);
}

AppFrame::~AppFrame()
{
//  delete _canvas;
//  delete _panel2;
}
