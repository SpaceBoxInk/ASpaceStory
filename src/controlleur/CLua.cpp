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

#include "../model/MAssException.hpp"
#include "../model/MInventaire.hpp"
#include "../model/MItem.hpp"
#include "../model/MPartieCouche.hpp"
#include "../model/MTerrain.hpp"
#include "../model/MTuile.hpp"
#include "CJeu.hpp"
#include "CNiveau.hpp"

//------------------------------------------------------------
//========================>static members<=========================
//------------------------------------------------------------
lua_State* CLua::lua = luaL_newstate();
CJeu* CLua::cJeu;
MItem* CLua::item = nullptr;
//------------------------------------------------------------
//=======================>Constructors<=======================
//------------------------------------------------------------

/**
 *
 * @param cJeu
 */
CLua::CLua(CJeu* cJeu)
{
  CLua::cJeu = cJeu;
  luaL_openlibs(lua);

  registerBaseFunctions();
  registerTerrainFunctions();
  registerEntiteFunctions();
  registerItemFunctions();
  registerEnigmeFunctions();
}

CLua::~CLua()
{
  lua_close(lua);
}

//------------------------------------------------------------
//=========================>Methods<==========================
//------------------------------------------------------------
/**
 * lua function signature :\n
 * void loadCouche(string coucheFile, int couche);\n
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
 * setScriptPath(folder, luaFile)\n
 * set the current folder (and the luaFile to execute if 2 args are passed)
 */
int CLua::setScriptPath(lua_State* l)
{
  if (getTop() == 1 || getTop() == 2)
  {
    cJeu->cNiveau.setScriptFolder(lua_tostring(l, 1));
  }
  else
  {
    throw MExceptionLuaArguments("setScriptPath(folder, luaFile = oldLuaFile)", getTop());
  }

  if (getTop() == 2)
  {
    cJeu->cNiveau.setLevelMainFile(lua_tostring(l, 2));
  }

  return 0;
}

/**
 * string getScriptPath()\n
 * return the current lua path and the current luaFile
 */
int CLua::getScriptPath(lua_State* l)
{
  testArgs(0);
  push(cJeu->cNiveau.getScriptFolder().c_str());
  push(cJeu->cNiveau.getLevelMainFile().c_str());
  return 2;
}

/**
 * string getResourcesPath()\n
 * return le chemin vers le dossier de ressources
 */
int CLua::getResourcesPath(lua_State* l)
{
  push(MParameters::getRootPath().c_str());
  return 1;
}

/**
 * redefinie le comportement du loadfile pour prendre en compte le chemin vers le dossier du script "courant"
 */
int CLua::loadfile(lua_State* l)
{
  std::string file = cJeu->cNiveau.getScriptFolder() + lua_tostring(l, 1);
  luaL_loadfile(l, file.c_str());
  return 1;
}

/**
 * addActionDeclenchement(int x, int y, int couche, fonction actionDeclenchement(entite))\n
 * ajoute l'action actionDeclenchement à la couche n°couche en (x,y)
 * déclenché lorsqu'une entité déclenche la couche(action volontaire)
 */
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

/**
 * addActionPassage(int x, int y, int couche, fonction actionPassage(string entite))\n
 * ajoute l'action actionPassage à la couche n°couche en (x,y)
 * déclenché lorsqu'une entité passe sur la couche(action NON volontaire)
 */
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

/**
 * @param entiteName out: le nom de l'entité retourné
 * @param nbArgsNoEntity: le nombre d'argument sans compter ce qu'il faut pour prendre une entité
 * @return retourne l'entité nommée si le nom de l'entité est spécifié (getTop() - nbArgsNoEntity == 1)
 * sinon retourne le personnage courant
 */
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

/**
 * setTexture(string entiteName, string texture)\n
 * set la texture de l'entité spécifiée\n
 *
 * setTexture(string texture)\n
 * set la texture du perso courant
 *
 */
int CLua::setTexture(lua_State* l)
{
  std::string entiteName;
  MEntite* e = getEntite(entiteName, 1);
  e->setTexture(lua_tostring(l, -1));
  return 0;
}

