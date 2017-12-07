/**
 * MTerrain.hpp
 *
 * Early optimization is the root of all evil
 *
 *  Created on: 11 nov. 2017
 *      Author: nihil
 */

#pragma once

#include "MPartieCouche.hpp"
#include "MTuile.hpp"

#include <cstdint>
#include <unordered_map>
#include <string>
#include <vector>

class MCoordonnees;

class MTerrain
{
//========================>Attributes<========================
private:
  static std::unordered_map<std::uint8_t, MPartieCouche> solsType;
  static std::unordered_map<std::uint8_t, MPartieCouche> elementsType;
  static std::unordered_map<std::uint8_t, MPartieCouche> cielsType;
  static MCoordonnees tailleMax;

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

  std::vector<std::string const*> getImagesList(MTypeCouche typeCouche);


  MCoordonnees getCoords(int index);
private:
  static void loadSpecificPath(std::string fichier, MTypeCouche const& type);
//=====================>Getters&Setters<======================
public:
  static MCoordonnees getTailleMax();

private:
  static std::unordered_map<uint8_t, MPartieCouche>& getTypeList(
      MTypeCouche const& typeCouche);
};

inline MCoordonnees MTerrain::getTailleMax()
{
  return tailleMax;
}
