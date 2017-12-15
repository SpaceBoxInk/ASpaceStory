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
#include "MTerrain.hpp"
#include "MTuile.hpp"

//------------------------------------------------------------
//========================>Constants<=========================
//------------------------------------------------------------

//------------------------------------------------------------
//=======================>Constructors<=======================
//------------------------------------------------------------

MEntite::MEntite(std::string const& nom, MTuile* tuile, float taille) :
    nom(nom), tuile(tuile), direction(0), taille(taille)
{
  tuile->placeEntite(this);
}

MEntite::~MEntite()
{
}

//------------------------------------------------------------
//=========================>Methods<==========================
//------------------------------------------------------------
MCoordonnees MEntite::getDirectionCoords()
{
  int dir = (direction / 90);
  return MCoordonnees(dir % 2, (dir - 1) % 2);
}

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

void MEntite::interagirTuile(MTerrain& terrain)
{
  try
  {
    MTuile& tuileInt = terrain(tuile->getPosition() + getDirectionCoords());
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
//------------------------------------------------------------
//=====================>Getters&Setters<======================
//------------------------------------------------------------

