/*
 * AppFrame.cpp
 *
 *  Created on: 15 déc. 2017
 *      Author: lordofkawaiii
 */

#include "AppFrame.hpp"

AppFrame::AppFrame(wxString const & title, wxPoint const & pos, wxSize const & size, int tailleTexture) :
wxFrame(NULL, wxID_ANY, title, pos, size),

    _canvas(
        new Canvas(this, wxNewId(), wxPoint(-1, -1),
                   wxSize(16 * tailleTexture, 8 * tailleTexture))),
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

  hbox->Add(_canvas, 10, wxEXPAND);
  hbox->Add(_panel2, 1, wxEXPAND);
  this->SetSizer(hbox);

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
