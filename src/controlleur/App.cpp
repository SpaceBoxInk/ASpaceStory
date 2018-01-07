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
#include <exception>
#include <wx/string.h>

IMPLEMENT_APP(App);
/**
 * Main load parameters and launch the game
 * @return true if initialization is well passed
 */
bool App::OnInit()
{
  MParameters::load(argv[0].ToStdString());
  AssEditor::MParameters::load(argv[0].ToStdString());
  try
  {
    new CJeu();
  }
  catch (MAssException& e)
  {
    std::cerr << e.what();
  }
  catch (std::exception& e)
  {
    std::cerr << e.what();
  }
  return true;
};
