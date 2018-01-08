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
#include "CPersonnage.hpp"

#include "../model/MAssException.hpp"
#include "../model/MCoordonnees.hpp"
#include "../model/MInventaire.hpp"
#include "../model/MItem.hpp"
#include "../model/MParameters.hpp"
#include "../model/MPartieCouche.hpp"
#include "../model/MPersonnage.hpp"
#include "../model/MTerrain.hpp"
#include "../model/MTuile.hpp"
#include "../vue/VInventaireInterface.hpp"

#include <stdexcept>

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
int CLua::cppLoadCouche(lua_State* l)
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
int CLua::cppSetScriptPath(lua_State* l)
{
  testArgs(1, 2);
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
int CLua::cppGetScriptPath(lua_State* l)
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
int CLua::cppGetResourcesPath(lua_State* l)
{
  testArgs(0);
  push(MParameters::getRootPath().c_str());
  return 1;
}

/**
 * redefinie le comportement du loadfile pour prendre en compte le chemin vers le dossier du script "courant"
 */
int CLua::loadfile(lua_State* l)
{
  testArgs(1);
  std::string file = cJeu->cNiveau.getScriptFolder() + lua_tostring(l, 1);
  luaL_loadfile(l, file.c_str());
  return 1;
}

/**
 * addActionDeclenchement(int x, int y, int couche, fonction actionDeclenchement(entite))\n
 * ajoute l'action actionDeclenchement à la couche n°couche en (x,y)
 * déclenché lorsqu'une entité déclenche la couche(action volontaire)
 */
int CLua::cppAddActionDeclenchement(lua_State* l)
{
  testArgs(4);
  MTypeCouche typeCouche = (MTypeCouche)lua_tointeger(l, 3);

  if (lua_isfunction(l, -1))
  {
    // store function
    int curIndex = luaL_ref(l, LUA_REGISTRYINDEX);

    auto couche = getTuile(1)->getPartieCouche(typeCouche);
    if (!couche)
    {
      throw MAssException("Couche " + to_string(typeCouche) + " inexistante");
    }

    couche->setActionDeclenchement(
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
int CLua::cppAddActionPassage(lua_State* l)
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
int CLua::cppNewEntity(lua_State* l)
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
int CLua::cppAddActionDefense(lua_State* l)
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
 * set la position de l'entite de nom entiteName\n
 *
 * setPosition(int x, int y)\n
 * set la position du perso
 */
int CLua::cppSetPosition(lua_State* l)
{
  testArgs(2, 3);
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
int CLua::cppSetTexture(lua_State* l)
{
  testArgs(1, 2);
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
int CLua::cppSetTaille(lua_State* l)
{
  testArgs(1, 2);
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
int CLua::cppGetCurrentPerso(lua_State* l)
{
  testArgs(0);
  lua_pushstring(l, cJeu->cPersonnage.getCurrentPerso()->getNom().c_str());
  return 1;
}

/**
 * newRobot(string nom, string texture, int x, int y, float taille)\n
 *
 */
int CLua::cppNewRobot(lua_State* l)
{
  testArgs(5);
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
int CLua::cppNewItem(lua_State* l)
{
  // required parameters :
  testArgs(3, 8);
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

/**
 * cppGiveNewItemToPerso()
 * donne le nouvel item créé au personnage courant
 */
int CLua::cppGiveNewItemToPerso(lua_State* l)
{
  testArgs(0);
  cJeu->cPersonnage.getCurrentPerso()->addItemToInventaire(getItem());
  item = nullptr;
  return 0;
}

/**
 * cppGiveNewItemToEntity(string nom)
 * donne le nouvel item créé à l'entité de nom nom
 */
int CLua::cppGiveNewItemToEntity(lua_State* l)
{
  testArgs(1);
  std::string nomEntite = lua_tostring(l, 2);
  MEntite* entite = cJeu->getEntite(nomEntite);
  entite->addItemToInventaire(getItem());
  item = nullptr;
  return 0;
}

/**
 * cppPutNewItemOn(int x, int y)
 * met l'item nouvellement créé sur la tuile (x, y)
 */
int CLua::cppPutNewItemOn(lua_State* l)
{
  testArgs(2);
  getTuile(1)->addItem(getItem());
  item = nullptr;
  return 0;
}

/**
 * addInventory(int x, int y, int tailleX, int tailleY)
 * permet d'ajouter un inventaire VISIBLE à la tuile de coordonnées (x, y)
 * de taille (tailleX, tailleY)
 */
int CLua::cppAddInventory(lua_State* l)
{
  testArgs(4);
  int tailleX = lua_tointeger(l, 3);
  int tailleY = lua_tointeger(l, 4);
  getTuile(1)->addInventaire(MCoordonnees(tailleX, tailleY));

  return 0;
}

/**
 * cppShowInventory(int x, int y)
 * show the inventory on coords (x, y)
 */
int CLua::cppShowInventory(lua_State* l)
{
  testArgs(2);
  getTuile(1)->getInventaire()->show();

  return 0;
}

/**
 * addActionUtilisation(luaFunction)
 */
int CLua::cppAddActionUtilisation(lua_State* l)
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

/**
 * addActionMining(string element, function(string entite, int itemId, int xMined, int yMined))
 * element est le nom d'un element définie dans elementList
 *
 * la fonction passée en paramètre peut retourner l'id du dernier item créé (dans cette fonction par exemple)
 * pour mettre cet item dans l'inventaire de l'entité mineuse
 */
int CLua::cppAddActionMining(lua_State* l)
{
  testArgs(2);
  std::string element = lua_tostring(l, 1);
  int curIndex = storeFunction();
  cJeu->cNiveau.getTerrain().getElement(element).setActionMining(
      [curIndex, l](MEntite* entite, int item, int xMined, int yMined)
      {
        pushFunctionFrom(curIndex);
        // pass entity name on 1st parameter
        push(entite->getNom().c_str());
        lua_pushinteger(l, item);
        lua_pushinteger(l, xMined);
        lua_pushinteger(l, yMined);
        // call function defined by lua
        lua_call(l, 4, 1);
        if (!lua_isnil(l, -1))
        {
          entite->addItemToInventaire(getItem());
          CLua::item = nullptr;
        }
      });

  return 0;
}

/**
 * newEnigme(nom, description, image)
 */
int CLua::cppNewEnigme(lua_State* l)
{
  testArgs(3);
  std::string nom = lua_tostring(l, 1);
  std::string description = lua_tostring(l, 2);
  std::string image = lua_tostring(l, 3);
  cJeu->cNiveau.addEnigme(nom, description, image);
  return 0;
}

/**
 * afficherEnigme(nom)
 */
int CLua::cppAfficherEnigme(lua_State* l)
{
  testArgs(1);
  std::string nom = lua_tostring(l, 1);
  cJeu->cNiveau.afficherEnigme(nom);
  return 0;
}

void CLua::registerBaseFunctions()
{
  lua_register(lua, "cppSetScriptPath", cppSetScriptPath);
  lua_register(lua, "cppGetScriptPath", cppGetScriptPath);
  lua_register(lua, "cppGetResourcesPath", cppGetResourcesPath);
  lua_register(lua, "loadfile", loadfile);
}

void CLua::registerTerrainFunctions()
{
  lua_register(lua, "cppLoadCouche", cppLoadCouche);
  lua_register(lua, "cppAddActionDeclenchement", cppAddActionDeclenchement);
  lua_register(lua, "cppAddActionPassage", cppAddActionPassage);

  lua_register(lua, "cppAddActionMining", cppAddActionMining);
}

void CLua::registerEntiteFunctions()
{
  lua_register(lua, "cppNewEntity", cppNewEntity);
  lua_register(lua, "cppNewRobot", cppNewRobot);

  lua_register(lua, "cppSetTaille", cppSetTaille);
  lua_register(lua, "cppSetPosition", cppSetPosition);
  lua_register(lua, "cppSetTexture", cppSetTexture);
  lua_register(lua, "cppGetCurrentPerso", cppGetCurrentPerso);
  lua_register(lua, "cppAddActionDefense", cppAddActionDefense);
}

void CLua::registerItemFunctions()
{
  lua_register(lua, "cppNewItem", cppNewItem);
  lua_register(lua, "cppGiveNewItemToPerso", cppGiveNewItemToPerso);
  lua_register(lua, "cppGiveNewItemToEntity", cppGiveNewItemToEntity);
  lua_register(lua, "cppPutNewItemOn", cppPutNewItemOn);
  lua_register(lua, "cppAddActionUtilisation", cppAddActionUtilisation);

  lua_register(lua, "cppAddInventory", cppAddInventory);
  lua_register(lua, "cppShowInventory", cppShowInventory);
}

void CLua::registerEnigmeFunctions()
{
  lua_register(lua, "cppNewEnigme", cppNewEnigme);
  lua_register(lua, "cppAfficherEnigme", cppAfficherEnigme);
}

void CLua::executeScript(std::string script)
{
  try
  {
    if (luaL_dofile(lua, script.c_str()))
    {
      std::cerr << "\nError : " << lua_tostring(lua, -1) << '\n';
      throw MAssException("Erreur lors de l'execution du script lua");
    }
  }
  catch (...)
  {
    lua_Debug ar;
    lua_getstack(lua, 0, &ar);
    lua_getinfo(lua, "nfSl", &ar);
    std::cerr << "Error in " << ar.namewhat << " : " << ar.name << '\n';
    throw;
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

void CLua::testArgs(int nbExpectedMin, int nbExpectedMax)
{

  int nb = lua_gettop(lua);
  try
  {
    if (nb < nbExpectedMin || nb > nbExpectedMax)
    {
      lua_Debug ar;
      lua_getstack(lua, 0, &ar);
      lua_getinfo(lua, "nf", &ar);
      throw MExceptionLuaArguments(
          "Expect between " + std::to_string(nbExpectedMin) + " arguments and "
              + std::to_string(nbExpectedMax) + " for "
              + std::string(ar.name),
          nb);
    }
  }
  catch (MAssException& e)
  {
    std::cerr << e.what();
    throw;
  }

}

void CLua::testArgs(int nbExpectedMin)
{
  testArgs(nbExpectedMin, nbExpectedMin);
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

