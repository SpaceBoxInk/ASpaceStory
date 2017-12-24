/*
 * MItem.cpp
 *
 *  Created on: Dec 15, 2017
 *      Author: lucadeslot
 */

#include "MItem.hpp"

#include "MEntite.hpp"

Id MItem::nextId = 0;

bool MItem::operator ==(MItem const& other) const
{
  return this->getId() == other.getId();
}


MItem::MItem(std::string nom, std::string description, MTypeEquipement type,
    int degats,
             int protection, bool supprimable, int miningLevel) :
    id(nextId++), nom(nom), type(type), description(description), degats(degats),
    protection(protection), supprimable(supprimable), actionUtilisation(nullptr),
    miningLevel(miningLevel) // TODO: contructeur de test à modifier
{
}

int MItem::getDegats() const
{
  return this->degats;
}

int MItem::getProtection() const
{
  return this->protection;
}

std::string MItem::getNom() const
{
  return this->nom;
}

Id MItem::getId() const
{
  return id;
}

void MItem::setActionUtilisation(std::function<void(std::string entite)> actionUtilisation)
{
  this->actionUtilisation = actionUtilisation;
}

void MItem::utilisation(MEntite* entite)
{
  if (actionUtilisation)
  {
    this->actionUtilisation(entite->getNom());
  }
}

