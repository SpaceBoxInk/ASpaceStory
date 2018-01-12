/**
 * @file CJeu.cpp
 *
 * Early optimization is the root of all evil
 * DRY ! Don't repeat yourself
 *
 *  @date 8 déc. 2017
 *  @author FederAndInk
 *  @brief TODO complete
 */

#include "CJeu.hpp"

#include "../model/MAssException.hpp"
#include "../model/MEvents.hpp"
#include "../model/MPersonnage.hpp"
#include "../model/MTuile.hpp"
#include "../outils/ObserverPattern/Observer.hpp"
#include "../vue/AppFrame.hpp"

#include <iostream>

//------------------------------------------------------------
//========================>Constants<=========================
//------------------------------------------------------------

//------------------------------------------------------------
//=======================>Constructors<=======================
//------------------------------------------------------------

CJeu::CJeu() :
    vuePrincipale(
        new AppFrame("A Space Story", wxPoint(0, 0),
            wxSize(wxSystemSettings::GetMetric(wxSYS_SCREEN_X) - 10,
                   wxSystemSettings::GetMetric(wxSYS_SCREEN_Y) - 80),
            32)),
    cNiveau(vuePrincipale), cPersonnage(vuePrincipale, &cNiveau.getTerrain()), cLua(this)
{

  cPersonnage.addPersonnage("joueur 1");
  cPersonnage.setPersonnage("joueur 1");
  cLua.executeScript(cNiveau.getScript());

  // TODO : to change (lua)
  vuePrincipale->addEntite(cPersonnage.getCurrentPerso()->getNom(),
                           cPersonnage.getCurrentPerso()->getTexture());
  vuePrincipale->setPositionOf(cPersonnage.getCurrentPerso()->getNom(),
                               cPersonnage.getCurrentPerso()->getTuile()->getPosition(),
                               cPersonnage.getCurrentPerso()->getDirection());
  dynamic_cast<AppFrame*>(vuePrincipale)->Show();

  thread = std::async(std::launch::async, [this]
  { cLua.executeMain();});

}

CJeu::~CJeu()
{
  dynamic_cast<AppFrame*>(vuePrincipale)->Close();
}

/**
 *
 * @param name le nom de l'entité
 * @return l'entité du nom @var name et du niveau courant
 */
MEntite* CJeu::getEntite(std::string name)
{
  MEntite* ent = cNiveau.getEntite(name);
  return ent;
}

/**
 *
 * @param name le nom du personnage à get
 * @return le personnage du nom spécifié
 */
MPersonnage* CJeu::getPersonnage(std::string name)
{
  return cPersonnage.getPersonnage(name);
}

//------------------------------------------------------------
//=========================>Methods<==========================
//------------------------------------------------------------

//------------------------------------------------------------
//=====================>Getters&Setters<======================
//------------------------------------------------------------

