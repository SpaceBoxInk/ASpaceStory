/*
 * ImagePanel.hpp
 *
 *  Created on: 27 déc. 2017
 *      Author: lordofkawaiii
 */
#pragma once

#include <wx/wx.h>
#include <wx/sizer.h>

class wxImagePanel : public wxPanel
{
  wxBitmap image;
  wxBitmap resized;
  int w, h;

public:
  wxImagePanel(wxFrame* parent, wxString file, wxBitmapType format);

  wxSize getPictureSize();
  void paintEvent(wxPaintEvent & evt);
  void paintNow();
  void OnSize(wxSizeEvent& event);
  void render(wxDC& dc);

  virtual void LoadImage(std::string file);

};





