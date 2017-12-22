/*
 * AppFrame.hpp
 *
 *  Created on: 15 déc. 2017
 *      Author: lordofkawaiii
 */

#pragma once
#include "AppFrameInterface.hpp"
#include "Caneva.hpp"



struct AppFrame : public AppFrameInterface, public wxFrame
{
public:
  AppFrame(wxString const & title, wxPoint const & pos, wxSize const & size,
           int tailleTexture);

  void loadFileIntoGround(int const* idList, std::string texture, MTypeCouche level,
                          int tailleTexture) override;
  void addEntite(std::string name, std::string file) override;
private:
  Canvas* getCaneva();

  void onResize(wxSizeEvent& event);

  wxPanel* getPanel();

//  wxPanel* _panel; // FIXME il sert à quoi ?
  Canvas* _canvas;
  wxPanel* _panel2;
};

//inline wxPanel* AppFrame::getPanel()
//{
//  return _panel;
//}
