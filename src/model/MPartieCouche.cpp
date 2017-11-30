/**
 * @file MPartieCouche.cpp
 *
 * Early optimization is the root of all evil
 *
 *  @date 23 nov. 2017
 *  @author FederAndInk
 *  @brief TODO complete
 */

#include "MPartieCouche.hpp"

//------------------------------------------------------------
//========================>Constants<=========================
//------------------------------------------------------------

//------------------------------------------------------------
//=======================>Constructors<=======================
//------------------------------------------------------------

MPartieCouche::MPartieCouche(MTypeCouche type, std::string name, float placeDispo)
{
}

MPartieCouche::~MPartieCouche()
{
}

//------------------------------------------------------------
//=========================>Methods<==========================
//------------------------------------------------------------

bool MPartieCouche::isTypeOf(MTypeCouche type) const
{
  return getType() == type;
}
//------------------------------------------------------------
//=====================>Getters&Setters<======================
//------------------------------------------------------------
MTypeCouche const& MPartieCouche::getType() const
{
  return type;
}

std::string const& MPartieCouche::getName() const
{
  return name;
}

float MPartieCouche::getPlaceDispo() const
{
  return placeDispo;
}
