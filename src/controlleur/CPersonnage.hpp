/**
 * CPersonnage.hpp
 *
 * Early optimization is the root of all evil
 *
 *  Created on: 10 nov. 2017
 *      Author: nihil
 */

#pragma once

#include "../model/MAssException.hpp"
#include "../model/MPersonnage.hpp"
#include "../outils/ObserverPattern/Observer.hpp"
#include "../vue/VPrimitif.hpp"

#include <map>
#include <string>

class MPersonnage;
class MTuile;

class MTerrain;

/**
 * le controlleur pour gérer les déplacements, les intéractions
 * du personnage (comme il est indépendant des niveaux)
 */
class CPersonnage : Observer
{
//========================>Attributes<========================
private:
  /**
   * Vue principale TODO : faire vue principale, pour l'instant ce n'est que la vue du terrain
   */
  VPrimitif* vuePrincipale;
  std::map<std::string, MPersonnage> personnages;
  MPersonnage* currentPerso;
  MTerrain* terrain;
  bool quit;
//=======================>Constructors<=======================
public:
  CPersonnage(VPrimitif* vuePrincipale, MTerrain* terrain);
  // TODO: rule of five ? copyandswap
  virtual ~CPersonnage();

private:

//=========================>Methods<==========================
public:
  void launchPersonnage();
  bool setPersonnage(std::string nom);
  void attaquer();
  MPersonnage* getPersonnage(std::string nom);
  MPersonnage* getCurrentPerso();
  void addPersonnage(std::string nom);
private:
  void setEventMethods();

//=====================>Getters&Setters<======================
public:

private:
  void changeVue(VPrimitif* vTerrain);
};

inline bool CPersonnage::setPersonnage(std::string nom)
try
{
  currentPerso = &personnages.at(nom);
  return true;
}
catch (...)
{
  return false;
}

inline MPersonnage* CPersonnage::getPersonnage(std::string nom)
try
{
  return &personnages.at(nom);
}
catch (...)
{
  return nullptr;
}

inline MPersonnage* CPersonnage::getCurrentPerso()
{
  return currentPerso;
}

inline void CPersonnage::addPersonnage(std::string nom)
{
auto [it, isInserted] = personnages.emplace(nom, nom);
  if (!isInserted)
    throw MExceptionEntiteDejaCreee(nom);
}

//------------------------------------------------------------
//=====================>Implementations<======================
//------------------------------------------------------------

/**
 *
 * @param vTerrain la vue du terrain
 * TODO : pour l'instant il n'y a pas la vuePrincipale/vueTerrain
 */
inline void CPersonnage::changeVue(VPrimitif* vTerrain)
{
  if (vuePrincipale)
  {
    delete vuePrincipale;
  }

  this->vuePrincipale = vTerrain;
}
