/**
 * MTuile.hpp
 *
 * Early optimization is the root of all evil
 *
 *  Created on: 10 nov. 2017
 *      Author: nihil
 */

#pragma once

#include "MPartieCouche.hpp"

#include <vector>

class MTuile
{
//========================>Attributes<========================
private:
  std::vector<MPartieCouche*> couches;


//=======================>Constructors<=======================
public:
  MTuile(MPartieCouche* sol, MPartieCouche* element = nullptr, MPartieCouche* ciel = nullptr);
  // TODO: rule of five ? copyandswap
  virtual ~MTuile();

private:

//=========================>Methods<==========================
public:

private:

//=====================>Getters&Setters<======================
public:
  void deletePartieCouche(MTypeCouche typeCouche);
  void setPartieCouche(MPartieCouche* couche);

private:
};
