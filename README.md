# ASpaceStory
The game

## Compilation
It uses c++17, so compile with g++ --std=c++1z or with clang5 with this same flag\
It also depends on [Lua](http://www.lua.org/home.html), [sfml](https://www.sfml-dev.org/) and [wxWidget](http://wxwidgets.org/)

## Compilation libs
you can use these commands :
<pre>
\`wx-config --libs\` \`pkg-config X11 --libs\` \`pkg-config X11 --libs\` \`pkg-config sfml-all --libs\`

and for gtk :
\`pkg-config gtk+-3.0 --libs\`

under Linux it may be :

X11
gtk-3
gdk-3
wx_baseu-3.0
wx_baseu_net-3.0
wx_gtk3u_core-3.0
wx_gtk3u_core-3.0
wx_gtk3u_adv-3.0
wx_gtk3u_qa-3.0
wx_gtk3u_html-3.0
wx_gtk3u_webview-3.0
wx_gtk3u_xrc-3.0
pangocairo-1.0
pango-1.0
sfml-graphics
sfml-window
sfml-audio
sfml-network
sfml-system
atk-1.0
cairo-gobject
cairo
gdk_pixbuf-2.0
gio-2.0
gobject-2.0
glib-2.0
lua
</pre>

## Compilation flags
use the same commands with --cflags :
<pre>
-I :
/usr/include/wx-3.0
/usr/include/gtk-3.0
/usr/include/at-spi2-atk/2.0
/usr/include/at-spi-2.0
/usr/include/dbus-1.0
/usr/lib/dbus-1.0/include
/usr/include/gtk-3.0
/usr/include/gio-unix-2.0/
/usr/include/cairo
/usr/include/pango-1.0
/usr/include/atk-1.0
/usr/include/cairo
/usr/include/pixman-1
/usr/include/freetype2
/usr/include/libpng16
/usr/include/harfbuzz
/usr/include/glib-2.0
/usr/lib/glib-2.0/include
/usr/include/freetype2
/usr/include/harfbuzz
/usr/include/libpng16
/usr/include/gdk-pixbuf-2.0
/usr/include/glib-2.0
/usr/lib/glib-2.0/include
/usr/lib/wx/include/gtk3-unicode-3.0
</pre>

-D :
<pre>
WXUSINGDLL
\_\_WXGTK__
FILE_OFFSET_BITS=64

-pthread
</pre>
