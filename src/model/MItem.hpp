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

class MEntite;

class MItem
{
  //========================>Attributes<========================
private:
  std::string nom;
  MTypeEquipement type;
  std::string description;
  int degats;
  int protection;
  bool supprimable;
  Id id;
  static Id nextId;
  std::function<void(std::string entite)> actionUtilisation;

  //=======================>Constructors<=======================
public:
  MItem(std::string nom, std::string description, MTypeEquipement type = MTypeEquipement::MAIN,
        int degats = 0,
        int protection = 0, bool supprimable = true);

  //=========================>Methods<==========================
public:
  void utilisation(MEntite* entite);

  //=====================>Getters&Setters<======================
  std::string getNom() const;
  int getDegats() const;
  int getProtection() const;
  Id getId() const;
  void setActionUtilisation(std::function<void(std::string entite)> actionUtilisation);


  //------------------------------------------------------------
  //=====================>Implementations<======================
  //------------------------------------------------------------
};

#endif /* SRC_MODEL_MITEM_HPP_ */
