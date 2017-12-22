/*
 * App.cpp
 *
 *  Created on: 15 déc. 2017
 *      Author: lordofkawaiii
 */

#include "App.hpp"
#include "CJeu.hpp"

#include "../model/MParameters.hpp"
#include "../vue/AppFrame.hpp"

IMPLEMENT_APP(App);
bool App::OnInit()
{
  MParameters::load(argv[0].ToStdString());
  new CJeu();
  return true;
};
