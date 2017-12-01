/*
 * MCoordonnees.cpp
 *
 *  Created on: Nov 13, 2017
 *      Author: lucadeslot
 */

#include "MCoordonnees.hpp"

// Constants
MCoordonnees const Mouvement::HAUT(0, -1);
MCoordonnees const Mouvement::BAS(0, 1);
MCoordonnees const Mouvement::DROITE(1, 0);
MCoordonnees const Mouvement::GAUCHE(-1, 0);

// Methods
/**
 *
 * @param x
 * @param y
 */
MCoordonnees::MCoordonnees(int x, int y) :
    x(x), y(y)
{
}

MCoordonnees MCoordonnees::operator +(MCoordonnees const & other) const
{
  return MCoordonnees(this->x + other.x, this->y + other.y);
}

MCoordonnees const& MCoordonnees::operator =(MCoordonnees const & other)
{
  this->x = other.x;
  this->y = other.y;
  return *this;
}

MCoordonnees const & MCoordonnees::operator +=(MCoordonnees const & other)
{
  return *this = other + *this;
}

bool MCoordonnees::operator ==(MCoordonnees const & other)
{
  return (other.x == this->x) and (other.y == this->y);
}

void MCoordonnees::deplacerDe(MCoordonnees const& m)
{
  *this += m;
}
