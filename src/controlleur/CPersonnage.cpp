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
#include "../model/MEvents.hpp"
#include "../model/MParameters.hpp"
#include "../model/MPartieCouche.hpp"
#include "../model/MTerrain.hpp"
#include "../model/MTuile.hpp"
#include "../vue/AppFrameInterface.hpp"

#include <cstdlib>

class MParameters;

using namespace std;

//------------------------------------------------------------
//========================>Constants<=========================
//------------------------------------------------------------

//------------------------------------------------------------
//=======================>Constructors<=======================
//------------------------------------------------------------

CPersonnage::CPersonnage(AppFrameInterface* vuePrincipale, MTerrain* terrain) :
    vuePrincipale(vuePrincipale), terrain(terrain)
{
  setEventMethods();
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
  addAction<MUserEvents, char>(
      MUserEvents::KEY_PRESSED, [this](char const& inputChar, Observed const&)
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

