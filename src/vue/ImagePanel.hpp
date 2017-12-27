/*
 * ImagePanel.hpp
 *
 *  Created on: 27 déc. 2017
 *      Author: lordofkawaiii
 */
#pragma once

#include <wx/wx.h>
#include <wx/sizer.h>

class inventory;

class wxImagePanel : public wxPanel
{
  wxBitmap image;

public:
  wxImagePanel(wxFrame* parent, wxString file, wxBitmapType format);

  void paintEvent(wxPaintEvent & evt);
  void paintNow();

  void render(wxDC& dc);

};





