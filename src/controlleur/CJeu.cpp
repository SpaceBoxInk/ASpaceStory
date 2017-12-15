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
  cPersonnage.addPersonnage("name");
  cPersonnage.setPersonnage("name");
  cLua.executeScript(cNiveau.getScript());
  // TODO : to change (lua)
  cPersonnage.launchPersonnage();
}

CJeu::~CJeu()
{
}

MEntite* CJeu::getEntite(std::string name)
{
  MEntite* ent = cNiveau.getEntite(name);
  return ent ? ent : cPersonnage.getPersonnage(name);
}
//------------------------------------------------------------
//=========================>Methods<==========================
//------------------------------------------------------------

//------------------------------------------------------------
//=====================>Getters&Setters<======================
//------------------------------------------------------------

