/**
 * VPrimitif.hpp
 *
 * Early optimization is the root of all evil
 *
 *  Created on: 10 nov. 2017
 *      Author: nihil
 */

#pragma once

#include <string>
#include <fstream>
#include "../model/MCoordonnees.hpp"

class VPrimitif
{
//========================>Attributes<========================
private:
  static char constexpr perso = '*';
  static char constexpr terrainHerbe = '.';
  static char constexpr montagne = '#';
  static int constexpr TAILLE_MAX = 100;

  static std::string const escC;
  static std::string const endC;
  static std::string const sepC;
  static std::string const foregroundRgb;

  static std::string const vert;
  static std::string const marron;
  static std::string const blanc;

  MCoordonnees positionJoueur;
//=======================>Constructors<=======================
public:
  VPrimitif();
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
  MCoordonnees getPosition() const;
private:

};

