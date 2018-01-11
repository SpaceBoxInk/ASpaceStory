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

#include "MAssException.hpp"
#include "MCompetence.hpp"
#include "MCoordonnees.hpp"
#include "MInventaire.hpp"
#include "MObjetTexture.hpp"

#include "../outils/ObserverPattern/Observed.hpp"

#include <functional>
#include <future>
#include <string>

class MItem;

class MTerrain;
class MTuile;

class MEntite : public MObjetTexture, public Observed
{
//========================>Attributes<========================
private:
  std::string nom;
  MTuile* tuile;
  /**
   * en degrée,
   * 0 : en haut (0),
   * 90 : droite (1)
   * 180 : bas (2)
   * -90 : gauche (3)
   */
  Mouvement direction;
  /**
   * allant de 0 à 1 pour savoir quel pourcentage d'une tuile prend une entité
   */
  float taille;
  MCompetence competences;
  MInventaire inventaire;

  std::function<void(std::string entite, int degat)> actionDefense;
  std::future<void> threadDefense;
  std::function<void(MEntite const& entite)> actionInteraction;
  std::future<void> threadInteraction;
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
  void interagirEntite(MTerrain& terrain);
  void utiliserObjet();
  void mine(MTerrain& terrain);

  int defenseTotale() const;
  int forceTotale() const;
  void addItemToInventaire(MItem* item);
  void equipe(Id idItem);

private:
  bool isAccessible(MTuile const& tuile) const;

//=====================>Getters&Setters<======================
public:
  Mouvement getDirection() const;
  void setDirection(Mouvement direction);

  std::string const & getNom() const;

  MTuile const * getTuile() const;
  void setTuile(MTuile* tuile);

  float getTaille() const;
  void setTaille(float taille);

  MCompetence const& getCompetences() const;
  MInventaire& getInventaire();



  void setActionDefense(std::function<void(std::string entite, int degat)> actionDefense);
  void setActionInteraction(std::function<void(MEntite const& entite)> actionInteraction);
private:
  int getMiningPower();
};
//------------------------------------------------------------
//=====================>Implementations<======================
//------------------------------------------------------------

inline Mouvement MEntite::getDirection() const
{
  return direction;
}

inline void MEntite::setActionDefense(std::function<void(std::string, int)> actionDefense)
{
  this->actionDefense = actionDefense;
}

inline void MEntite::setActionInteraction(
    std::function<void(MEntite const& entite)> actionInteraction)
{
  this->actionInteraction = actionInteraction;
}

inline void MEntite::setDirection(Mouvement direction)
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

inline void MEntite::setTaille(float taille)
{
  if (taille < 0 || taille > 1)
  {
    throw MAssException(
        "Taille de " + std::to_string(taille) + " invalide pour l'entité" + getNom());
  }
  this->taille = taille;
}

