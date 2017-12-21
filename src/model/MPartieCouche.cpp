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

#include <iostream>

//------------------------------------------------------------
//========================>Constants<=========================
//------------------------------------------------------------

//------------------------------------------------------------
//=======================>Constructors<=======================
//------------------------------------------------------------

MPartieCouche::MPartieCouche(MTypeCouche type, std::string name, std::string fichierImg,
                             float placeDispo) :
    type(type), name(name), fichierImg(fichierImg), placeDispo(placeDispo)
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

void MPartieCouche::passageDe(MEntite* entite)
{
  if (actionPassage)
  {
    actionPassage(entite->getNom());
  }
}

void MPartieCouche::declenchementDe(MEntite* entite)
{
  if (actionDeclenchement)
  {
    actionDeclenchement(entite->getNom());
  }
}

void MPartieCouche::mine(MEntite* entite, int item)
{
  throw std::logic_error("Cannot call mine on couche isn't ELEMENT !");
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

int MPartieCouche::getMiningLevel() const
{
  throw std::logic_error("Cannot call getMiningLevel on couche isn't ELEMENT !");
}

void MPartieCouche::setActionMining(
    std::function<void(MEntite* entite, int item)> actionMining)
{
  throw std::logic_error("Cannot call setActionMining on couche isn't ELEMENT !");
}

void MPartieCouche::unSetActionMining()
{
  throw std::logic_error("Cannot call unSetActionMining on couche isn't ELEMENT !");
}
