/*
 * MItem.cpp
 *
 *  Created on: Dec 15, 2017
 *      Author: lucadeslot
 */

#include "MItem.hpp"

MItem::MItem(std::string const& texture) :
    MObjetTexture(texture), nom("test"), type((MTypeEquipement)2), description("testDescr"),
    degats(3), protection(34) // TODO: contructeur de test à modifier
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
