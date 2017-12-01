/**
 * MTerrain.hpp
 *
 * Early optimization is the root of all evil
 *
 *  Created on: 11 nov. 2017
 *      Author: nihil
 */

#pragma once

#include "MTuile.hpp"

#include <map>

class MCoordonnees;

class MTerrain
{
//========================>Attributes<========================
private:
  static std::map<u_int8_t, MPartieCouche> solsType;
  static std::map<u_int8_t, MPartieCouche> elementsType;
  static std::map<u_int8_t, MPartieCouche> cielsType;
  static MCoordonnees tailleMax;

  std::vector<MTuile> tuiles;
//=======================>Constructors<=======================
public:
  MTerrain();
  // TODO: rule of five ? copyandswap
  virtual ~MTerrain();

private:

//=========================>Methods<==========================
public:
  static void loadTypes();
  MTuile& operator()(int x, int y);

private:

//=====================>Getters&Setters<======================
public:

private:

};
