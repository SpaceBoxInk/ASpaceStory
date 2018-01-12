/**
 * @file MTerrain.cpp
 *
 * Early optimization is the root of all evil
 *
 *  Created on: 11 nov. 2017
 *      Author: nihil
 */

#include "MTerrain.hpp"
#include "MAssException.hpp"
#include "MEvents.hpp"
#include "MParameters.hpp"
#include "MPartieCoucheElement.hpp"

#include <fstream>
#include <iostream>
#include <experimental/filesystem>
#include <iterator>
#include <stdexcept>
#include <unordered_map>
#include <utility>

namespace fs = std::experimental::filesystem;
//------------------------------------------------------------
//========================>Constants<=========================
//------------------------------------------------------------
std::unordered_map<std::uint8_t, MPartieCouche*> MTerrain::solsType;
std::unordered_map<std::uint8_t, MPartieCouche*> MTerrain::elementsType;
std::unordered_map<std::uint8_t, MPartieCouche*> MTerrain::cielsType;

MCoordonnees MTerrain::taille(16, 8);
//------------------------------------------------------------
//=======================>Constructors<=======================
//------------------------------------------------------------

MTerrain::MTerrain()
{
  taille =
  { MParameters::getNbTuileX(), MParameters::getNbTuileY()};
  loadTypes();
}

MTerrain::~MTerrain()
{
  for (int i = tuiles.size() - 1; i >= 0; --i)
  {
    delete tuiles[i];
    tuiles.pop_back();
  }
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

MCoordonnees MTerrain::toCoords(int index) const
{
  return MCoordonnees(index % taille.getX(), index / taille.getX());
}

void MTerrain::loadSpecificPath(std::string fichier, MTypeCouche const& type)
{
  std::ifstream fichierType;
  std::string name;
  std::string imgFile;
  unsigned short ID;
  float placeDispo;

  int miningLevel;

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
      // FIXME to remove : getTypeList(type).insert( { ID, MPartieCouche(ID, type, name, imgFile, placeDispo) });
      if (type == MTypeCouche::ELEMENT)
      {
        fichierType >> miningLevel;
        getTypeList(type).insert(
            { ID, new MPartieCoucheElement(ID, type, name, imgFile, placeDispo, miningLevel) });
      }
      else
      {
        getTypeList(type).insert(
            { ID, new MPartieCouche(ID, type, name, imgFile, placeDispo) });
      }
    }
  }
  else
  {
    std::cerr << "File " << fichier << " could not be opened" << '\n';
  }
  fichierType.close();
}

MPartieCouche& MTerrain::getElement(std::string element)
{
  auto elemMap = getTypeList(MTypeCouche::ELEMENT);
  return *std::find_if(elemMap.begin(), elemMap.end(),
                       [element](std::pair<uint8_t, MPartieCouche*> pair)
                       {
                         return pair.second->getName() == element;
                       })->second;
}

