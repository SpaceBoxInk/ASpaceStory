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

#include <map>
#include <string>

class AppFrameInterface;
class MPersonnage;
class MTuile;

class MTerrain;

/**
 * le controlleur pour gérer les déplacements, les intéractions
 * du personnage (comme il est indépendant des niveaux)
 */
class CPersonnage : public Observer
{
//========================>Attributes<========================
private:
  /**
   * Vue principale TODO : faire vue principale, pour l'instant ce n'est que la vue du terrain
   */
  AppFrameInterface* vuePrincipale;
  std::map<std::string, MPersonnage> personnages;
  MPersonnage* currentPerso;
  MTerrain* terrain;
  bool quit;
//=======================>Constructors<=======================
public:
  CPersonnage(AppFrameInterface* vuePrincipale, MTerrain* terrain);
  // TODO: rule of five ? copyandswap
  virtual ~CPersonnage();

private:

//=========================>Methods<==========================
public:
  bool setPersonnage(std::string nom);
  MPersonnage* getPersonnage(std::string nom);
  MPersonnage* getCurrentPerso();
  void addPersonnage(std::string nom);
private:
  void setEventMethods();

//=====================>Getters&Setters<======================
public:

private:
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
  else
  {
    it->second.addObserver(this);
  }
}

//------------------------------------------------------------
//=====================>Implementations<======================
//------------------------------------------------------------
