/*
 * MInventaire.hpp
 *
 *  Created on: Dec 15, 2017
 *      Author: lucadeslot
 */

#ifndef SRC_MODEL_MINVENTAIRE_HPP_
#define SRC_MODEL_MINVENTAIRE_HPP_

#include <array>
#include <vector>

class MItem;
using Id = unsigned long long int;

enum class MTypeEquipement
{
  MAIN,
  CASQUE,
  PLASTRON,
  PANTALON,
  CHAUSSURE,
  SIZE, // définit le nombre de pièce d'équipement
  NONE
};

bool operator<(MTypeEquipement lh, MTypeEquipement rh);
MTypeEquipement operator-(MTypeEquipement lh, int rh);
MTypeEquipement operator++(MTypeEquipement& equip);

class MInventaire
{
  //========================>Attributes<========================

private:
  std::array<MItem*, 5> equipement;
  std::vector<MItem*> items;
  unsigned int taille;

public:

//=======================>Constructors<=======================
public:
  MInventaire(int taille);

//=========================>Methods<==========================
public:
  int getForceEquipement() const;
  int getDefenseEquipement() const;
  void supprimerItem(Id const& idItem);
  bool estEquipe(MTypeEquipement typeEquip) const;
  void ajouterItem(MItem* item);
  void equiperItem(MItem* item);
  MItem* getEquipement(MTypeEquipement typeEquipement);

  //=====================>Getters&Setters<======================

public:
  int getDegatEquipement(MTypeEquipement typeEquip) const;
  int getDefenseEquipement(MTypeEquipement typeEquip) const;

};

//------------------------------------------------------------
//=====================>Implementations<======================
//------------------------------------------------------------

#endif /* SRC_MODEL_MINVENTAIRE_HPP_ */
