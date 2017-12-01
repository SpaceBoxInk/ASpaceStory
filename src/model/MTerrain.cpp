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
std::map<uint8_t, MPartieCouche> MTerrain::solsType;
std::map<uint8_t, MPartieCouche> MTerrain::elementsType;
std::map<uint8_t, MPartieCouche> MTerrain::cielsType;

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

void MTerrain::loadTypes()
{
  loadSpecificPath(MParameters::getSolsPath(), MTypeCouche::SOL);
  loadSpecificPath(MParameters::getSolsPath(), MTypeCouche::ELEMENT);
  loadSpecificPath(MParameters::getSolsPath(), MTypeCouche::CIEL);
}

MTuile& MTerrain::operator ()(int x, int y)
{
  return tuiles[x * tailleMax.getX() + y];
}

void MTerrain::loadSpecificPath(std::string fichier, MTypeCouche const& type)
{
  std::ifstream fichierType;
  std::string name;
  std::string imgFile;
  uint8_t ID;
  float placeDispo;

  fichierType.open(fichier);
  if (fichierType)
  {
    while (!fichierType.eof())
    {
      fichierType >> name;
      fichierType >> imgFile; // passer les ':'
      fichierType >> imgFile;
      fichierType >> ID;
      fichierType >> placeDispo;
      getTypeList(type).insert( { ID, MPartieCouche(type, name, placeDispo) });
    }
    fichierType.close();
  }
}

void MTerrain::loadCouche(std::string const & fichier, MTypeCouche const & type)
{
  std::ifstream fichierTerrain(fichier, std::ios::binary);
  char input;
  if (fichierTerrain)
  {
    while (fichierTerrain.read(&input, 1))
    {

      uint8_t ID = (uint8_t)input;
      // MTuile tuile = (getTypeList(type)[ID]);

    }
  }
  uint8_t ID; // elem fichier

}

std::map<uint8_t, MPartieCouche>& MTerrain::getTypeList(MTypeCouche const& typeCouche)
{
  switch (typeCouche) {
  case MTypeCouche::SOL:
    return solsType;
    break;
  case MTypeCouche::ELEMENT:
    return elementsType;
    break;
  default:
    return cielsType;
    break;
  }
}
//------------------------------------------------------------
//=====================>Getters&Setters<======================
//------------------------------------------------------------

