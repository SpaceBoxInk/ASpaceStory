/*
 * MItem.hpp
 *
 *  Created on: Dec 15, 2017
 *      Author: lucadeslot
 */

#ifndef SRC_MODEL_MITEM_HPP_
#define SRC_MODEL_MITEM_HPP_


#include "MInventaire.hpp"
#include "MObjetTexture.hpp"

#include <string>

class MItem : public MObjetTexture
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
  MItem(std::string const& texture);

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
