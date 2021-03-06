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
#include "../model/MRobot.hpp"
#include "../model/MTerrain.hpp"
#include "../model/MTuile.hpp"
#include "../outils/ObserverPattern/Observer.hpp"
#include "../vue/AppFrameInterface.hpp"

class MParameters;

using namespace std;

//------------------------------------------------------------
//========================>Constants<=========================
//------------------------------------------------------------

//------------------------------------------------------------
//=======================>Constructors<=======================
//------------------------------------------------------------

CPersonnage::CPersonnage(AppFrameInterface* vuePrincipale, MTerrain* terrain) :
    vuePrincipale(vuePrincipale), editor(terrain), terrain(terrain), quit(false)
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
      MUserEvents::KEY_PRESSED,
      [this](char const& inputChar, Observed const&)
      {
        if (inputChar == '!')
        {
          quit=true;
        }
        if (MParameters::isMouvKey(inputChar))
        {
          currentPerso->deplacer(*terrain, MParameters::getMouvFromKey(inputChar));
        }
        else if (MParameters::isActionKey(inputChar))
        {
          switch (MParameters::getActionFromKey(inputChar))
          {
            case MActionsKey::INTERACT_ENV:
            currentPerso->interagirTuile(*terrain);
            break;
            case MActionsKey::INTERACT_ENTITY_KEY:
            currentPerso->interagirEntite(*terrain);
            break;
            case MActionsKey::MINE:
            currentPerso->mine(*terrain); // FIXME move in model (notify)*//

            vuePrincipale->loadFileIntoGround(&terrain->getImagesList(MTypeCouche::ELEMENT)[0], MParameters::getTextureFor(MTypeCouche::ELEMENT),
                MTypeCouche::ELEMENT, MParameters::getTailleTuile());
            break;
            currentPerso->attaquer(*terrain);
            break;
            case MActionsKey::USE_MAIN_OBJECT:
            currentPerso->utiliserObjet();
            break;
            case MActionsKey::OPEN_EDITOR:
            editor.showEditor();
            break;
            case MActionsKey::OPEN_INVENTORY:

            break;
            default:
            break;
          }
        }

      });

  addAction<MModelEvents, MEntite>(
      MModelEvents::ENTITY_MOVED, [this](MEntite const& entity, Observed const&)
      {
        vuePrincipale->setPositionOf(entity.getNom(), entity.getTuile()->getPosition(), entity.getDirection());
      });

  addAction(MUserEvents::EXIT, [this](Observed const&)
  {
    editor.saveProgram();
  });
}

void CPersonnage::addRobot(std::string const & nom, std::string const & texture, MTuile* tuile,
                           float taille)
{
  bool isInserted = currentPerso->makeRobot(nom, texture, tuile, taille);
  if (isInserted)
  {
    currentPerso->getRobot(nom).addObserver(this);

    currentPerso->getRobot(nom).setActionInteraction(
        [this, nom](MEntite const& entite)
        {
          editor.setProgramName(currentPerso->getNom() + "-" + nom + ".lua", &currentPerso->getRobot(nom));
          editor.showEditor();
        });

    vuePrincipale->addEntite(nom, texture);
    vuePrincipale->setPositionOf(nom, tuile->getPosition(),
                                 currentPerso->getRobot(nom).getDirection());

  }
}
//------------------------------------------------------------
//=====================>Getters&Setters<======================
//------------------------------------------------------------

