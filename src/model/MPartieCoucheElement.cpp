/**
 * @file MPartieCoucheElement.cpp
 *
 * Early optimization is the root of all evil
 * DRY ! Don't repeat yourself
 *
 *  @date 20 déc. 2017
 *  @author FederAndInk
 *  @brief TODO complete
 */

#include "MPartieCoucheElement.hpp"

//------------------------------------------------------------
//========================>Constants<=========================
//------------------------------------------------------------

//------------------------------------------------------------
//=======================>Constructors<=======================
//------------------------------------------------------------

MPartieCoucheElement::MPartieCoucheElement(Id ID, MTypeCouche type, std::string name,
                                           std::string fichierImg, float placeDispo,
                                           int miningLevel) :
    MPartieCouche(ID, type, name, fichierImg, placeDispo), miningLevel(miningLevel),
    actionMining(
        new std::function<void(MEntite* entite, int item, int xMined, int yMined)>(nullptr))
{
}

MPartieCoucheElement::~MPartieCoucheElement()
{
}

//------------------------------------------------------------
//=========================>Methods<==========================
//------------------------------------------------------------
void MPartieCoucheElement::mine(MEntite* entite, int item, MCoordonnees minedCoords)
{
  if (*actionMining)
  {
    (*actionMining)(entite, item, minedCoords.getX(), minedCoords.getY());
  }
}

//------------------------------------------------------------
//=====================>Getters&Setters<======================
//------------------------------------------------------------
void MPartieCoucheElement::setActionMining(
    std::function<void(MEntite* entite, int item, int xMined, int yMined)> actionMining)
{
  *this->actionMining = actionMining;
}

void MPartieCoucheElement::unSetActionMining()
{
  *actionMining = nullptr;
}

int MPartieCoucheElement::getMiningLevel() const
{
  return miningLevel;
}