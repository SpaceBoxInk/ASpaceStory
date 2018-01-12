/**
 * MTuile.hpp
 *
 * Early optimization is the root of all evil
 *
 *  Created on: 10 nov. 2017
 *      Author: nihil
 */

#pragma once

#include "MAssException.hpp"
#include "MCoordonnees.hpp"
#include "MEntite.hpp"
#include "MItem.hpp"
#include "MPartieCouche.hpp"

#include <array>
#include <vector>

class VInventaireInterface;

class MEntite;

/**
 * Représente une partie du #MTerrain,\
 * et permet de stocker une entité,
 * des objets, et des couches(sol, elements, ciel)
 */
class MTuile
{
//========================>Attributes<========================
private:
  /**
   * pour representer le sol,
   * l'endroit ou l'on se déplace (elements)
   * et le ciel\
   */
  std::array<MPartieCouche*, 3> couches;
  std::vector<MItem*> items;
  VInventaireInterface* vItems;
  MCoordonnees position;

  MEntite* entite;

//=======================>Constructors<=======================
public:
  MTuile(MCoordonnees const& position, MPartieCouche const& couche);
  /**
   * constructeur de recopie supprimé\
   * on ne veut pas pouvoir copier la tuile
   */
  MTuile(MTuile const&) = delete;
  MTuile const& operator=(MTuile const&) = delete;
  // TODO: rule of five ? copyandswap
  virtual ~MTuile();

private:

//=========================>Methods<==========================
public:
  operator MCoordonnees() const;

  float getPlaceDispo() const;

  bool isAdjacente(MTuile const& tuileOther) const;
  bool deplacerEntiteVers(MTuile& tuileDst);

  void interagirTuile(MEntite* entite);
  void mine(MEntite* entite, int item); // replace By item
  void addItem(MItem* item);
  void addInventaire(MCoordonnees taille);
private:
  float getPlaceDispoOn(MTypeCouche const& typeCouche) const;

//=====================>Getters&Setters<======================
public:
  MCoordonnees const & getPosition() const;
  void deletePartieCouche(MTypeCouche typeCouche);
  MEntite* getEntite();
  MEntite const* getEntite() const;
  bool isEntitePresente() const;
  void placeEntite(MEntite* entite);


  MPartieCouche* getPartieCouche(MTypeCouche type);
  bool hasPartieCouche(MTypeCouche type) const;
  MPartieCouche const* getPartieCouche(MTypeCouche type) const;
  void setPartieCouche(MPartieCouche const& couche);

  VInventaireInterface* getInventaire();
private:
};
//------------------------------------------------------------
//=====================>Implementations<======================
//------------------------------------------------------------

/**
 * Opérateur de cast
 * permet de caster la tuile en position:\
 * (#MCoordonnees)tuile
 * @return la position de la tuile
 */
inline MTuile::operator MCoordonnees() const
{
  return getPosition();
}

inline MCoordonnees const& MTuile::getPosition() const
{
  return position;
}

inline MEntite* MTuile::getEntite()
{
  return entite;
}

/**
 *
 * @retval true si une entité est sur la tuile
 */
inline bool MTuile::isEntitePresente() const
{
  return entite;
}

/**
 *
 * @param type le type de la couche voulu
 * @return la couche du type spécifié (modifiable)
 */
inline MPartieCouche* MTuile::getPartieCouche(MTypeCouche type)
{
  return couches.at((int)type);
}



/**
 *
 * @param type le type de la couche voulu
 * @return la couche du type spécifié (NON modifiable)
 */
inline MPartieCouche const* MTuile::getPartieCouche(MTypeCouche type) const
{
  return couches.at((int)type);
}

inline void MTuile::placeEntite(MEntite* entite)
{
  if (this->entite)
  {
    throw MExceptionEntiteDejaCreee(this->entite->getNom());
  }
  this->entite = entite;
  for (int i = 0; i < (int)MTypeCouche::SIZE; ++i)
  {
    if (getPartieCouche((MTypeCouche)i))
    {
      getPartieCouche((MTypeCouche)i)->passageDe(entite);
    }
  }
}

