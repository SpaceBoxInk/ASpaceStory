/*
 * AppFrame.cpp
 *
 *  Created on: 15 déc. 2017
 *      Author: lordofkawaiii
 */

#include "AppFrame.hpp"

AppFrame::AppFrame(wxString const & title, wxPoint const & pos, wxSize const & size, int tailleTexture) :
wxFrame(NULL, wxID_ANY, title, pos, size),
_panel(new wxPanel(this)),
_canvas(
    new Canvas(
        _panel.get(),
        wxID_ANY,
        wxPoint(-1, -1),
                   wxSize(16 * tailleTexture, 8 * tailleTexture)))
{

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

Canvas* AppFrame::getCaneva()
{
  return this->_canvas.get();
}
