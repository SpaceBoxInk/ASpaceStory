/*
 * VInventory.hpp
 *
 *  Created on: 4 janv. 2018
 *      Author: lordofkawaiii
 */

#pragma once
#include "VInventaireInterface.hpp"
#include "VItem.hpp"
#include "vector"
#include "ImagePanel.hpp"

class VInventory : public VInventaireInterface, public wxFrame
{
//========================>Attributes<========================
private:
  std::vector<VItem*> items; //vide au debut
//=======================>Constructors<=======================
public:
  VInventory(wxString const & title, MCoordonnees coord);
  // TODO: rule of five ? copyandswap
  virtual ~VInventory();

  void addObjInv(unsigned long long id, std::string name, std::string description,
                 std::string image, int position = -1) override;
  void delObjInv(unsigned long long id) override;
  void show(bool show) override;

private:

//=========================>Methods<==========================
public:

private:

//=====================>Getters&Setters<======================
public:

private:

};
