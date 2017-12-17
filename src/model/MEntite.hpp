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

#include <functional>
#include <string>

#include "MCompetence.hpp"
#include "MCoordonnees.hpp"

class MInventaire;

class MTerrain;
class MTuile;

class MEntite
{
//========================>Attributes<========================
private:
  std::string nom;
  MTuile* tuile;
  /**
   * en degrée,
   * 0 : en haut,
   * 90 : droite
   * -90 : gauche
   * 180 : bas
   */
  int direction;
  float taille;
  MCompetence competences;
  MInventaire* inventaire;

  std::function<void()> actionDefense;
//=======================>Constructors<=======================
public:
  MEntite(std::string const& nom, MTuile* tuile, float taille);
  // TODO: rule of five ? copyandswap
  virtual ~MEntite();

private:

//=========================>Methods<==========================
public:
  MCoordonnees getDirectionCoords();

  void deplacer(MTerrain& terrain, Mouvement const& deplacement);

  void attaquer(MTerrain& terrain);
  void seDefendre(MEntite& attaquant, int degats);
  void interagirTuile(MTerrain& terrain);

  int defenseTotale() const;
  int forceTotale() const;

private:
  bool isAccessible(MTuile const& tuile);

//=====================>Getters&Setters<======================
public:
  int getDirection() const;

  std::string const & getNom() const;

  MTuile const * getTuile() const;

  float getTaille() const;

  MCompetence const& getCompetences() const;

private:
  void setDirection(int direction);
  void setDirection(Mouvement direction);

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
  // FIXME do something for negatives or fix direction to 4 positions
  this->direction = direction % 360;
}

inline void MEntite::setDirection(Mouvement direction)
{
  this->direction = MouvementT::getDirection(direction);
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

