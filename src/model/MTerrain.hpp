/**
 * MTerrain.hpp
 *
 * Early optimization is the root of all evil
 *
 *  Created on: 11 nov. 2017
 *      Author: nihil
 */

#pragma once

#include "MCoordonnees.hpp"
#include "MPartieCouche.hpp"
#include "MTuile.hpp"

#include "../outils/ObserverPattern/Observed.hpp"

#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

class MCoordonnees;

/**
 * Le terrain est composée de tuile
 * Il sert pour les organiser, initialiser\
 * rechercher
 */
class MTerrain : public Observed
{
//========================>Attributes<========================
private:
  /**
   * map pour avoir la partie couche(lu dans les fichiers *list des tuiles)\n
   * en fonction d'un index(lu dans les fichiers .n*)
   */
  static std::unordered_map<std::uint8_t, MPartieCouche> solsType;
  static std::unordered_map<std::uint8_t, MPartieCouche> elementsType;
  static std::unordered_map<std::uint8_t, MPartieCouche> cielsType;
  /**
   * le point qui défini la taille du terrain\
   * le nombre d'element sur x et sur y
   * pour une définir x [0..3] et y [0..3] :\
   * MCoordonnees(4, 4)
   */
  static MCoordonnees taille;

  std::vector<MTuile*> tuiles;
//=======================>Constructors<=======================
public:
  MTerrain();
  // TODO: rule of five ? copyandswap
  virtual ~MTerrain();

private:

//=========================>Methods<==========================
public:
  static void loadTypes();
  void loadCouche(std::string const & fichier, MTypeCouche const & type);
  MTuile& operator()(MCoordonnees const& coord);
  MTuile& operator()(int index);
  MTuile& operator()(int x, int y);

  std::vector<MTuile*> getAdjacentes(MTuile const& tuile);

  std::vector<int> getImagesList(MTypeCouche typeCouche) const;

  MEntite* procheEntite(MCoordonnees coordonneeJoueur);
  MCoordonnees toCoords(int index);
private:
  static void loadSpecificPath(std::string fichier, MTypeCouche const& type);
//=====================>Getters&Setters<======================
public:
  static MCoordonnees getTaille();
  static void setTaille(MCoordonnees taille);

private:
  static std::unordered_map<uint8_t, MPartieCouche>& getTypeList(
      MTypeCouche const& typeCouche);
};

inline MCoordonnees MTerrain::getTaille()
{
  return taille;
}

inline void MTerrain::setTaille(MCoordonnees taille)
{
  MTerrain::taille = taille;
}
