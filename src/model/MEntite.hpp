/**
 * @file MEntite.hpp
 *
 * Early optimization is the root of all evil
 * DRY ! Don't repeat yourself
 *
 *  @date 3 déc. 2017
 *  @author FederAndInk
 *  @brief TODO complete
 */

#pragma once

#include "MCoordonnees.hpp"

#include <string>

class MTerrain;
class MTuile;

class MEntite
{
//========================>Attributes<========================
private:
  std::string nom;
  MTuile* tuile;
  int direction;
  float taille;
//=======================>Constructors<=======================
public:
  MEntite(std::string const& nom, MTuile* tuile, float taille);
  // TODO: rule of five ? copyandswap
  virtual ~MEntite();

private:

//=========================>Methods<==========================
public:
  void deplacer(MTerrain& terrain, Mouvement const& deplacement);

private:
  bool isAccessible(MTuile const& tuile);

//=====================>Getters&Setters<======================
public:
  int getDirection() const;
  void setDirection(int direction);

  std::string const & getNom() const;

  MTuile const * getTuile() const;

  float getTaille() const;

private:

};
//------------------------------------------------------------
//=====================>Implementations<======================
//------------------------------------------------------------

inline int MEntite::getDirection() const
{
  return direction;
}

inline void MEntite::setDirection(int direction)
{
  this->direction = direction;
}

inline std::string const & MEntite::getNom() const
{
  return nom;
}

inline MTuile const * MEntite::getTuile() const
{
  return tuile;
}

inline float MEntite::getTaille() const
{
  return taille;
}
