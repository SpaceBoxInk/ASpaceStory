/*
 * MItem.hpp
 *
 *  Created on: Dec 15, 2017
 *      Author: lucadeslot
 */

#ifndef SRC_MODEL_MITEM_HPP_
#define SRC_MODEL_MITEM_HPP_


#include <string>

#include "MInventaire.hpp"

class MItem
{
  //========================>Attributes<========================
private:
  std::string nom;
  MTypeEquipement type;
  std::string description;
  int degats;
  int protection;


  //=======================>Constructors<=======================
public:
  MItem();

  //=========================>Methods<==========================
public:
  int getDegats() const;
  int getProtection() const;

  //=====================>Getters&Setters<======================



  //------------------------------------------------------------
  //=====================>Implementations<======================
  //------------------------------------------------------------
};

#endif /* SRC_MODEL_MITEM_HPP_ */
