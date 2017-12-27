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
  testArgs(2);
  std::string coucheFile = lua_tostring(l, 1);
  MTypeCouche couche = (MTypeCouche)lua_tointeger(l, 2);

  coucheFile = cJeu->cNiveau.getScriptFolder() + coucheFile;
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

/**
 * setScriptPath(folder, luaFile)
 * set the current folder (and the luaFile to execute if 2 args are passed)
 */
int CLua::setScriptPath(lua_State* l)
{
  if (getTop() >= 1)
  {
    cJeu->cNiveau.setScriptFolder(lua_tostring(l, 1));
  }
  else if (getTop() == 2)
  {
    cJeu->cNiveau.setLevelMainFile(lua_tostring(l, 2));
  }

  return 0;
}

/**
 * return the current lua path and the current luaFile
 */
int CLua::getScriptPath(lua_State* l)
{
  testArgs(0);
  push(cJeu->cNiveau.getScriptFolder().c_str());
  push(cJeu->cNiveau.getLevelMainFile().c_str());
  return 2;
}

int CLua::getResourcesPath(lua_State* l)
{
  push(MParameters::getRootPath().c_str());
  return 1;
}

int CLua::addActionDeclenchement(lua_State* l)
{
  testArgs(4);
  MTypeCouche couche = (MTypeCouche)lua_tointeger(l, 3);

  if (lua_isfunction(l, -1))
  {
    // store function
    int curIndex = luaL_ref(l, LUA_REGISTRYINDEX);

    getTuile(1)->getPartieCouche(couche)->setActionDeclenchement(
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
  MTypeCouche couche = (MTypeCouche)lua_tointeger(l, 3);

  if (lua_isfunction(l, -1))
  {
    // store function
    int curIndex = luaL_ref(l, LUA_REGISTRYINDEX);

    // get tuile with coord in 1st and 2sc param
    getTuile(1)->getPartieCouche(couche)->setActionPassage([curIndex, l](std::string entite)
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
/**
 * newEntity(name, texture, x, y, taille)
 */
int CLua::newEntity(lua_State* l)
{
  testArgs(5);
  std::string name = lua_tostring(l, 1);
  std::string texture = lua_tostring(l, 2);
  MTuile* tuile = getTuile(3);
  float taille = lua_tonumber(l, 5);

  cJeu->cNiveau.addEntite(name, texture, tuile, taille);
  return 0;
}

/**
 * addActionDefense(string entite, actionDefense(string entiteAttaquante, int degat));
 */
int CLua::addActionDefense(lua_State* l)
{
  testArgs(2);
  MEntite* entite = cJeu->getEntite(lua_tostring(l, 1));
  if (lua_isfunction(l, -1))
  {
    // store function
    int curIndex = luaL_ref(l, LUA_REGISTRYINDEX);

    entite->setActionDefense([curIndex, l](std::string entite, int degat)
    {
      // get function previously stored in special lua table registry
        lua_rawgeti(l, LUA_REGISTRYINDEX, curIndex);
        if (lua_isfunction(l, -1))
        {
          // pass entity name on 1st parameter
          push(entite.c_str());
          push(degat);
          // call function defined by lua
          lua_call(l, 2, 0);
        }
      });

  }

  return 0;
}

MEntite* CLua::getEntite(std::string& entiteName, int nbArgsNoEntity)
{
  if (getTop() - nbArgsNoEntity == 1)
  {
    entiteName = lua_tostring(lua, 1);
    return cJeu->getEntite(entiteName);
  }
  else if (getTop() - nbArgsNoEntity == 0)
  {
    entiteName = cJeu->cPersonnage.getCurrentPerso()->getNom();
    return cJeu->cPersonnage.getCurrentPerso();
  }
  else
  {
    throw MExceptionLuaArguments(
        "one arg for personnage, \ntwo : string for entity, int for item", getTop());
  }
}

/**
 * setPosition(string entiteName, int x, int y)
 */
int CLua::setPosition(lua_State* l)
{
  // FIXME : testNbArgs
  std::string entiteName;
  MEntite* e = getEntite(entiteName, 2);

  if (e)
  {
    e->setTuile(getTuile(-2));
  }
  else
  {
    throw MExceptionEntiteInexistante(entiteName);
  }
  return 0;
}

int CLua::setTexture(lua_State* l)
{
  std::string entiteName;
  MEntite* e = getEntite(entiteName, 1);
  e->setTexture(lua_tostring(l, -1));
  return 0;
}

/**
 * setTaille(string entiteName, int taille)
 */
int CLua::setTaille(lua_State* l)
{
  // FIXME : testNbArgs
  std::string entiteName;
  float taille = lua_tonumber(l, -1);

  MEntite* e = getEntite(entiteName, 1);

  if (e)
  {
    e->setTaille(taille);
  }
  else
  {
    throw MExceptionEntiteInexistante(entiteName);
  }
  return 0;
}

int CLua::getCurrentPerso(lua_State* l)
{
  testArgs(0);
  lua_pushstring(l, cJeu->cPersonnage.getCurrentPerso()->getNom().c_str());
  return 1;
}

void CLua::registerBaseFunctions()
{
  lua_register(lua, "setScriptPath", setScriptPath);
  lua_register(lua, "getScriptPath", getScriptPath);
  lua_register(lua, "getResourcesPath", getResourcesPath);
}

void CLua::registerTerrainFunctions()
{
  lua_register(lua, "loadCouche", loadCouche);
  lua_register(lua, "addActionDeclenchement", addActionDeclenchement);
  lua_register(lua, "addActionPassage", addActionPassage);
}

void CLua::registerEntiteFunctions()
{
  lua_register(lua, "newEntity", newEntity);

  lua_register(lua, "setTaille", setTaille);
  lua_register(lua, "setPosition", setPosition);
  lua_register(lua, "setTexture", setTexture);
  lua_register(lua, "getCurrentPerso", getCurrentPerso);
  lua_register(lua, "addActionDefense", addActionDefense);
}

void CLua::executeScript(std::string script)
{
  try
  {
    luaL_dofile(lua, script.c_str());
  }
  catch (MAssException& e)
  {
    throw;
  }
  catch (...)
  {
    lua_Debug ar;
    lua_getstack(lua, 0, &ar);
    lua_getinfo(lua, "nfSl", &ar);
    std::cout << "Error in " << ar.namewhat << " : " << ar.name << '\n';
  }
}

////////////////////////////////////////////////////////////////////////////////
//-/////////////////////////Lua/ASS function Helpers/////////////////////////-//
////////////////////////////////////////////////////////////////////////////////
MTuile* CLua::getTuile(int index)
{
  int x = lua_tointeger(lua, index);
  int y = lua_tointeger(lua, index + 1);
  return &(cJeu->cNiveau.getTerrain()(x, y));
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

void CLua::push(lua_Integer n)
{
  lua_pushinteger(lua, n);
}

void CLua::push(int n)
{
  lua_pushinteger(lua, n);
}

int CLua::getTop()
{
  return lua_gettop(lua);
}

void CLua::testArgs(int nbExcpected)
{

  int nb = lua_gettop(lua);
  try
  {
    if (nb != nbExcpected)
    {
      lua_Debug ar;
      lua_getstack(lua, 0, &ar);
      lua_getinfo(lua, "nf", &ar);
      throw MExceptionLuaArguments(
          "Expect " + std::to_string(nbExcpected) + " arguments for " + std::string(ar.name),
          nb);
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

