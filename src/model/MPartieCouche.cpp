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

MPartieCouche::MPartieCouche(int id, MTypeCouche type, std::string name,
                             std::string fichierImg,
                             float placeDispo) :
    id(id), type(type), name(name), fichierImg(fichierImg), placeDispo(placeDispo)
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

std::string const& MPartieCouche::getFichierImg() const
{
  return fichierImg;
}

float MPartieCouche::getPlaceDispo() const
{
  return placeDispo;
}
