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

MTuile::MTuile(MPartieCouche const* sol, MPartieCouche const* element,
               MPartieCouche const* ciel)
{
  setPartieCouche(sol);
  setPartieCouche(element);
  setPartieCouche(ciel);
}

MTuile::~MTuile()
{
}

//------------------------------------------------------------
//=========================>Methods<==========================
//------------------------------------------------------------

//------------------------------------------------------------
//=====================>Getters&Setters<======================
//------------------------------------------------------------
void MTuile::setPartieCouche(MPartieCouche const* couche)
{
  if (couche)
  {
    couches[(int)couche->getType()] = *couche;
  }
}

