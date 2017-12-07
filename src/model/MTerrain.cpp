/**
 * MTerrain.cpp
 *
 * Early optimization is the root of all evil
 *
 *  Created on: 11 nov. 2017
 *      Author: nihil
 */

#include "MTerrain.hpp"

#include <_types/_uint8_t.h>
#include <fstream>
#include <iterator>
#include <string>
#include <utility>
#include <vector>

#include "MCoordonnees.hpp"
#include "MParameters.hpp"
#include "MPartieCouche.hpp"

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
  if (fichierTerrain)
  {
    uint8_t ID;
    std::vector<uint8_t> vecteurControle;
    vecteurControle.insert(vecteurControle.begin(),
                           std::istream_iterator<uint8_t>(fichierTerrain),
                           std::istream_iterator<uint8_t>());
    if (vecteurControle.size() <= (unsigned int)(tailleMax.getX() * tailleMax.getY()))
    {
      for (unsigned int i = 0; i < vecteurControle.size(); ++i)
    {
        ID = vecteurControle[i];
      tuiles[i].setPartieCouche(new MPartieCouche(getTypeList(type).find(ID)->second));
      ++i;
    }
    }
  }
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

