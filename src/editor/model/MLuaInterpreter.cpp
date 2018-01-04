/**
 * @file LuaInterpreter.cpp
 *
 * Early optimization is the root of all evil
 *
 *  @date 22 nov. 2017
 *  @author FederAndInk
 *  @brief TODO complete
 */

#include "MLuaInterpreter.hpp"
#include "MParameters.hpp"

#include "../../model/MAssException.hpp"
#include "../../model/MCoordonnees.hpp"
#include "../../model/MRobot.hpp"
#include "../../model/MTerrain.hpp"
#include "../view/Editor.hpp"

#include <thread>
#include <typeinfo>

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
bool MLuaInterpreter::abort = false;
std::string MLuaInterpreter::output;

Editor* MLuaInterpreter::ihmEditor = nullptr;
MTerrain* MLuaInterpreter::terrain = nullptr;

MRobot* MLuaInterpreter::robot = nullptr;
using namespace std::chrono_literals;

template<class Type>
std::string& operator<<(std::string& ss, Type t)
{
  using namespace std;
  if constexpr(!std::is_arithmetic<Type>::value || sizeof(Type) == 1)
  {
    ss += t;
  }
  else
  {
    ss += std::to_string(t);
  }
  MLuaInterpreter::ihmEditor->writeRes(ss);
  ss = "";
  return ss;
}

int MLuaInterpreter::avancer(lua_State* l)
{
  std::this_thread::sleep_for(robot->getSpeed());
  output << "Avance d'une case" << '\n';
  Mouvement mouv = robot->getDirection();
  robot->deplacer(*terrain, mouv);
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
  std::this_thread::sleep_for(robot->getSpeed());
  int direction = lua_tonumber(l, 1);
  try
  {
    int newDir = (int(robot->getDirection()) + direction / 90) % 4;
    robot->setDirection(Mouvement(newDir >= 0 ? newDir : 4 - newDir));
    output << "Tourne de " << direction << " degrés" << '\n';
    if (direction != 0 && direction != 90 && direction != -90 && direction != 180)
    {
      output << "Attention, " << direction
          << " degrés n'est pas conventionnel, choisi plutôt parmi ceux la : \n0, 90, -90, 180\n";
    }
  }
  catch (MAssException& e)
  {
    output << e.what();
  }
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

MLuaInterpreter::MLuaInterpreter(MTerrain* terrain, Editor* ihmEditor)
{
  MLuaInterpreter::terrain = terrain;
  MLuaInterpreter::ihmEditor = ihmEditor;

  lua = luaL_newstate();
  luaL_openlibs(lua);
  registerFonctions();
  lua_sethook(lua, [](lua_State *L, lua_Debug *ar)
  {
    if (abort)
    {
      luaL_error(L, "");
    }
  },
              LUA_HOOKLINE, 0);
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
  robot->launch();
  abort = false;
  running.lock();
  luaL_dofile(lua, exePath.c_str());
  running.unlock();
  abort = false;
}

void MLuaInterpreter::interrupt()
{
  if (isRunning())
  {
    abort = true;
  }
  else
  {
    robot->reset();
  }
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
  output = "";
}

std::string const& MLuaInterpreter::getOutput() const
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
