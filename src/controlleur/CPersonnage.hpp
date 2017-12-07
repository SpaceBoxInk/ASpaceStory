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
#include "../vue/VPrimitif.hpp"

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

  MPersonnage* personnage;

  MTerrain* terrain;
//=======================>Constructors<=======================
public:
  CPersonnage(VPrimitif* vuePrincipale, MTerrain* terrain, MPersonnage* personnage);
  // TODO: rule of five ? copyandswap
  virtual ~CPersonnage();

private:

//=========================>Methods<==========================
public:

private:
  void setEventMethods();

//=====================>Getters&Setters<======================
public:

private:
  void changeVue(VPrimitif* vTerrain);
};
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
