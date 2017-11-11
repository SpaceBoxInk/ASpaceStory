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

class VPrimitif
{
//========================>Attributes<========================
private:
  static char constexpr perso = '*';
  static char constexpr terrainHerbe = '.';
  static char constexpr montagne = '#';

  static std::string const escC;
  static std::string const endC;
  static std::string const sepC;
  static std::string const foregroundRgb;

  static std::string const vert;
  static std::string const marron;
  static std::string const blanc;
//=======================>Constructors<=======================
public:
  VPrimitif();
  // TODO: rule of five ? copyandswap
  virtual ~VPrimitif();

private:

//=========================>Methods<==========================
public:
  void show();
private:
  char getInput();
//=====================>Getters&Setters<======================
public:

private:

};

