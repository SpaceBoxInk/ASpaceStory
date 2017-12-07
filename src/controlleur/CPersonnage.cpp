/**
 * CPersonnage.cpp
 *
 * Early optimization is the root of all evil
 *
 *  Created on: 10 nov. 2017
 *      Author: nihil
 */

#include "CPersonnage.hpp"

#include "../model/MCoordonnees.hpp"
#include "../model/MParameters.hpp"
#include "../model/MTerrain.hpp"
#include "../model/MTuile.hpp"

#include <cstdlib>
#include <string>

class MParameters;

using namespace std;

//------------------------------------------------------------
//========================>Constants<=========================
//------------------------------------------------------------

//------------------------------------------------------------
//=======================>Constructors<=======================
//------------------------------------------------------------

CPersonnage::CPersonnage(VPrimitif* vuePrincipale, MTerrain* terrain, MPersonnage* personnage) :
    vuePrincipale(vuePrincipale), personnage(personnage), terrain(terrain)
{
  setEventMethods();
  vuePrincipale->setImg(MTypeCouche::SOL, terrain->getImagesList(MTypeCouche::SOL));

  do
  {
    this->vuePrincipale->show((MCoordonnees)*personnage->getTuile());
  } while (true);
}

CPersonnage::~CPersonnage()
{
}

//------------------------------------------------------------
//=========================>Methods<==========================
//------------------------------------------------------------
void CPersonnage::setEventMethods()
{
  vuePrincipale->addObserver(this);

  // action when keyboard input
  addAction<string, char>("keyEvent", [this](char const& inputChar, Observed const&)
  {
    if (inputChar == '!')
    {
      exit(0);
    }
    if (MParameters::isMouvKey(inputChar))
    {
      personnage->deplacer(*terrain, MParameters::getMouvFromKey(inputChar));
    }

  });
}

//------------------------------------------------------------
//=====================>Getters&Setters<======================
//------------------------------------------------------------

