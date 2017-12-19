/*
 * App.cpp
 *
 *  Created on: 15 déc. 2017
 *      Author: lordofkawaiii
 */

#include "App.hpp"
IMPLEMENT_APP(App);
bool App::OnInit()
{
  AppFrame *frame = new AppFrame("Hello World", wxPoint(50, 50), wxSize(512, 340), 32);
  frame->Show(true);
  return true;
};
