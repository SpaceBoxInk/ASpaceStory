/**
 * @file CLua.cpp
 *
 * Early optimization is the root of all evil
 * DRY ! Don't repeat yourself
 *
 *  @date 9 déc. 2017
 *  @author FederAndInk
 *  @brief TODO complete
 */

#include "CLua.hpp"
#include "CJeu.hpp"
#include "CNiveau.hpp"

#include "../model/MAssException.hpp"
#include "../model/MPartieCouche.hpp"
#include "../model/MTerrain.hpp"

#include <string>

//------------------------------------------------------------
//========================>static members<=========================
//------------------------------------------------------------
lua_State* CLua::lua = luaL_newstate();
//------------------------------------------------------------
CJeu* CLua::cJeu;
//=======================>Constructors<=======================
//------------------------------------------------------------

CLua::CLua(CJeu* cJeu)
{
  CLua::cJeu = cJeu;
  luaL_openlibs(lua);

  registerBaseFunctions();
  registerTerrainFunctions();
}

CLua::~CLua()
{
  lua_close(lua);
}

//------------------------------------------------------------
//=========================>Methods<==========================
//------------------------------------------------------------
/**
 * lua function signature :
 * void loadCouche(string coucheFile, int couche);
 *
 * @param l lua interpreter
 * @return number of returns
 */
int CLua::loadCouche(lua_State* l)
{
  testArgs(2);
  std::string coucheFile = lua_tostring(l, 1);
  MTypeCouche couche = (MTypeCouche)lua_tointeger(l, 2);

  coucheFile = cJeu->cNiveau.getLevelFolder() + coucheFile;
  try
  {
    cJeu->cNiveau.getTerrain().loadCouche(coucheFile, couche);
  }
  catch (MAssException& e)
  {
    std::cerr << e.what();
  }
  return 0;
}

int CLua::setScriptFolder(lua_State* l)
{
  testArgs(1);
  cJeu->cNiveau.setScriptFolder(lua_tostring(l, 1));

  return 0;
}

int CLua::addActionDeclenchement(lua_State* l)
{
  testArgs(4);
  int x = lua_tointeger(l, 1);
  int y = lua_tointeger(l, 2);
  MTypeCouche couche = (MTypeCouche)lua_tointeger(l, 3);

  if (lua_isfunction(l, -1))
  {
    // store function
    int curIndex = luaL_ref(l, LUA_REGISTRYINDEX);

    cJeu->cNiveau.getTerrain()(x, y).getPartieCouche(couche)->setActionDeclenchement(
        [curIndex, l](std::string entite)
        {
          // get function previously stored in special lua table registry
          lua_rawgeti(l, LUA_REGISTRYINDEX, curIndex);
          if (lua_isfunction(l, -1))
          {
            push(entite.c_str());
            // call function defined by lua
            lua_call(l, 1, 0);
          }
        });

  }
  return 0;
}

int CLua::addActionPassage(lua_State* l)
{
  testArgs(4);
  int x = lua_tointeger(l, 1);
  int y = lua_tointeger(l, 2);
  MTypeCouche couche = (MTypeCouche)lua_tointeger(l, 3);

  if (lua_isfunction(l, -1))
  {
    // store function
    int curIndex = luaL_ref(l, LUA_REGISTRYINDEX);

    cJeu->cNiveau.getTerrain()(x, y).getPartieCouche(couche)->setActionPassage(
        [curIndex, l](std::string entite)
        {
          // get function previously stored in special lua table registry
          lua_rawgeti(l, LUA_REGISTRYINDEX, curIndex);
          if (lua_isfunction(l, -1))
          {
            // pass entity name on 1st parameter
            push(entite.c_str());
            // call function defined by lua
            lua_call(l, 1, 0);
          }
        });

  }
  return 0;
}

void CLua::registerBaseFunctions()
{
  lua_register(lua, "setScriptFolder", setScriptFolder);
}

void CLua::registerTerrainFunctions()
{
  lua_register(lua, "loadCouche", loadCouche);
  lua_register(lua, "addActionDeclenchement", addActionDeclenchement);
  lua_register(lua, "addActionPassage", addActionPassage);
}

void CLua::executeScript(std::string script)
{
  luaL_dofile(lua, script.c_str());
}

////////////////////////////////////////////////////////////////////////////////
//-///////////////////////////Lua function Helpers///////////////////////////-//
////////////////////////////////////////////////////////////////////////////////
void CLua::push(lua_Boolean b)
{
  lua_pushboolean(lua, b);
}

void CLua::push(lua_CFunction f)
{
  lua_pushcfunction(lua, f);
}

void CLua::push(lua_String str)
{
  lua_pushstring(lua, str);
}

void CLua::push(lua_Number n)
{
  lua_pushnumber(lua, n);
}

void CLua::testArgs(int nbExcpected)
{
  try
  {
    if (lua_gettop(lua) != nbExcpected)
    {
      throw MExceptionLuaArguments("Expect 4 arguments for addActionDeclenchement",
                                   lua_gettop(lua));
    }
  }
  catch (MAssException& e)
  {
    std::cerr << e.what();
    throw;
  }

}
////////////////////////////////////////////////////////////////////////////////

//------------------------------------------------------------
//=====================>Getters&Setters<======================
//------------------------------------------------------------

