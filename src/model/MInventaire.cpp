/*
 * MInventaire.cpp
 *
 *  Created on: Dec 15, 2017
 *      Author: lucadeslot
 */

#include "MInventaire.hpp"
#include "MItem.hpp"


MInventaire::MInventaire()
{
  // TODO : change that
  MItem* a1 = new MItem();
  MItem* a2 = new MItem();
  MItem* a3 = new MItem();
  MItem* a4 = new MItem();
  MItem* a5 = new MItem();
  equipement =
  { a1, a2, a3, a4, a5};
}

int MInventaire::getDegatEquipement(MTypeEquipement typeEquip) const
{
  return this->equipement.at((int)typeEquip)->getDegats();
}

int MInventaire::getDefenseEquipement(MTypeEquipement typeEquip) const
{
  return this->equipement.at((int)typeEquip)->getProtection();
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
  return this->equipement.at((int)typeEquip);
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

MTypeEquipement operator ++(MTypeEquipement equip)
{
  return (MTypeEquipement)((int)equip + 1);
}

