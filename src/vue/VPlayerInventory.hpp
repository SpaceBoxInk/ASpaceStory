/*
 * VPlayerInventory.hpp
 *
 *  Created on: 5 janv. 2018
 *      Author: lordofkawaiii
 */

#pragma once

#include "VInventory.hpp"
#include "VPlayerInventaireInterface.hpp"

class VPlayerInventory : public VPlayerInventaireInterface, public VInventory
{
//========================>Attributes<========================
private:
  std::vector<VItem*> Quick;

//=======================>Constructors<=======================
public:
  VPlayerInventory(wxString const & title, MCoordonnees coord);
  // TODO: rule of five ? copyandswap
  ~VPlayerInventory();

private:

//=========================>Methods<==========================
public:
  void addObjPlayerQuickInv(unsigned long long id, std::string name, std::string description,
                            std::string image, int position = -1) override;
  void delObjInv(unsigned long long id);
private:

//=====================>Getters&Setters<======================
public:

private:

};
