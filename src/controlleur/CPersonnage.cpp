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

#include <cstdlib>

class MParameters;

using namespace std;

//------------------------------------------------------------
//========================>Constants<=========================
//------------------------------------------------------------

//------------------------------------------------------------
//=======================>Constructors<=======================
//------------------------------------------------------------

CPersonnage::CPersonnage(VPrimitif* vuePrincipale, MTerrain* terrain) :
    vuePrincipale(vuePrincipale), terrain(terrain), quit(false)
{
  setEventMethods();
}

CPersonnage::~CPersonnage()
{
  if (personnage)
  {
    delete personnage;
    personnage = nullptr;
  }
}

void CPersonnage::launchPersonnage()
{
  vuePrincipale->setImg(MTypeCouche::SOL, terrain->getImagesList(MTypeCouche::SOL));
  do
  {
    this->vuePrincipale->show((MCoordonnees)*personnage->getTuile());
  } while (!quit);
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
          quit=true;
        }
        if (MParameters::isMouvKey(inputChar))
        {
          personnage->deplacer(*terrain, MParameters::getMouvFromKey(inputChar));
        }
        else if (MParameters::isActionKey(inputChar))
        {
          switch (MParameters::getActionFromKey(inputChar))
          {
            case MActionsKey::INTERACT_ENV_KEY:
            personnage->interagirTuile(*terrain);
            break;
            default:
            break;
          }
        }

      });
}

//------------------------------------------------------------
//=====================>Getters&Setters<======================
//------------------------------------------------------------

