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
#include <any>
#include <iostream>
#include <string>
#include <typeinfo>

class MEntite;
class MItem;
class CJeu;
class MTuile;

extern "C"
{
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}
/**
 * to define a lua string
 */
using lua_String = char const*;
/**
 * to define a lua bool
 */
using lua_Boolean = bool;

/**
 * interpreteur lua pour créer et gerer les niveaux
 */
class CLua
{
//========================>Attributes<========================
private:
  /**
   * l'interpreteur lua
   *
   * @see [le manuel lua](http://www.lua.org/manual/5.3/)
   * @see [la pile lua](http://www.lua.org/manual/5.3/manual.html#4.1)
   * @see [detail de la pile](http://gamerboom.com/wp-content/uploads/2012/02/lua-Stack-1-from-altdevblogaday.com_.png)
   */
  static lua_State* lua;
  /**
   * pointeur vers la "racine" du jeu\n
   * utilisé pour les fonctions appelées depuis le lua (eg: pour faire les niveaux)
   */
  static CJeu* cJeu;
  static MItem* item;

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
  static int getResourcesPath(lua_State* l);
  static int loadfile(lua_State* l);

  static int addActionDeclenchement(lua_State* l);
  static int addActionPassage(lua_State* l);

  static int addActionMining(lua_State* l);

  static int newEntity(lua_State* l);
  static int addActionDefense(lua_State* l);

  static MEntite* getEntite(std::string& entiteName, int nbArgsNoEntity);
  static int setPosition(lua_State* l);
  static int setTaille(lua_State* l);
  static int setTexture(lua_State* l);

  static int getCurrentPerso(lua_State* l);

  static int newRobot(lua_State* l);

  //==================Register functions========================
  static int newItem(lua_State* l);

  static int giveNewItemToPerso(lua_State* l);
  static int giveNewItemToEntity(lua_State* l);
  static int putNewItemOn(lua_State* l);

  static int addActionUtilisation(lua_State* l);

  static int newEnigme(lua_State* l);
  static int afficherEnigme(lua_State* l);



//==================Register functions========================
  void registerBaseFunctions();
  void registerTerrainFunctions();
  void registerEntiteFunctions();
  void registerItemFunctions();
  void registerEnigmeFunctions();
//======================Lua/ASS function helper===================
  static MTuile* getTuile(int index);
  static MItem* getItem();
//======================Lua function helper===================
  static void push(lua_Number n);
  static void push(lua_Integer n);
  static void push(lua_Unsigned n);
  static void push(int n);
  static void push(lua_String str);
  static void push(lua_CFunction f);
  static void push(lua_Boolean b);
  static int getTop();
  static int storeFunction();
  static void pushFunctionFrom(int index);
  static void testArgs(int nbExcpected);
  static std::string getCurFunction();

  template<class T>
  T getTableData(lua_State* l, char const* key, int paramNb = 1);
//=====================>Getters&Setters<======================
public:

private:

};

//------------------------------------------------------------
//=====================>Implementations<======================
//------------------------------------------------------------
/**
 *
 * @param l l'interpreteur lua
 * @param key la clé que l'on veut récupérer (like : map["key"])
 * @param paramNb là où se trouve la table (map) dans la pile lua
 * @return
 */
template<class T>
T CLua::getTableData(lua_State* l, char const* key, int paramNb)
{
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
