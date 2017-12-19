/*
 * MCoordonnees.cpp
 *
 *  Created on: Nov 13, 2017
 *      Author: lucadeslot
 */

#include "MCoordonnees.hpp"

#include <array>
#include <vector>

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

bool MCoordonnees::operator ==(MCoordonnees const & other) const
{
  return (other.x == this->x) and (other.y == this->y);
}

void MCoordonnees::deplacerDe(MCoordonnees const& m)
{
  *this += m;
}

std::string MCoordonnees::str() const
{
  using namespace std;
  return "(" + to_string(x) + "; " + to_string(y) + ")";
}

namespace MouvementT
{
  MCoordonnees operator *(Mouvement m)
  {
    static std::vector<MCoordonnees> const mouvements = { MCoordonnees(0, -1), // HAUT 0 -> (0/90) % 2, (0/90-1)%2
    MCoordonnees(0, 1), // BAS 180 -> (180/90) % 2, (180/90-1)
    MCoordonnees(1, 0), // DROITE 90 -> (90/90) % 2, (90/90-1)
    MCoordonnees(-1, 0) // GAUCHE -90 -> (dir/90) % 2,  (dir/90-1) %2
        };

    return mouvements.at((int)m);
  }

}

