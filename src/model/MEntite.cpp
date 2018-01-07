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
#include "MEvents.hpp"
#include "MItem.hpp"
#include "MTerrain.hpp"
#include "MTuile.hpp"

//------------------------------------------------------------
//========================>Constants<=========================
//------------------------------------------------------------

//------------------------------------------------------------
//=======================>Constructors<=======================
//------------------------------------------------------------

MEntite::MEntite(std::string const& nom, std::string const& texture, MTuile* tuile,
                 float taille) :
    MObjetTexture(texture), nom(nom), tuile(nullptr), direction(Mouvement::DROITE),
    taille(0),
    inventaire(70),
    actionDefense(nullptr), actionInteraction(nullptr)
{
  setTaille(taille);
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
        setChanged();
        notifyObservers(MModelEvents::ENTITY_MOVED, *this);
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

/**
 * interagi avec la tuile dans la #direction de l'entité\
 * ex: appuie sur un bouton
 * @param terrain le terrain ou est l'entité
 */
void MEntite::interagirTuile(MTerrain& terrain)
try
{
  using MouvementT::operator *;
  MTuile& tuileInt = terrain(tuile->getPosition() + *direction);
  tuileInt.interagirTuile(this);
}
catch (MExceptionOutOfTerrain& e)
{
}

void MEntite::interagirEntite(MTerrain& terrain)
try
{
  using MouvementT::operator *;
  MEntite* entite = terrain(getTuile()->getPosition() + *direction).getEntite();
  if (entite && entite->actionInteraction)
  {
    entite->actionInteraction(*this);
  }
}
catch (MExceptionOutOfTerrain& e)
{
}

/**
 * mine la #MTuile devant l'entite (la couche 1 : #MTypeCouche::ELEMENT)
 * @param terrain le terrain ou est l'entité
 */
void MEntite::mine(MTerrain& terrain)
try
{
  using namespace MouvementT;
  MTuile& tuileInt = terrain(tuile->getPosition() + *direction);
  tuileInt.mine(this, getMiningPower());
}
catch (MExceptionOutOfTerrain& e)
{
}

void MEntite::equipe(Id idItem)
{
  inventaire.equipe(idItem);
}

bool MEntite::isAccessible(MTuile const & tuile) const
{
  return this->tuile->isAdjacente(tuile);
}

void MEntite::attaquer(MTerrain& terrain)
try
{
  using MouvementT::operator *;
  MEntite* entiteCible = terrain(getTuile()->getPosition() + *direction).getEntite();
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

void MEntite::addItemToInventaire(MItem* item)
{
  this->inventaire.ajouterItem(item);
}

void MEntite::utiliserObjet()
{
  if (inventaire.getEquipement(MTypeEquipement::MAIN))
  {
    inventaire.getEquipement(MTypeEquipement::MAIN)->utilisation(this);
  }
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
  if (this->tuile && tuile)
  {
    if (this->tuile->deplacerEntiteVers(*tuile))
    {
      this->tuile = tuile;
    }
  }
  else if (tuile)
  {
    tuile->placeEntite(this);
    this->tuile = tuile;
  }
}

MInventaire& MEntite::getInventaire()
{
  return this->inventaire;
}

int MEntite::getMiningPower()
{
  if (inventaire.estEquipe(MTypeEquipement::MAIN))
  {
    return inventaire.getEquipement(MTypeEquipement::MAIN)->getMiningLevel();
  }
  return 0;
}
