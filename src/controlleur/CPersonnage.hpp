/**
 * CPersonnage.hpp
 *
 * Early optimization is the root of all evil
 *
 *  Created on: 10 nov. 2017
 *      Author: nihil
 */

#pragma once

#include "../model/MPersonnage.hpp"
#include "../outils/ObserverPattern/Observer.hpp"

#include <string>

class AppFrameInterface;
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
  AppFrameInterface* vuePrincipale;

  MPersonnage* personnage;

  MTerrain* terrain;
//=======================>Constructors<=======================
public:
  CPersonnage(AppFrameInterface* vuePrincipale, MTerrain* terrain);
  // TODO: rule of five ? copyandswap
  virtual ~CPersonnage();

private:

//=========================>Methods<==========================
public:
  void setPersonnage(std::string nom, std::string sprite, MTuile* tuile, float taille);
private:
  void setEventMethods();

//=====================>Getters&Setters<======================
public:

private:
};

inline void CPersonnage::setPersonnage(std::string nom, std::string sprite, MTuile* tuile,
                                       float taille)
{
  personnage = new MPersonnage(nom, sprite, tuile, taille);
}

//------------------------------------------------------------
//=====================>Implementations<======================
//------------------------------------------------------------
