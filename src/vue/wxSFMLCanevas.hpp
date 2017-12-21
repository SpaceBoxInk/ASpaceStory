#include <iostream>
#include <wx/wx.h>
#include <memory>
#include <SFML/Graphics.hpp>

#ifdef __WXGTK__
#include <gdk/gdkx.h>
#include <gtk/gtk.h>
#endif

using namespace std;

static int const kDefaultWindowWidth = 1280;
static int const kDefaultWindowHeight = 720;
static int const kCanvasMargin = 50;

class wxSfmlCanvas : public wxControl, public sf::RenderWindow
{
public:
  wxSfmlCanvas(wxWindow *parent = nullptr, wxWindowID windowId = -1, wxPoint const &position =
                   wxDefaultPosition,
               wxSize const &size = wxDefaultSize, long style = 0);

  virtual void onUpdate();

wxDECLARE_EVENT_TABLE();
  void onIdle(wxIdleEvent& event);

  void onPaint(wxPaintEvent& event);


  // Explicitly overriding prevents wxWidgets from drawing, which could result in flicker
  void onEraseBackground(wxEraseEvent& event);

  void createRenderWindow();

  void setwxWindowSize(wxSize const & size);

  void setRenderWindowSize(sf::Vector2u const & size);

  virtual ~wxSfmlCanvas();

};

