/*
 * AppFrame.hpp
 *
 *  Created on: 15 déc. 2017
 *      Author: lordofkawaiii
 */

#pragma once
#include "AppFrameInterface.hpp"
#include "Caneva.hpp"


/**
 * La racine de la vue (application)
 */
struct AppFrame : public AppFrameInterface, public wxFrame
{
public:
  AppFrame(wxString const & title, wxPoint const & pos, wxSize const & size,
           int tailleTexture,
           MCoordonnees taille = MCoordonnees(10, 8));

  virtual ~AppFrame();

  void loadFileIntoGround(int const* idList, std::string texture, MTypeCouche level,
                          int tailleTexture) override;


  void addEntite(std::string name, std::string file) override;

  void move(std::string entityName, MCoordonnees const& offset) override;
  void setPositionOf(std::string entityName, MCoordonnees const& offset) override;
private:
  Canvas* getCaneva();
  void onFocus(wxFocusEvent& event);

  void onKey(wxKeyEvent& event);
  void onCursor(wxMouseEvent& event);
  void onResize(wxSizeEvent& event);
public:
  void showEnigma(std::string title, std::string file, std::string textInside);
  void showDialog(std::string title, std::string file, std::string textInside);
  wxPanel* getPanel();
private:
  Canvas* _canvas;
  wxPanel* _panel2;
  MCoordonnees tailleInventory;
public:
  wxTextCtrl* cursorloc;
};

//inline wxPanel* AppFrame::getPanel()
//{
//  return _panel;
//}
