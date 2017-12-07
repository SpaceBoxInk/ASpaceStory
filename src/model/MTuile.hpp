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

class MTuile
{
//========================>Attributes<========================
private:
  std::array<MPartieCouche*, 3> couches;
  MCoordonnees position;

  MEntite* entite;
//=======================>Constructors<=======================
public:
  MTuile(MCoordonnees const& position, std::string nameCoucheSol, std::string fichierImg,
         float placeDispoSol);
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
  void setPartieCouche(MTypeCouche type, std::string name, std::string fichierImg,
                       float placeDispo);
private:
};
//------------------------------------------------------------
//=====================>Implementations<======================
//------------------------------------------------------------

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

inline bool MTuile::isEntitePresente()
{
  return entite;
}

inline MPartieCouche* MTuile::getPartieCouche(MTypeCouche type)
{
  return couches.at((int)type);
}

inline MPartieCouche const* MTuile::getPartieCouche(MTypeCouche type) const
{
  return couches.at((int)type);
}


inline void MTuile::placeEntite(MEntite* entite)
{
  this->entite = entite;
}

