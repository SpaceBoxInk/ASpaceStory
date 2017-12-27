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

#include "MCompetence.hpp"
#include "MCoordonnees.hpp"
#include "MInventaire.hpp"
#include "MObjetTexture.hpp"

#include <functional>
#include <string>

class MTerrain;
class MTuile;

class MEntite : public MObjetTexture
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
  MInventaire inventaire;

  std::function<void(std::string, int)> actionDefense;
//=======================>Constructors<=======================
public:
  MEntite(std::string const& nom, std::string const& texture, MTuile* tuile = nullptr,
          float taille = 1);
  // TODO: rule of five ? copyandswap
  virtual ~MEntite();

private:

//=========================>Methods<==========================
public:
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
  void setTuile(MTuile* tuile);

  float getTaille() const;
  void setTaille(float taille);

  MCompetence const& getCompetences() const;

  void setActionDefense(std::function<void(std::string, int)> actionDefense);
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

inline void MEntite::setActionDefense(std::function<void(std::string, int)> actionDefense)
{
  this->actionDefense = actionDefense;
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

inline void MEntite::setTaille(float taille)
{
  this->taille = taille;
}

