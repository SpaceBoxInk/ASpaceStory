/**
 * @file LuaInterpreter.cpp
 *
 * Early optimization is the root of all evil
 *
 *  @date 22 nov. 2017
 *  @author FederAndInk
 *  @brief TODO complete
 */


#include "../../editor/model/MLuaInterpreter.hpp"

#include "../../editor/model/MParameters.hpp"
#include "../../editor/tools/utils.hpp"

#include <iostream>

extern "C"
{
#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>
}

using namespace AssEditor;
//------------------------------------------------------------
//========================>Constants<=========================
//------------------------------------------------------------
std::stringstream MLuaInterpreter::output;

int MLuaInterpreter::avancer(lua_State* l)
{
  output << "Avance d'une case" << '\n';
  return 0;
}

int MLuaInterpreter::avancerDe(lua_State* l)
{
  int n = lua_tonumber(l, 1);
  output << "Avance de " << n << " case" << '\n';
  return 0;
}

int MLuaInterpreter::tournerDe(lua_State* l)
{
  int direction = lua_tonumber(l, 1);
  output << "Tourne de " << direction << " degrés" << '\n';
  return 0;
}

int MLuaInterpreter::print(lua_State* l)
{
  for (int i = 1; i <= lua_gettop(l); ++i)
  {
    output << lua_tostring(l, i);
  }
  output << "\n";
  return 0;
}

//------------------------------------------------------------
//=======================>Constructors<=======================
//------------------------------------------------------------

MLuaInterpreter::MLuaInterpreter()
{
  lua = luaL_newstate();
  luaL_openlibs(lua);
  registerFonctions();
}

MLuaInterpreter::~MLuaInterpreter()
{
  lua_close(lua);
}

//------------------------------------------------------------
//=========================>Methods<==========================
//------------------------------------------------------------
void MLuaInterpreter::execute(std::string const& exePath)
{
  luaL_dofile(lua, exePath.c_str());
}

void MLuaInterpreter::registerFonctions()
{
  if (MParameters::getLang() == "En")
  {
    lua_register(lua, "moveForward", MLuaInterpreter::avancer);
    lua_register(lua, "moveForwardBy", MLuaInterpreter::avancerDe);
    lua_register(lua, "print", MLuaInterpreter::print);
    lua_register(lua, "turn", MLuaInterpreter::tournerDe);
  }
  else
  {
    lua_register(lua, "avancer", MLuaInterpreter::avancer);
    lua_register(lua, "avancerDe", MLuaInterpreter::avancerDe);
    lua_register(lua, "ecrire", MLuaInterpreter::print);
    lua_register(lua, "tournerDe", MLuaInterpreter::tournerDe);
  }
}

//------------------------------------------------------------
//=====================>Getters&Setters<======================
//------------------------------------------------------------
void MLuaInterpreter::clearOutput()
{
  output.str(std::string());
}

std::stringstream const& MLuaInterpreter::getOutput() const
{
//  lua_Debug dbg;
//
//  lua_getinfo(lua, ">Sn", &dbg);
//  if (dbg.what)
//  {
//    printLog(dbg.what, LogType::WARNING);
//  }
//  std::cout << output.str();
  return output;
}