/**
 * setTaille(string entiteName, int taille)\n
 * set la taille de l'entité spécifiée\n
 *
 * setTaille(int taille)\n
 * set la taille du perso courant
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

/**
 * string getCurrentPerso()\n
 * retourne le nom du perso courant
 */
int CLua::getCurrentPerso(lua_State* l)
{
  testArgs(0);
  lua_pushstring(l, cJeu->cPersonnage.getCurrentPerso()->getNom().c_str());
  return 1;
}

/**
 * newRobot(string nom, string texture, int x, int y, float taille)\n
 *
 */
int CLua::newRobot(lua_State* l)
{
  std::string nom = lua_tostring(l, 1);
  std::string texture = lua_tostring(l, 2);
  MTuile* tuile = getTuile(3);
  float taille = lua_tonumber(l, 5);

  cJeu->cPersonnage.addRobot(nom, texture, tuile, taille);
  return 0;
}

/**
 * newItem(nom, description, texture, degat = 0, equipement = MAIN(0), protection = 0, supprimable = true, miningLevel = 0)
 */
int CLua::newItem(lua_State* l)
{
  // required parameters :
  std::string nom = lua_tostring(l, 1);
  std::string description = lua_tostring(l, 2);
  std::string texture = lua_tostring(l, 3);
  // Default parameters :
  int degats = 0;
  MTypeEquipement equipement = MTypeEquipement::MAIN;
  int protection = 0;
  bool supprimable = true;
  int miningLevel = 0;

  switch (getTop()) {
  case 8:
    miningLevel = lua_tointeger(l, 7);
    /* no break */
  case 7:
    supprimable = lua_toboolean(l, 6);
    /* no break */
  case 6:
    protection = lua_tointeger(l, 5);
    /* no break */
  case 5:
    degats = lua_tointeger(l, 4);
    /* no break */
  case 4:
    equipement = (MTypeEquipement)lua_tointeger(l, 3);
    break;
  case 3:
      // default min parameters
    break;
  default:
    throw MExceptionLuaArguments("Nombre d'argument pour création d'item invalid ! ",
                                 getTop());
  }
  item = new MItem(nom, texture, description, equipement, degats, protection, supprimable,
                   miningLevel);
  push(item->getId());
  return 1;
}

int CLua::giveNewItemToPerso(lua_State* l)
{
  cJeu->cPersonnage.getCurrentPerso()->addItemToInventaire(getItem());
  item = nullptr;
  return 0;
}

int CLua::giveNewItemToEntity(lua_State* l)
{
  testArgs(1);
  std::string nomEntite = lua_tostring(l, 2);
  MEntite* entite = cJeu->getEntite(nomEntite);
  entite->addItemToInventaire(getItem());
  item = nullptr;
  return 0;
}

int CLua::putNewItemOn(lua_State* l)
{
  testArgs(2);
  int x = lua_tointeger(l, 1);
  int y = lua_tointeger(l, 2);
  cJeu->cNiveau.getTerrain()(x, y).addItem(getItem());
  item = nullptr;
  return 0;
}

/**
 * addActionUtilisation(luaFunction)
 */
