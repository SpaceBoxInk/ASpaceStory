/**
 * MTerrain.cpp
 *
 * Early optimization is the root of all evil
 *
 *  Created on: 11 nov. 2017
 *      Author: nihil
 */

#include "MTerrain.hpp"
#include "MCoordonnees.hpp"
#include "MParameters.hpp"
#include "MPartieCouche.hpp"

#include <sys/types.h>
#include <fstream>
#include <string>

//------------------------------------------------------------
//========================>Constants<=========================
//------------------------------------------------------------
std::map<u_int8_t, MPartieCouche> MTerrain::solsType;
std::map<u_int8_t, MPartieCouche> MTerrain::elementsType;
std::map<u_int8_t, MPartieCouche> MTerrain::cielsType;

MCoordonnees MTerrain::tailleMax(40, 20);
//------------------------------------------------------------
//=======================>Constructors<=======================
//------------------------------------------------------------

MTerrain::MTerrain()
{
}

MTerrain::~MTerrain()
{
}

//------------------------------------------------------------
//=========================>Methods<==========================
//------------------------------------------------------------
void MTerrain::loadTypes()
{
  std::ifstream fichierTerrain;
  MTypeCouche type = MTypeCouche::SOL;
  std::string name;
  int ID;
  float placeDispo;

  fichierTerrain.open(MParameters::getSolsPath());
  MPartieCouche(type, name, placeDispo);
  fichierTerrain.close();

  fichierTerrain.open(MParameters::getElementsPath());
}

MTuile& MTerrain::operator ()(int x, int y)
{
  return tuiles[x * tailleMax.getX() + y];
}
//------------------------------------------------------------
//=====================>Getters&Setters<======================
//------------------------------------------------------------

