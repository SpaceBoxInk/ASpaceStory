/*
 * AppFrame.hpp
 *
 *  Created on: 15 déc. 2017
 *      Author: lordofkawaiii
 */

#include "Caneva.hpp"

struct AppFrame : public wxFrame
{
  AppFrame(wxString const & title, wxPoint const & pos, wxSize const & size,
           int tailleTexture);
  Canvas* getCaneva();
  unique_ptr<wxPanel> _panel;
  unique_ptr<Canvas> _canvas;
};
