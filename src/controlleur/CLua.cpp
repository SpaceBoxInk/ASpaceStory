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
CJeu* CLua::cJeu;
//------------------------------------------------------------
//=======================>Constructors<=======================
//------------------------------------------------------------

CLua::CLua(CJeu* cJeu)
{
  CLua::cJeu = cJeu;
  luaL_openlibs(lua);

  registerBaseFunctions();
  registerTerrainFunctions();
  registerEntiteFunctions();
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
  cJeu->cNiveau.setScriptFolder(lua_tostring(l, 1));

  return 0;
}

/**
 * setPosition(string entiteName, int x, int y)
 */
int CLua::setPosition(lua_State* l)
{
  // FIXME : testNbArgs
  std::string entiteName = lua_tostring(l, 1);
  int x = lua_tonumber(l, 2);
  int y = lua_tonumber(l, 3);

  MEntite* e = cJeu->getEntite(entiteName);
  if (e)
  {
    e->setTuile(&(cJeu->cNiveau.getTerrain()(x, y)));
  }
  else
  {
    throw MExceptionEntiteInexistante(entiteName);
  }
  return 0;
}

/**
 * setTaille(string entiteName, int taille)
 */
int CLua::setTaille(lua_State* l)
{
  // FIXME : testNbArgs
  std::string entiteName = lua_tostring(l, 1);
  float taille = lua_tonumber(l, 2);

  MEntite* e = cJeu->getEntite(entiteName);
  if (e)
  {
    e->setTaille(taille);
  }
  return 0;
}

int CLua::getCurrentPerso(lua_State* l)
{
  lua_pushstring(l, cJeu->cPersonnage.getCurrentPerso()->getNom().c_str());
  return 1;
}

void CLua::registerBaseFunctions()
{
  lua_register(lua, "setScriptFolder", setScriptFolder);
}

void CLua::registerTerrainFunctions()
{
  lua_register(lua, "loadCouche", loadCouche);
}

void CLua::registerEntiteFunctions()
{
  lua_register(lua, "setTaille", setTaille);
  lua_register(lua, "setPosition", setPosition);
  lua_register(lua, "getCurrentPerso", getCurrentPerso);
}

void CLua::executeScript(std::string script)
{
  luaL_dofile(lua, script.c_str());
}

////////////////////////////////////////////////////////////////////////////////
//-///////////////////////////Lua function Helpers///////////////////////////-//
////////////////////////////////////////////////////////////////////////////////
void CLua::push(lua_State* l, lua_Boolean b)
{
  lua_pushboolean(l, b);
}

void CLua::push(lua_State* l, lua_CFunction f)
{
  lua_pushcfunction(l, f);
}

void CLua::push(lua_State* l, lua_String str)
{
  lua_pushstring(l, str);
}

void CLua::push(lua_State* l, lua_Number n)
{
  lua_pushnumber(l, n);
}

////////////////////////////////////////////////////////////////////////////////

//------------------------------------------------------------
//=====================>Getters&Setters<======================
//------------------------------------------------------------

