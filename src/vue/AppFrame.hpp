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

  void onResize(wxSizeEvent& event);

  wxPanel* getPanel();

  wxPanel* _panel;
  Canvas* _canvas;
  wxPanel* _panel2;
};

inline wxPanel* AppFrame::getPanel()
{
  return _panel;
}
