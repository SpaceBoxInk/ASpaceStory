/*
 * wxSFMLCaneva.cpp
 *
 *  Created on: 15 déc. 2017
 *      Author: lordofkawaiii
 */

#include "wxSFMLCanevas.hpp"

wxSfmlCanvas::wxSfmlCanvas(wxWindow *parent, wxWindowID windowId,
    wxPoint const &position , wxSize const &size ,
                           long style) :
    wxControl(parent, windowId, position, size, style)
{
  createRenderWindow();
}
void wxSfmlCanvas::onUpdate()
{

}
void wxSfmlCanvas::onIdle(wxIdleEvent& event)
{

  // Send a paint message when control is idle, to ensure max framerate
  Refresh();
}
void wxSfmlCanvas::onPaint(wxPaintEvent& event)
{
  wxPaintDC dc(this);     // Prepare control to be repainted
  onUpdate();             // Tick update
  display();              // Draw
}
void wxSfmlCanvas::onEraseBackground(wxEraseEvent& event)
{

}
void wxSfmlCanvas::createRenderWindow()
{
#ifdef __WXGTK__
  gtk_widget_realize(m_wxwindow);
  gtk_widget_set_double_buffered(m_wxwindow, false);

  GdkWindow *gdkWindow = gtk_widget_get_window((GtkWidget*)GetHandle());
  XFlush(GDK_WINDOW_XDISPLAY(gdkWindow));

  sf::RenderWindow::create(GDK_WINDOW_XID(gdkWindow));
#else
  sf::RenderWindow::create(GetHandle());
#endif
}
void wxSfmlCanvas::setwxWindowSize(wxSize const & size)
{
  this->SetSize(size);
}
void wxSfmlCanvas::setRenderWindowSize(sf::Vector2u const & size)
{
  this->setSize(size);
}
wxSfmlCanvas::~wxSfmlCanvas()
{

}
wxBEGIN_EVENT_TABLE(wxSfmlCanvas, wxControl) EVT_IDLE(wxSfmlCanvas::onIdle)
EVT_PAINT(wxSfmlCanvas::onPaint)
EVT_ERASE_BACKGROUND(wxSfmlCanvas::onEraseBackground)
wxEND_EVENT_TABLE()
