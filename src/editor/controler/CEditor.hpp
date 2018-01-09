/**
 * CMethods.hpp
 *
 * Early optimization is the root of all evil
 *
 *  Created on: 5 nov. 2017
 *      Author: nihil
 */

#pragma once

#include "../../outils/ObserverPattern/Observer.hpp"
#include "../model/MLuaInterpreter.hpp"
#include "../model/MMethodsLoader.hpp"
#include "../model/MSave.hpp"

#include <wx/textctrl.h>
#include <future>
#include <set>
#include <string>
#include <vector>

class MTerrain;

class Editor;

enum class Event
{
  METHOD_INPUT,
  SAVE_AND_CLOSE_EDITOR,
  EXECUTE_EDITOR,
  SYNTAX,
  ABORT,
};

class CEditor : public Observer
{
//========================>Attributes<========================
private:
  static wxColour keywordColor;

  MMethodsLoader methodsLoader;
  std::set<std::string> listeKey;
  MSave save;
  Editor* ihmEditor;
  MLuaInterpreter luaInterpreter;
//=======================>Constructors<=======================
public:
  CEditor(MTerrain* terrain);
  // TODO: rule of five ? copyandswap
  virtual ~CEditor();

private:

//=========================>Methods<==========================
public:
  void setProgramName(std::string programName, MRobot* robot);
  void loadMethods(std::string method);
  void showEditor(bool show = true);

  void saveProgram();
private:
  void addEvents();

  void writeColoredMet(std::string const& method);
  void writeColoredMot(std::string const& mot);
  wxTextCoord formatMethod(std::string& method, std::vector<wxTextCoord> & wordRepCoord);
//=====================>Getters&Setters<======================
public:

private:

};
