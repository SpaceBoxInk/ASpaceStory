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
#include "MCoordonnees.hpp"
#include "MInventaire.hpp"
#include "MThreads.hpp"

//------------------------------------------------------------
//========================>Constants<=========================
//------------------------------------------------------------

//------------------------------------------------------------
//=======================>Constructors<=======================
//------------------------------------------------------------

MPartieCoucheElement::MPartieCoucheElement(Id ID, MTypeCouche type, std::string name,
                                           std::string fichierImg, float placeDispo,
                                           int miningLevel) :
    MPartieCouche(ID, type, name, fichierImg, placeDispo),
    miningLevel(miningLevel),
    actionMining(
        new std::function<void(MEntite* entite, int item, int xMined, int yMined)>(nullptr))
{
}

MPartieCoucheElement::MPartieCoucheElement(MPartieCoucheElement const & other) :
    MPartieCouche(other), miningLevel(other.miningLevel), actionMining(other.actionMining)
{
}

MPartieCoucheElement& MPartieCoucheElement::operator =(MPartieCoucheElement const & other)
{
  MPartieCouche::operator =(other);
  miningLevel = other.miningLevel;
  actionMining = other.actionMining;
  return *this;
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
    MThreads::parallelize(*actionMining, entite, item, minedCoords.getX(), minedCoords.getY());
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
