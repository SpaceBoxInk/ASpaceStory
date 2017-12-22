/**
 * @file MEntite.cpp
 *
 * Early optimization is the root of all evil
 * DRY ! Don't repeat yourself
 *
 *  @date 3 déc. 2017
 *  @author FederAndInk
 *  @brief TODO complete
 */

#include "MEntite.hpp"

#include "MAssException.hpp"
#include "MInventaire.hpp"
#include "MTerrain.hpp"
#include "MTuile.hpp"

//------------------------------------------------------------
//========================>Constants<=========================
//------------------------------------------------------------

//------------------------------------------------------------
//=======================>Constructors<=======================
//------------------------------------------------------------

MEntite::MEntite(std::string const& nom, MTuile* tuile, float taille) :
    nom(nom), direction(0), taille(taille), actionDefense(nullptr)
{
  setTuile(tuile);
}

MEntite::~MEntite()
{
}

//------------------------------------------------------------
//=========================>Methods<==========================
//------------------------------------------------------------
/**
 * Deplace l'entite de deplacement sur le terrain\
 * eg: avec deplacement == Mouvement::HAUT,\
 * l'entite va se deplacer d'une case vers le haut
 *
 * @param terrain le terrain où se deplace l'entite
 * @param deplacement le deplacement voulu
 */
void MEntite::deplacer(MTerrain& terrain, Mouvement const & deplacement)
{
  // on a redefinie l'operator* pour Mouvement
  // on peut avoir le deplacement (x, y) en fonction d'un element de l'enum ! :)
  using MouvementT::operator *;

  // on set la direction peut importe si on peut aller sur la case
  setDirection(deplacement);
  try
  {
    // on prend la position de la tuile, puis on ajoute le deplacement
    // cela permet d'avoir la position (x, y) de la tuile où se deplacer
    // on demande au terrain d'avoir la tuile : operator()
    // ~~~~~~~~~~~~~~~~~~~~~~~v-----------------------------------v~
    MTuile& tuileDst = terrain(tuile->getPosition() + *deplacement);

    if (isAccessible(tuileDst))
    {
      if (tuile->deplacerEntiteVers(tuileDst))
      {
        tuile = &terrain(tuile->getPosition() + *deplacement);
      }
    }
  }
  catch (MExceptionOutOfTerrain& e)
  {
  }
}

void MEntite::seDefendre(MEntite& attaquant, int degats)
{
  this->competences.enleveVie(degats - defenseTotale());
  if (actionDefense)
  {
    actionDefense(attaquant.getNom(), degats);
  }
}

void MEntite::interagirTuile(MTerrain& terrain)
{
  try
  {
    MTuile& tuileInt = terrain(
        tuile->getPosition() + MouvementT::getDirectionCoords(direction));
    tuileInt.interagirTuile(this);
  }
  catch (MExceptionOutOfTerrain& e)
  {
  }
}

bool MEntite::isAccessible(MTuile const & tuile)
{
  return this->tuile->isAdjacente(tuile);
}

void MEntite::attaquer(MTerrain& terrain)
try
{
  MEntite* entiteCible = terrain(
      getTuile()->getPosition() + MouvementT::getDirectionCoords(direction)).getEntite(); // FIXME : add direction
  if (entiteCible)
  {
    entiteCible->seDefendre(*this, this->forceTotale());
  }
}
catch (MExceptionOutOfTerrain& e)
{
}

int MEntite::forceTotale() const
{
  return competences.getForce() + inventaire.getForceEquipement();
}

int MEntite::defenseTotale() const
{
  return inventaire.getDefenseEquipement();
}
//------------------------------------------------------------
//=====================>Getters&Setters<======================
//------------------------------------------------------------

MCompetence const& MEntite::getCompetences() const
{
  return this->competences;
}

void MEntite::setTuile(MTuile* tuile)
{
  this->tuile = tuile;
  if (tuile)
  {
    tuile->placeEntite(this);
  }
}

void MEntite::setDirection(int direction)
{
  // FIXME do something for negatives or fix direction to 4 positions
  if (direction != 0 || direction != 90 || direction != -90 || direction != 180)
  {
    throw MAssException("Direction not viable ! : " + std::to_string(direction));
  }
  this->direction = direction % 360;
}
