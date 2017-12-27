/*
 * inventory.hpp
 *
 *  Created on: 22 déc. 2017
 *      Author: lordofkawaiii
 */
#pragma once
#include <wx/wx.h>
#include <wx/log.h>
#include "VInventaireInterface.hpp"
#include "ImagePanel.hpp"

class inventory : public wxFrame, public VInventaireInterface
{
//========================>Attributes<========================
private:
  wxImagePanel* picture;
  wxTextCtrl* text;
//=======================>Constructors<=======================
public:
  inventory(wxString const & title, wxString file, std::string text);
  // TODO: rule of five ? copyandswap
  virtual ~inventory();

private:

//=========================>Methods<==========================
public:
  void onFocus(wxFocusEvent& event);
  void OnQuit(wxCommandEvent & WXUNUSED(event));
private:

//=====================>Getters&Setters<======================
public:

private:

};
