/*
 * MInventaire.cpp
 *
 *  Created on: Dec 15, 2017
 *      Author: lucadeslot
 */

#include "MInventaire.hpp"
#include "MItem.hpp"


MInventaire::MInventaire() :
    equipement( { })
{
}

int MInventaire::getDegatEquipement(MTypeEquipement typeEquip) const
{
  if (estEquipe(typeEquip))
  {
    return this->equipement.at((int)typeEquip)->getDegats();
  }
  return 0;
}

int MInventaire::getDefenseEquipement(MTypeEquipement typeEquip) const
{
  if (estEquipe(typeEquip))
  {
    return this->equipement.at((int)typeEquip)->getProtection();
  }
  return 0;
}

int MInventaire::getForceEquipement() const
{
  int forceTotale = 0;
  for (MTypeEquipement i = MTypeEquipement::MAIN; i < MTypeEquipement::SIZE - 1; ++i)
  {
    if (estEquipe(i))
    {
      forceTotale = forceTotale + getDegatEquipement(i);
    }
  }
  return forceTotale;
}

int MInventaire::getDefenseEquipement() const
{
  int defenseTotale = 0;
  for (MTypeEquipement i = MTypeEquipement::MAIN; i < MTypeEquipement::SIZE - 1; ++i)
  {
    if (estEquipe(i))
    {
      defenseTotale = defenseTotale + getDefenseEquipement(i);
    }
  }
  return defenseTotale;
}

bool MInventaire::estEquipe(MTypeEquipement typeEquip) const
{
  return typeEquip < MTypeEquipement::SIZE && this->equipement.at((int)typeEquip);
}

//===========================================================
//====================>MTypeEquipement<======================
//===========================================================

bool operator <(MTypeEquipement lh, MTypeEquipement rh)
{
  return (int)lh < (int)rh;
}


MTypeEquipement operator -(MTypeEquipement lh, int rh)
{
  return (MTypeEquipement)((int)lh - rh);
}

MTypeEquipement operator ++(MTypeEquipement& equip)
{
  return equip = (MTypeEquipement)((int)equip + 1);
}

