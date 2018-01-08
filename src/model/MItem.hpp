/*
 * MItem.hpp
 *
 *  Created on: Dec 15, 2017
 *      Author: lucadeslot
 */

#ifndef SRC_MODEL_MITEM_HPP_
#define SRC_MODEL_MITEM_HPP_

#include <functional>
#include <string>

#include "MInventaire.hpp"
#include "MObjetTexture.hpp"

#include <string>

class MEntite;

class MItem: public MObjetTexture
{
  //========================>Attributes<========================
private:
  Id id;
  static Id nextId;
  std::string nom;
  MTypeEquipement type;
  std::string description;
  int degats;
  int protection;
  bool supprimable;
  std::function<void(std::string entite)> actionUtilisation;
  int miningLevel;

  //=======================>Constructors<=======================
public:
  MItem(std::string nom, std::string const& texture, std::string description, MTypeEquipement type = MTypeEquipement::MAIN,
        int degats = 0, int protection = 0, bool supprimable = true, int miningLevel = 0);

  //=========================>Methods<==========================
public:
  void utilisation(MEntite* entite);

  bool operator ==(MItem const& other) const;

  //=====================>Getters&Setters<======================
  std::string getNom() const;
  std::string getDescription() const;
  int getDegats() const;
  int getProtection() const;
  Id getId() const;
  void setActionUtilisation(std::function<void(std::string entite)> actionUtilisation);

  MTypeEquipement getType() const;
  int getMiningLevel() const;
};
//------------------------------------------------------------
//=====================>Implementations<======================
//------------------------------------------------------------

inline MTypeEquipement MItem::getType() const
{
  return type;
}

inline std::string MItem::getDescription() const
{
  return description;
}

inline int MItem::getMiningLevel() const
{
  return miningLevel;
}

#endif /* SRC_MODEL_MITEM_HPP_ */
