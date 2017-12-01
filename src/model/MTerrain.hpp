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
  static std::map<uint8_t, MPartieCouche> solsType;
  static std::map<uint8_t, MPartieCouche> elementsType;
  static std::map<uint8_t, MPartieCouche> cielsType;
  static MCoordonnees tailleMax;


//=======================>Constructors<=======================
public:
  MTerrain();
  // TODO: rule of five ? copyandswap
  virtual ~MTerrain();

private:

//=========================>Methods<==========================
public:
  static void loadTypes();
  void loadCouche(std::string const& fichier, MTypeCouche const& type);
private:
  static void loadSpecificPath(std::string fichier, MTypeCouche const& type);
//=====================>Getters&Setters<======================
public:

private:
  static std::map<uint8_t, MPartieCouche>& getTypeList(MTypeCouche const& typeCouche);
};
