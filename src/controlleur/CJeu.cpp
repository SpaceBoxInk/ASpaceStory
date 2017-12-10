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

#include "../model/MCoordonnees.hpp"
#include "../model/MPersonnage.hpp"
#include "../vue/VPrimitif.hpp"

//------------------------------------------------------------
//========================>Constants<=========================
//------------------------------------------------------------

//------------------------------------------------------------
//=======================>Constructors<=======================
//------------------------------------------------------------

CJeu::CJeu() :
vuePrincipale(cNiveau.getTerrain().getTaille()), cNiveau(&vuePrincipale),
    cPersonnage(&vuePrincipale, &cNiveau.getTerrain()), cLua(this)
{
  cLua.executeScript(cNiveau.getScript());
  // TODO : to change (lua)
  cPersonnage.setPersonnage("name", &cNiveau.getTerrain()(2, 1), 0.9);
  cPersonnage.launchPersonnage();
}

CJeu::~CJeu()
{
}

//------------------------------------------------------------
//=========================>Methods<==========================
//------------------------------------------------------------

//------------------------------------------------------------
//=====================>Getters&Setters<======================
//------------------------------------------------------------

