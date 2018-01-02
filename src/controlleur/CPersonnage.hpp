/**
 * CPersonnage.hpp
 *
 * Early optimization is the root of all evil
 *
 *  Created on: 10 nov. 2017
 *      Author: nihil
 */

#pragma once

#include "../editor/controler/CEditor.hpp"
#include "../model/MAssException.hpp"
#include "../model/MPersonnage.hpp"

#include <map>
#include <string>

class AppFrameInterface;
class MPersonnage;
class MTuile;
class MTerrain;

/**
 * le controlleur pour gérer les déplacements, les interactions
 * du personnage (comme il est indépendant des niveaux)
 */
class CPersonnage : public Observer
{
//========================>Attributes<========================
private:
  AppFrameInterface* vuePrincipale;
  CEditor editor;

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
  void addRobot(std::string const& nom, std::string const& texture, MTuile* tuile,
                float taille);
private:
  void setEventMethods();

//=====================>Getters&Setters<======================
public:

private:
};

//------------------------------------------------------------
//=====================>Implementations<======================
//------------------------------------------------------------

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