int CLua::addActionUtilisation(lua_State* l)
{
  testArgs(1);
  if (lua_isfunction(l, -1))
  {
    // store function
    int curIndex = luaL_ref(l, LUA_REGISTRYINDEX);
    getItem()->setActionUtilisation([curIndex, l](std::string entite)
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

int CLua::addActionMining(lua_State* l)
{
  testArgs(2);
  std::string element = lua_tostring(l, 1);
  int curIndex = storeFunction();
  cJeu->cNiveau.getTerrain().getElement(element).setActionMining(
      [curIndex, l](MEntite* entite, int item)
      {
        pushFunctionFrom(curIndex);
        // pass entity name on 1st parameter
        push(entite->getNom().c_str());
        lua_pushinteger(l, item);
        // call function defined by lua
        lua_call(l, 2, 1);
        if (!lua_isnil(l, -1))
        {
          entite->addItemToInventaire(getItem());
          CLua::item = nullptr;
        }
      });

  return 0;
}

int CLua::newEnigme(lua_State* l)
{
  testArgs(3);
  std::string nom = lua_tostring(l, 1);
  std::string description = lua_tostring(l, 2);
  std::string image = lua_tostring(l, 3);
  cJeu->cNiveau.addEnigme(nom, description, image);
  return 0;
}

int CLua::afficherEnigme(lua_State* l)
{
  testArgs(1);
  std::string nom = lua_tostring(l, 1);
  cJeu->cNiveau.afficherEnigme(nom);
  return 0;
}

void CLua::registerBaseFunctions()
{
  lua_register(lua, "setScriptPath", setScriptPath);
  lua_register(lua, "getScriptPath", getScriptPath);
  lua_register(lua, "getResourcesPath", getResourcesPath);
  lua_register(lua, "loadfile", loadfile);
}

void CLua::registerTerrainFunctions()
{
  lua_register(lua, "loadCouche", loadCouche);
  lua_register(lua, "addActionDeclenchement", addActionDeclenchement);
  lua_register(lua, "addActionPassage", addActionPassage);

  // TODO : change in another register !!
  lua_register(lua, "addActionMining", addActionMining);
}

void CLua::registerEntiteFunctions()
{
  lua_register(lua, "newEntity", newEntity);
  lua_register(lua, "newRobot", newRobot);

  lua_register(lua, "setTaille", setTaille);
  lua_register(lua, "setPosition", setPosition);
  lua_register(lua, "setTexture", setTexture);
  lua_register(lua, "getCurrentPerso", getCurrentPerso);
  lua_register(lua, "addActionDefense", addActionDefense);
}

void CLua::registerItemFunctions()
{
  lua_register(lua, "newItem", newItem);
  lua_register(lua, "giveNewItemToPerso", giveNewItemToPerso);
  lua_register(lua, "giveNewItemToEntity", giveNewItemToEntity);
  lua_register(lua, "putNewItemOn", putNewItemOn);
  lua_register(lua, "addActionUtilisation", addActionUtilisation);
}

void CLua::registerEnigmeFunctions()
{
  lua_register(lua, "newEnigme", newEnigme);
  lua_register(lua, "afficherEnigme", afficherEnigme);
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
/**
 *
 * @param index a partir du quel sont rangé le x, y dans la pile lua
 * @return la tuile en (x, y) pris depuis l'index
 */
MTuile* CLua::getTuile(int index)
{
  int x = lua_tointeger(lua, index);
  int y = lua_tointeger(lua, index + 1);
  return &(cJeu->cNiveau.getTerrain()(x, y));
}

MItem* CLua::getItem()
try
{
  if (!item)
  {
    throw MExceptionNullPtr("Aucun item de nouveau créé ! call : " + getCurFunction());
  }
  return item;
}
catch (MAssException& e)
{
  std::cerr << e.what() << std::endl;
  throw;
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

void CLua::push(lua_Unsigned n)
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

int CLua::storeFunction()
{
  if (lua_isfunction(lua, -1))
  {
    // store function
    return luaL_ref(lua, LUA_REGISTRYINDEX);
  }
  throw std::invalid_argument("This is not a function ! called : " + getCurFunction());
  return 0;
}

void CLua::pushFunctionFrom(int index)
{
  // get function previously stored in special lua table registry
  lua_rawgeti(lua, LUA_REGISTRYINDEX, index);
  if (!lua_isfunction(lua, -1))
  {
    throw std::invalid_argument(
        "Try to get back a function but not get a function ! called : " + getCurFunction());
  }
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



std::string CLua::getCurFunction()
{
  lua_Debug ar;
  lua_getstack(lua, 0, &ar);
  lua_getinfo(lua, "nf", &ar);
  return ar.name;
}
////////////////////////////////////////////////////////////////////////////////

//------------------------------------------------------------
//=====================>Getters&Setters<======================
//------------------------------------------------------------

