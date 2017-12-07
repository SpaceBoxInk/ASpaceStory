/**
 * MTuile.cpp
 *
 * Early optimization is the root of all evil
 *
 *  Created on: 10 nov. 2017
 *      Author: nihil
 */

#include "MTuile.hpp"
#include "MAssException.hpp"

#include <algorithm>
#include <utility>

//------------------------------------------------------------
//========================>Constants<=========================
//------------------------------------------------------------

//------------------------------------------------------------
//=======================>Constructors<=======================
//------------------------------------------------------------

MTuile::MTuile(MCoordonnees const& position,
               std::string nameCoucheSol, std::string fichierImg,
               float placeDispoSol) :
    couches( { nullptr }), position(position), entite(nullptr)
{
  setPartieCouche(MTypeCouche::SOL, nameCoucheSol, fichierImg, placeDispoSol);
}

MTuile::~MTuile()
{
  for (unsigned int i = 0; i < couches.size(); ++i)
  {
    deletePartieCouche((MTypeCouche)i);
  }
}

float MTuile::getPlaceDispo() const
{
  if (entite)
  {
    return 0;
  }
  else
  {
    // on prend la place dispo minimum de toutes les couches
    return std::min(
        { getPlaceDispoOn(MTypeCouche::SOL), getPlaceDispoOn(MTypeCouche::ELEMENT),
            getPlaceDispoOn(MTypeCouche::CIEL) });
  }
}

//------------------------------------------------------------
//=========================>Methods<==========================
//------------------------------------------------------------

bool MTuile::isAdjacente(MTuile const & tuileOther)
{
  using MouvementT::operator *;
  using std::rel_ops::operator !=;

  int i = 0;
  while (i < (int)Mouvement::SIZE
      && *((Mouvement)i) + this->getPosition() != tuileOther.getPosition())
  {
    ++i;
  }
  return i < (int)Mouvement::SIZE;
}

bool MTuile::deplacerEntiteVers(MTuile& tuileDst)
{
  if (!isEntitePresente())
  {
    throw MExceptionEntiteNonPresente(this);
  }
  // SEE : pas besoin d'un delta car taille de l'entite << placeDispo de la tuile
  if (entite->getTaille() <= tuileDst.getPlaceDispo())
  {
    tuileDst.placeEntite(entite);
    entite = nullptr;
    return true;
  }
  return false;
}

float MTuile::getPlaceDispoOn(MTypeCouche const & typeCouche) const
{
  if (couches.at((int)typeCouche))
  {
    return couches.at((int)typeCouche)->getPlaceDispo();
  }
  return MPartieCouche::PLACE_MAX;
}

//------------------------------------------------------------
//=====================>Getters&Setters<======================
//------------------------------------------------------------
void MTuile::deletePartieCouche(MTypeCouche typeCouche)
{
  if (couches[(int)typeCouche])
  {
    delete couches[(int)typeCouche];
    couches[(int)typeCouche] = nullptr;
  }
}

/**
 *
 * @param couche la couche de la tuile à set
 */
void MTuile::setPartieCouche(MTypeCouche type, std::string name, std::string fichierImg,
                             float placeDispo)
{
  if (couches.at((int)type))
  {
    deletePartieCouche(type);
  }
  couches[(int)type] = new MPartieCouche(type, name, fichierImg, placeDispo);
}

