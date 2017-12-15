/*
 * MCoordonnees.hpp
 *
 *  Created on: Nov 13, 2017
 *      Author: lucadeslot
 */

#ifndef SRC_MODEL_MCOORDONNEES_HPP_
#define SRC_MODEL_MCOORDONNEES_HPP_

#include <string>


class MCoordonnees
{
public:
  MCoordonnees(int x, int y);

  MCoordonnees operator+(MCoordonnees const& other) const;
  MCoordonnees const& operator=(MCoordonnees const& other);
  MCoordonnees const& operator+=(MCoordonnees const& other);
  bool operator ==(MCoordonnees const & other) const;
//  bool operator <(MCoordonnees const & other) const;

  void deplacerDe(MCoordonnees const& m);

  int getX() const;
  int getY() const;

  std::string str() const;

private:
  int x;
  int y;
};

enum class Mouvement
{
  HAUT = 0,
  BAS,
  DROITE,
  GAUCHE,
  SIZE
};

namespace MouvementT
{
  /// retourne les coordonnees de mouvement à appliquer en fonction du mouvement
  MCoordonnees operator *(Mouvement m);

  constexpr int size()
  {
    return (int)(Mouvement::SIZE);
  }

  int getDirection(Mouvement m);

}

//==============================================================
//========================>Definitions<=========================
//==============================================================
inline int MCoordonnees::getX() const
{
  return x;
}

inline int MCoordonnees::getY() const
{
  return y;
}

#endif /* SRC_MODEL_MCOORDONNEES_HPP_ */
