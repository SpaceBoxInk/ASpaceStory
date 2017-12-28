/*
 * App.cpp
 *
 *  Created on: 15 déc. 2017
 *      Author: lordofkawaiii
 */

#include "App.hpp"
#include "CJeu.hpp"

#include "../editor/model/MParameters.hpp"
#include "../model/MParameters.hpp"

#include <wx/app.h>
#include <wx/string.h>

IMPLEMENT_APP(App);
bool App::OnInit()
{
  MParameters::load(argv[0].ToStdString());
  AssEditor::MParameters::load(argv[0].ToStdString());
  new CJeu();
  return true;
};
