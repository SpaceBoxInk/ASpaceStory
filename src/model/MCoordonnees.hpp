/*
 * MCoordonnees.hpp
 *
 *  Created on: Nov 13, 2017
 *      Author: lucadeslot
 */

#ifndef SRC_MODEL_MCOORDONNEES_HPP_
#define SRC_MODEL_MCOORDONNEES_HPP_

struct Mouvement;

class MCoordonnees
{
public:
  MCoordonnees(int x, int y);

  MCoordonnees operator+(MCoordonnees const& other) const;
  MCoordonnees const& operator=(MCoordonnees const& other);
  MCoordonnees const& operator+=(MCoordonnees const& other);
  bool operator ==(MCoordonnees const & other);

  void deplacerDe(MCoordonnees const& m);

private:
  int x;
  int y;
};
struct Mouvement
{
  static MCoordonnees const HAUT;
  static MCoordonnees const BAS;
  static MCoordonnees const DROITE;
  static MCoordonnees const GAUCHE;
};

#endif /* SRC_MODEL_MCOORDONNEES_HPP_ */
