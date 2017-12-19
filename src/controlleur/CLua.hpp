/**
 * @file CLua.hpp
 *
 * Early optimization is the root of all evil
 * DRY ! Don't repeat yourself
 *
 *  @date 9 déc. 2017
 *  @author FederAndInk
 *  @brief TODO complete
 */

#pragma once

#include <exception>
#include <cxxabi.h>
#include <luaconf.h>
#include <any>
#include <iostream>
#include <typeinfo>

class CJeu;
class MTuile;

extern "C"
{
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

using lua_String = char const*;
using lua_Boolean = bool;

class CLua
{
//========================>Attributes<========================
private:
  static lua_State* lua;
  static CJeu* cJeu;
//=======================>Constructors<=======================
public:
  CLua(CJeu* cJeu);
  // TODO: rule of five ? copyandswap
  virtual ~CLua();

private:

//=========================>Methods<==========================
public:
  void executeScript(std::string script);

private:
  static int loadCouche(lua_State* l);
  static int setScriptPath(lua_State* l);
  static int getScriptPath(lua_State* l);

  static int addActionDeclenchement(lua_State* l);
  static int addActionPassage(lua_State* l);

  static int newEntity(lua_State* l);
  static int addActionDefense(lua_State* l);
  template<class T>
  static int setPosition(lua_State* l);
  template<class T>
  static int setTaille(lua_State* l);

  static int getCurrentPerso(lua_State* l);

//==================Register functions========================
  void registerBaseFunctions();
  void registerTerrainFunctions();
  void registerEntiteFunctions();
//======================Lua/ASS function helper===================
  static MTuile* getTuile(int index);
//======================Lua function helper===================
  static void push(lua_Number n);
  static void push(lua_Integer n);
  static void push(int n);
  static void push(lua_String str);
  static void push(lua_CFunction f);
  static void push(lua_Boolean b);
  static int getTop();
  static void testArgs(int nbExcpected);

  template<class T>
  T getTableData(lua_State* l, char const* key, int paramNb = 1);
//=====================>Getters&Setters<======================
public:

private:

};

//------------------------------------------------------------
//=====================>Implementations<======================
//------------------------------------------------------------
template<class T>
T CLua::getTableData(lua_State* l, char const* key, int paramNb)
{
// TODO : verifier que si la pile n'est pas vide ca fonctionne toujours
  lua_getfield(l, paramNb, key);
  std::any any;
  switch (lua_type(l, -1)) {
  case LUA_TBOOLEAN:
    any = lua_toboolean(l, -1);
    break;
  case LUA_TNIL:
    any = nullptr;
    break;
  case LUA_TSTRING:
    any = lua_tostring(l, -1);
    break;
  case LUA_TNUMBER:
    if (typeid(T) == typeid(LUA_INTEGER))
    {
      any = lua_tointeger(l, -1);
    }
    else
    {
      any = lua_tonumber(l, -1);
    }
    break;
  case LUA_TFUNCTION:
    any = lua_tocfunction(l, -1);
    break;
  case LUA_TTHREAD:
    any = lua_tothread(l, -1);
    break;
  case LUA_TLIGHTUSERDATA:
    any = lua_touserdata(l, -1);
    break;
  case LUA_TUSERDATA:
    any = lua_touserdata(l, -1);
    break;
  }
  lua_pop(l, 1);
  try
  {
    return std::any_cast<T>(any);
  }
  catch (std::exception& e)
  {
    int status = -4;
    auto anyType = abi::__cxa_demangle(any.type().name(), nullptr, nullptr, &status);
    auto wrongType = abi::__cxa_demangle(typeid(T).name(), nullptr, nullptr, &status);
    std::cerr << "Type is : " << anyType << " not " << wrongType << '\n';
    std::cerr << "Or " << key << " does not exist in table " << '\n';
    return 0;
  }
}
