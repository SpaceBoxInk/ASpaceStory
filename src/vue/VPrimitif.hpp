/**
 * VPrimitif.hpp
 *
 * Early optimization is the root of all evil
 *
 *  Created on: 10 nov. 2017
 *      Author: nihil
 */

#pragma once

#include "../model/MCoordonnees.hpp"
#include "../model/MPartieCouche.hpp"
#include "../outils/ObserverPattern/Observed.hpp"

#include <map>
#include <string>
#include <vector>

class MCoordonnees;

class VPrimitif : public Observed
{
//========================>Attributes<========================
private:
  static char constexpr perso = '*';
  static char constexpr terrainHerbe = '.';
  static char constexpr montagne = '#';
  MCoordonnees const TAILLE_MAX;

  static std::string const escC;
  static std::string const endC;
  static std::string const sepC;
  static std::string const foregroundRgb;

  static std::string const blanc;

  static std::map<char, std::string> const colors;

  std::vector<std::string const*> imgSols;
  std::vector<std::string const*> imgElems;
  std::vector<std::string const*> imgCiels;

//=======================>Constructors<=======================
public:
  VPrimitif(MCoordonnees const& coordMax);
  // TODO: rule of five ? copyandswap
  virtual ~VPrimitif();

private:

//=========================>Methods<==========================
public:
  void show(MCoordonnees positionJoueur);
private:
  void printTile(char type);
  void sendInput();
//=====================>Getters&Setters<======================
public:
  void setImg(MTypeCouche const& typeCouche, std::vector<std::string const*> const& imgs);

private:

};

