/**
 * MTerrain.cpp
 *
 * Early optimization is the root of all evil
 *
 *  Created on: 11 nov. 2017
 *      Author: nihil
 */

#include "MTerrain.hpp"
#include "MAssException.hpp"
#include "MCoordonnees.hpp"
#include "MParameters.hpp"

#include <bits/stdint-uintn.h>
#include <fstream>
#include <iostream>
#include <iterator>
#include <utility>
#include <stdexcept>

//------------------------------------------------------------
//========================>Constants<=========================
//------------------------------------------------------------
std::unordered_map<std::uint8_t, MPartieCouche> MTerrain::solsType;
std::unordered_map<std::uint8_t, MPartieCouche> MTerrain::elementsType;
std::unordered_map<std::uint8_t, MPartieCouche> MTerrain::cielsType;

MCoordonnees MTerrain::tailleMax(40, 20);
//------------------------------------------------------------
//=======================>Constructors<=======================
//------------------------------------------------------------

MTerrain::MTerrain()
{
  loadTypes();
  try
  {
    loadCouche(MParameters::getLevelPath() + "/level1/level1.nbg", MTypeCouche::SOL);
  }
  catch (MAssException& e)
  {
    std::cerr << e.what();
    throw;
  }
}

MTerrain::~MTerrain()
{
}

//------------------------------------------------------------
//=========================>Methods<==========================
//------------------------------------------------------------
void MTerrain::loadTypes()
{
  loadSpecificPath(MParameters::getSolsPath(), MTypeCouche::SOL);
  loadSpecificPath(MParameters::getElementsPath(), MTypeCouche::ELEMENT);
  loadSpecificPath(MParameters::getCielsPath(), MTypeCouche::CIEL);
}

void MTerrain::loadSpecificPath(std::string fichier, MTypeCouche const& type)
{
  std::ifstream fichierType;
  std::string name;
  std::string imgFile;
  unsigned short ID;
  float placeDispo;

  fichierType.open(fichier);
  if (fichierType)
  {
    while (!fichierType.eof())
    {
      fichierType >> name;
      if (name[0] == '#')
      {
        // on ne veut pas la line commentée
        std::getline(fichierType, name);
        continue;
      }
      fichierType >> imgFile; // passer les ':'
      fichierType >> imgFile;
      fichierType >> ID;
      fichierType >> placeDispo;
      getTypeList(type).insert( { ID, MPartieCouche(type, name, imgFile, placeDispo) });
    }
  }
  else
  {
    std::cerr << "File " << fichier << " could not be opened" << '\n';
  }
  fichierType.close();
}

std::unordered_map<uint8_t, MPartieCouche>& MTerrain::getTypeList(
    MTypeCouche const& typeCouche)
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

MCoordonnees MTerrain::getCoords(int index)
{
  return MCoordonnees(index % tailleMax.getX(), index / tailleMax.getX());
}

/**
 * FIXME : complete comments
 * @param fichier
 * @param type
 */
void MTerrain::loadCouche(std::string const & fichier, MTypeCouche const & type)
{
  std::ifstream fichierCouche(fichier, std::ios::binary);
  if (fichierCouche)
  {
    uint32_t nbElemRequis = (unsigned int)(tailleMax.getX() * tailleMax.getY());
    uint8_t ID;
    std::vector<uint8_t> vecteurControle;
    vecteurControle.insert(vecteurControle.begin(),
                           std::istream_iterator<uint8_t>(fichierCouche),
                           std::istream_iterator<uint8_t>());
    if (vecteurControle.size() == nbElemRequis)
    {
      for (unsigned int i = 0; i < vecteurControle.size(); ++i)
      {
        ID = vecteurControle[i];
        if (ID == 0 && type != MTypeCouche::SOL)
        {
          // le rien
          continue;
        }
        else if (ID == 0 && type == MTypeCouche::SOL)
        {
          throw std::invalid_argument(
              std::string("Id 0 not expected for couche SOL in offset ") + std::to_string(i));
        }
        MPartieCouche const & couche = getTypeList(type).at(ID);
        // si on veut mettre une couche à une tuile pas existante
        // il faut aussi que le type soit le sol, on commence par le sol !
        if (tuiles.size() <= i && type == MTypeCouche::SOL)
        {
          // SEE : push_back may be replaced by something related to the position "i"
          tuiles.push_back(
              new MTuile(getCoords(i), couche.getName(), couche.getFichierImg(),
                         couche.getPlaceDispo()));
        }
        else if (tuiles.size() > i)
        {
          tuiles[i]->setPartieCouche(couche.getType(), couche.getName(),
                                     couche.getFichierImg(), couche.getPlaceDispo());
        }
        else
        {
          throw MExceptionInvalidTypeCouche(MTypeCouche::SOL, type);
        }
      }
    }
    else
    {
      throw MExceptionFile(fichier,
          "Le fichier n'est pas du bon format\nil faut " + std::to_string(nbElemRequis)
              + " tuiles(octets)");
    }
  }
  else
  {
    throw MExceptionFile(fichier, "ne peut etre ouvert");
  }
}

MTuile& MTerrain::operator ()(int x, int y)
{
  return (*this)(MCoordonnees(x, y));
}

MTuile& MTerrain::operator ()(MCoordonnees const & coord)
{
  if (coord.getX() >= 0 && coord.getY() >= 0 && coord.getX() < tailleMax.getX()
      && coord.getY() < tailleMax.getY())
  {
    return *tuiles.at(coord.getY() * tailleMax.getX() + coord.getX());
  }
  throw MExceptionOutOfTerrain(coord);
}

MTuile& MTerrain::operator ()(int index)
try
{
  return *tuiles.at(index);
}
catch (...)
{
  throw MExceptionOutOfTerrain(index);
}

std::vector<MTuile*> MTerrain::getAdjacentes(MTuile const & tuile)
{
  using MouvementT::operator *;

  std::vector<MTuile*> tuiles;
  // this is a pointer
  // we want to use operator(MCoordonnees)
  // (*this) : deref this,
  MTerrain& thisRef = *this;
  for (int i = 0; i < (int)Mouvement::SIZE; ++i)
  {
    try
    {
      // call operator() then we reference the result : we want the pointer
      tuiles.push_back(&thisRef(tuile.getPosition() + *(Mouvement)i));
    }
    catch (MExceptionOutOfTerrain& e)
    {
    }
  }
  return tuiles;
}

std::vector<std::string const*> MTerrain::getImagesList(MTypeCouche typeCouche)
{
  std::vector<std::string const*> imgs;
  for (MTuile const* tuile : tuiles)
  {
    MPartieCouche const* couche = tuile->getPartieCouche(typeCouche);
    if (couche)
    {
      imgs.push_back(&couche->getFichierImg());
    }
    else
    {
      imgs.push_back(nullptr);
    }
  }
  return imgs;
}
//------------------------------------------------------------
//=====================>Getters&Setters<======================
//------------------------------------------------------------