std::unordered_map<uint8_t, MPartieCouche*>& MTerrain::getTypeList(
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

/**
 * @param fichier le fichier de couche à charger (.data : .nbg, nvc, nsk)
 * @param type le type de couche (0,1,2 : sol, element ciel)
 */
void MTerrain::loadCouche(std::string const & fichier, MTypeCouche const & type)
{
  std::ifstream fichierCouche(fichier, std::ios::binary);

  if (fichierCouche)
  {
    uint32_t nbElemRequis = (unsigned int)(taille.getX() * taille.getY());
    uint32_t nbElem = fs::file_size(fichier);
    uint8_t ID;
    if (nbElem == nbElemRequis)
    {
      for (unsigned int i = 0; i < nbElem; ++i)
      {
        ID = fichierCouche.get();
        if (ID == 0 && type != MTypeCouche::SOL)
        {
          // le rien
          tuiles[i]->deletePartieCouche(type);
          continue;
        }
        else if (ID == 0 && type == MTypeCouche::SOL)
        {
          throw MExceptionArgumentsInvalides(
              std::string("Id 0 not expected for couche SOL in offset ") + std::to_string(i));
        }
        try
        {
          MPartieCouche const& couche = *getTypeList(type).at(ID);
          // si on veut mettre une couche à une tuile pas existante
          // il faut aussi que le type soit le sol, on commence par le sol !
          if (tuiles.size() <= i && type == MTypeCouche::SOL)
          {
            tuiles.push_back(new MTuile(toCoords(i), couche));
          }
          else if (tuiles.size() > i)
          {
            tuiles[i]->setPartieCouche(couche);
          }
          else
          {
            fichierCouche.close();
            throw MExceptionInvalidTypeCouche(MTypeCouche::SOL, type);
          }

        }
        catch (std::exception& e)
        {
          fichierCouche.close();
          throw MExceptionArgumentsInvalides(
              "couche n°" + std::to_string((int)ID) + " n'existe pas dans la liste "
                  + to_string(type) + "\nVoici le nombre d'id : "
                  + std::to_string(getTypeList(type).size() - 1));
        }
      }
      fichierCouche.close();
    }
    else
    {
      fichierCouche.close();
      throw MExceptionFile(
          fichier,
          "Le fichier n'est pas du bon format\nil faut " + std::to_string(nbElemRequis)
              + " tuiles(octets)" "\nVous fournissez " + std::to_string(nbElem)
              + " tuiles(octets)");
    }
  }
  else
  {
    throw MExceptionFile(fichier, "ne peut etre ouvert");
  }
  setChanged();
  notifyObservers(MModelEvents::COUCHE_LOADED, type);
}

/**
 * pour pouvoir faire : terrain(1,1)
 * @return la tuile spécifiée aux coordonnées (x, y)
 * @throw MExceptionOutOfTerrain si les coordonnées sortent du terrain
 */
MTuile& MTerrain::operator ()(int x, int y)
{
  return (*this)(MCoordonnees(x, y));
}

/**
 * pour pouvoir faire : terrain(MCoordonnees(1,1))
 * @return la tuile spécifiée aux coordonnées coord
 * @throw MExceptionOutOfTerrain si les coordonnées sortent du terrain
 */
MTuile& MTerrain::operator ()(MCoordonnees const & coord)
{
  if (coord.getX() >= 0 && coord.getY() >= 0 && coord.getX() < taille.getX()
      && coord.getY() < taille.getY())
  {
    return *tuiles.at(coord.getY() * taille.getX() + coord.getX());
  }
  throw MExceptionOutOfTerrain(coord);
}

/**
 * pour pouvoir faire : terrain(15)
 * @return la tuile spécifiée a l'index index
 * @throw MExceptionOutOfTerrain si l'index sortent du terrain
 */
MTuile& MTerrain::operator ()(int index)
try
{
  return *tuiles.at(index);
}
catch (...)
{
  throw MExceptionOutOfTerrain(index);
}

/**
 *
 * @param tuile
 * @return un vecteur des tuiles adjacentes (en croix sans les diagonales définie par les #Mouvement)
 */
std::vector<MTuile*> MTerrain::getAdjacentes(MTuile const & tuile)
{
  using MouvementT::operator *;

  std::vector<MTuile*> tuiles;
  // this is a pointer
  // we want to use operator(MCoordonnees)
  // (*this) : deref this,
  MTerrain& thisRef = *this;
  for (int i = 0; i < MouvementT::size(); ++i)
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

std::vector<int> MTerrain::getImagesList(MTypeCouche typeCouche) const
{
  std::vector<int> imgs;
  for (MTuile const* tuile : tuiles)
  {
    MPartieCouche const* couche = tuile->getPartieCouche(typeCouche);
    if (couche)
    {
      imgs.push_back(couche->getId());
    }
    else
    {
      imgs.push_back(0);
    }
  }
  return imgs;
}
//------------------------------------------------------------
//=====================>Getters&Setters<======================
//------------------------------------------------------------

