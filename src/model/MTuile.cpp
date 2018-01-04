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
#include "MPartieCoucheElement.hpp"

#include <algorithm>
#include <utility>

//------------------------------------------------------------
//========================>Constants<=========================
//------------------------------------------------------------

//------------------------------------------------------------
//=======================>Constructors<=======================
//------------------------------------------------------------

/**
 * @param position la position de la tuile sur le #MTerrain
 * @param id l'id de la couche sol (définie dans la solList)
 * @param nameCoucheSol le nom de la couche sol de la tuile
 * @param fichierImg le nom du fichier image de la COUCHE SOL
 * @param placeDispoSol sa place disponible
 */
MTuile::MTuile(MCoordonnees const& position, MPartieCouche const& couche) :
    couches( { }), position(position), entite(nullptr)
{
  if (couche.isTypeOf(MTypeCouche::SOL))
  {
    setPartieCouche(couche);
  }
  else 
  {
    throw MExceptionInvalidTypeCouche();
  }
}

MTuile::~MTuile()
{
  for (unsigned int i = 0; i < couches.size(); ++i)
  {
    deletePartieCouche((MTypeCouche)i);
  }
}

/**
 *
 * @return la place total disponible sur la TUILE\
 * en fonction des différentes #MPartieCouche
 */
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

/**
 *
 * @param tuileOther la tuile à comparer avec this
 * @retval true si tuileOther est à coté de la tuile this (diagonales non comprises)
 */
bool MTuile::isAdjacente(MTuile const & tuileOther) const
{
  using MouvementT::operator *;
  using std::rel_ops::operator !=;

  int i = 0;
  while (i < MouvementT::size()
      && *((Mouvement)i) + this->getPosition() != tuileOther.getPosition())
  {
    ++i;
  }
  return i < MouvementT::size();
}

/**
 * déplace l'entite de la tuile this vers la tuile tuileDst
 * @param tuileDst la tuile de destination de l'entité
 * @retval true si l'entité à été déplacée
 */
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
// SEE : we can throw
  return false;
}

/**
 * permet de déclancher les effet de la tuile
 * @param entite entité interagissant
 */
void MTuile::interagirTuile(MEntite* entite)
{
  for (int i = 0; i < (int)MTypeCouche::SIZE; ++i)
  {
    if (getPartieCouche((MTypeCouche)i))
    {
      getPartieCouche((MTypeCouche)i)->declenchementDe(entite);
    }
  }
}

float MTuile::getPlaceDispoOn(MTypeCouche const & typeCouche) const
{
  if (couches.at((int)typeCouche))
  {
    return couches.at((int)typeCouche)->getPlaceDispo();
  }
  return MPartieCouche::PLACE_MAX;
}

void MTuile::addItem(MItem* item)
{
  this->items.push_back(item);
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

void MTuile::mine(MEntite* entite, int item)
{
  MPartieCouche* elem = getPartieCouche(MTypeCouche::ELEMENT);
  if (elem && elem->getMiningLevel() >= 0 && item >= elem->getMiningLevel())
  {
    elem->mine(entite, item);
    deletePartieCouche(MTypeCouche::ELEMENT);
  }
}

/**
 * @param id l'id définie dans la *List (eg: solList), permet de récupérer une image en fonction d'une couleur indéxée (gimp ^^)
 * @param type le type de la couche (sol, element, ciel)
 * @param name le nom (eg: montagne, herbe)
 * @param fichierImg doit être carré
 * @param placeDispo de 0 à 1 définie la place qu'il y a sur cette couche
 */
void MTuile::setPartieCouche(MPartieCouche const& couche)
{
  if (couches.at((int)couche.getType()))
  {
    deletePartieCouche(couche.getType());
  }
  if (couche.isTypeOf(MTypeCouche::ELEMENT))
  {
    couches[(int)couche.getType()] = new MPartieCoucheElement(
        dynamic_cast<MPartieCoucheElement const&>(couche));
  }
  else
  {
    couches[(int)couche.getType()] = new MPartieCouche(couche);
  }
}

