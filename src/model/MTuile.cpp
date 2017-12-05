/**
 * MTuile.cpp
 *
 * Early optimization is the root of all evil
 *
 *  Created on: 10 nov. 2017
 *      Author: nihil
 */

#include "MTuile.hpp"

//------------------------------------------------------------
//========================>Constants<=========================
//------------------------------------------------------------

//------------------------------------------------------------
//=======================>Constructors<=======================
//------------------------------------------------------------

MTuile::MTuile(MPartieCouche* sol, MPartieCouche* element, MPartieCouche* ciel)
{
  setPartieCouche(sol);
  setPartieCouche(element);
  setPartieCouche(ciel);
}

MTuile::~MTuile()
{
  for (int i = 0; i < couches.size(); ++i)
  {
    deletePartieCouche((MTypeCouche)i);
  }
}

//------------------------------------------------------------
//=========================>Methods<==========================
//------------------------------------------------------------

//------------------------------------------------------------
//=====================>Getters&Setters<======================
//------------------------------------------------------------
void MTuile::deletePartieCouche(MTypeCouche typeCouche)
{
  if (couches[(int)typeCouche])
  {
    delete couches[(int)typeCouche];
    couches[(int)typeCouche] = nullptr;
  }
}

/**
 *
 * @param couche la couche de la tuile à set
 */
void MTuile::setPartieCouche(MPartieCouche* couche)
{
  if (couche)
  {
    couches[(int)couche->getType()] = couche;
  }
}

