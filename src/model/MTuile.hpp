/**
 * MTuile.hpp
 *
 * Early optimization is the root of all evil
 *
 *  Created on: 10 nov. 2017
 *      Author: nihil
 */

#pragma once

#include "MCoordonnees.hpp"
#include "MEntite.hpp"
#include "MPartieCouche.hpp"

#include <array>
#include <string>

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
  MCoordonnees position;

  MEntite* entite;
//=======================>Constructors<=======================
public:
  MTuile(MCoordonnees const& position, int id, std::string nameCoucheSol,
         std::string fichierImg, float placeDispoSol);
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

  bool isAdjacente(MTuile const& tuileOther);
  bool deplacerEntiteVers(MTuile& tuileDst);
private:
  float getPlaceDispoOn(MTypeCouche const& typeCouche) const;

//=====================>Getters&Setters<======================
public:
  MCoordonnees const & getPosition() const;
  void deletePartieCouche(MTypeCouche typeCouche);
  MEntite const& getEntite() const;
  bool isEntitePresente();
  void placeEntite(MEntite* entite);

  MPartieCouche* getPartieCouche(MTypeCouche type);
  MPartieCouche const* getPartieCouche(MTypeCouche type) const;
  void setPartieCouche(int id, MTypeCouche type, std::string name, std::string fichierImg,
                       float placeDispo);
private:
};
//------------------------------------------------------------
//=====================>Implementations<======================
//------------------------------------------------------------

/**
 * Opérateur de cast
 * permet de caster la tuile en position:\
 * (#MPosition)tuile
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

inline MEntite const & MTuile::getEntite() const
{
  return *entite;
}

/**
 *
 * @retval @e true si une entité est sur la tuile
 */
inline bool MTuile::isEntitePresente()
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
  this->entite = entite;
}

