/*
 * MInventaire.cpp
 *
 *  Created on: Dec 15, 2017
 *      Author: lucadeslot
 */

#include "MInventaire.hpp"

#include <algorithm>
#include <iterator>
#include <string>

#include "MItem.hpp"

MInventaire::MInventaire(int taille) :
    equipement( { }), taille(taille)
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

void MInventaire::equiperItem(MItem* item)
{
  auto it = std::find(items.begin(), items.end(), item);
  if (it != items.end())
  {
    items.erase(it, it);
  }
  if (estEquipe(item->getType()))
  {
    this->items.push_back(this->getEquipement(item->getType()));
    this->equipement[(int)item->getType()] = nullptr;
  }
  equipement[(int)item->getType()] = item;
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

void MInventaire::ajouterItem(MItem* item)
{
  if (this->items.size() < this->taille)
  {
    items.push_back(item);
  }
}

void MInventaire::supprimerItem(Id const& idItem)
{
  auto item = std::find_if(items.begin(), items.end(), [idItem](MItem* i) -> bool
  {
    return i->getId() == idItem;
  });
  items.erase(item);
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

MItem* MInventaire::getEquipement(MTypeEquipement typeEquipement)
{
  return this->equipement.at((int)typeEquipement);
}
