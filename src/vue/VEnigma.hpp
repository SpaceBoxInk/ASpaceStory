/*
 * inventory.hpp
 *
 *  Created on: 22 déc. 2017
 *      Author: lordofkawaiii
 */
#pragma once
#include <wx/wx.h>
#include <wx/log.h>
#include "ImagePanel.hpp"

class VEnigma : public wxFrame
{
//========================>Attributes<========================
private:
  wxImagePanel* picture;
  wxTextCtrl* text;
//=======================>Constructors<=======================
public:
  VEnigma(wxString const & title, wxString file, std::string text);
  // TODO: rule of five ? copyandswap
  virtual ~VEnigma();

private:

//=========================>Methods<==========================
public:
  void onFocus(wxFocusEvent& event);
  void onQuit(wxCommandEvent & WXUNUSED(event));
private:

//=====================>Getters&Setters<======================
public:

private:

};
