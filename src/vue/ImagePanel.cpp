/*
 * ImagePanel.cpp
 *
 *  Created on: 27 déc. 2017
 *      Author: lordofkawaiii
 */

#include "ImagePanel.hpp"

wxImagePanel::wxImagePanel(wxFrame* parent, wxString file, wxBitmapType format) :
    wxPanel(parent)
{
  // load the file... ideally add a check to see if loading was successful
  image.LoadFile(file, format);
  assert(image.IsOk());
  this->Bind(wxEVT_PAINT, &wxImagePanel::paintEvent, this);
  this->Bind(wxEVT_SIZE, &wxImagePanel::OnSize, this);
  w = -1;
  h = -1;
}

/*
 * Called by the system of by wxWidgets when the panel needs
 * to be redrawn. You can also trigger this call by
 * calling Refresh()/Update().
 */

void wxImagePanel::paintEvent(wxPaintEvent & evt)
{
  // depending on your system you may need to look at double-buffered dcs
  wxPaintDC dc(this);
  render(dc);
}

/*
 * Alternatively, you can use a clientDC to paint on the panel
 * at any time. Using this generally does not free you from
 * catching paint events, since it is possible that e.g. the window
 * manager throws away your drawing when the window comes to the
 * background, and expects you will redraw it when the window comes
 * back (by sending a paint event).
 */
void wxImagePanel::paintNow()
{
  // depending on your system you may need to look at double-buffered dcs
  wxClientDC dc(this);
  render(dc);
}

/*
 * Here we do the actual rendering. I put it in a separate
 * method so that it can work no matter what type of DC
 * (e.g. wxPaintDC or wxClientDC) is used.
 */
void wxImagePanel::render(wxDC& dc)
{
  int neww, newh;
  dc.GetSize(&neww, &newh);

  if (neww != w || newh != h)
  {
    resized = wxBitmap(image.ConvertToImage().Scale(neww, newh /*, wxIMAGE_QUALITY_HIGH*/));
    w = neww;
    h = newh;
    dc.DrawBitmap(resized, 0, 0, false);
  }
  else
  {
    dc.DrawBitmap(resized, 0, 0, false);
  }
}

/*
 * Here we call refresh to tell the panel to draw itself again.
 * So when the user resizes the image panel the image should be resized too.
 */
void wxImagePanel::OnSize(wxSizeEvent& event)
{
  Refresh();
  //skip the event.
  event.Skip();
}

void wxImagePanel::LoadImage(std::string file)
{
  this->image.LoadFile(file, wxBITMAP_TYPE_PNG);
}
