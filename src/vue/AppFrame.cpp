/*
 * AppFrame.cpp
 *
 *  Created on: 15 déc. 2017
 *      Author: lordofkawaiii
 */

#include "AppFrame.hpp"
#include "../model/MParameters.hpp"
#include "VEnigma.hpp"

AppFrame::AppFrame(wxString const & title, wxPoint const & pos, wxSize const & size, int tailleTexture) :
    wxFrame(NULL, wxID_ANY, title, pos, size),

    _canvas(
        new Canvas(this, wxNewId(), wxPoint(-1, -1),
            wxSize(MParameters::getNbTuileX() * tailleTexture,
                   MParameters::getNbTuileY() * tailleTexture))),
    _panel2(
        new wxPanel(this, wxID_ANY
                    , wxPoint(-1, -1), wxSize(-1, -1)
        ))
{
  this->SetMinSize(size);

//  getCaneva()->Connect(getCaneva()->GetId(), wxEVT_SIZE,
//                       wxSizeEventHandler(Canvas::onResize),
//                       getCaneva());

  wxBoxSizer* hbox = new wxBoxSizer(wxVERTICAL);
  wxBoxSizer* hbox2 = new wxBoxSizer(wxHORIZONTAL);


  hbox->Add(_canvas, 9, wxEXPAND);
  hbox->Add(_panel2, 1, wxEXPAND);
  hbox2->Add(new wxButton(_panel2, wxID_ADD, wxT("sert a rien"), wxPoint(-1, -1)), 1,
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
    // It's a "normal" character. Notice that this includes
    // control characters in 1..31 range, e.g. WXK_RETURN or
    // WXK_BACK, so check for them explicitly.
    if (uc >= 32)
    {
      wxLogMessage
      ("You pressed '%c'", uc);
    }
    else
    {
      // It's a control character
      wxLogMessage
      ("MEH");
  }
}
else // No Unicode equivalent.
{
  // It's a special key, deal with all the known ones:
  switch (event.GetKeyCode()) {
  case WXK_LEFT:
  case WXK_RIGHT:
  break;
  case WXK_F1:
  break;
}
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
