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

#include <bits/exception.h>
#include <cxxabi.h>
#include <luaconf.h>
#include <any>
#include <iostream>
#include <typeinfo>

class CJeu;

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
  static int setScriptFolder(lua_State* l);

//==================Register functions========================
  void registerBaseFunctions();
  void registerTerrainFunctions();
//======================Lua function helper===================
  void push(lua_State* l, lua_Number n);
  void push(lua_State* l, lua_String str);
  void push(lua_State* l, lua_CFunction f);
  void push(lua_State* l, lua_Boolean b);

  template<typename ... Ts>
  void pushargs(lua_State *l, Ts ...args);

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
    return std::any_cast < T > (any);
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

template<typename ... Ts>
inline void CLua::pushargs(lua_State* l, Ts ... args)
{
//( push (l , args ) , ...);
}
