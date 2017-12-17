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
  inventaire = new MInventaire();
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
  if (competences.getVie() != 0)
  { // si l'entité est encore vivante
    this->attaquer(attaquant);
  }
  else
  {
    // TODO: je sais pas
  }
}

int MEntite::defenseTotale() const
{
int defenseTotale = 0;
for (MTypeEquipement i = MTypeEquipement::MAIN; i < MTypeEquipement::SIZE - 1; ++i)
{
  if (inventaire->estEquipe(i))
  {
      defenseTotale = defenseTotale + inventaire->getDefenseEquipement(i);
  }
}
return defenseTotale;
}

bool MEntite::isAccessible(MTuile const & tuile)
{
  return this->tuile->isAdjacente(tuile);
}

void MEntite::attaquer(MTerrain& terrain)
try
{
  MEntite* entiteCible = terrain(getTuile()->getPosition()).getEntite(); // FIXME : add direction
  if (entiteCible != nullptr)
  {
    entiteCible->seDefendre(*this, this->forceTotale());
  }
}
catch (MExceptionOutOfTerrain& e)
{
}

int MEntite::forceTotale() const
{
int forceTotale = 0;
for (MTypeEquipement i = MTypeEquipement::MAIN; i < MTypeEquipement::SIZE - 1; ++i)
{
  if (MEntite::inventaire->estEquipe(i))
  {
    forceTotale = forceTotale + MEntite::inventaire->getDegatEquipement(i);
  }
}
return forceTotale;
}
//------------------------------------------------------------
//=====================>Getters&Setters<======================
//------------------------------------------------------------


MCompetence const& MEntite::getCompetences() const
{
  return this->competences;
}

