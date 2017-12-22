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

//------------------------------------------------------------
//========================>Constants<=========================
//------------------------------------------------------------

//------------------------------------------------------------
//=======================>Constructors<=======================
//------------------------------------------------------------

CJeu::CJeu() :
    vuePrincipale(new AppFrame("A Space Story", wxPoint(50, 50), wxSize(512, 340), 32)),
    cNiveau(vuePrincipale), cPersonnage(vuePrincipale, &cNiveau.getTerrain()), cLua(this)
{
  cLua.executeScript(cNiveau.getScript());
  // TODO : to change (lua)
  cPersonnage.setPersonnage("name", MParameters::getSpritesPath() + "texture3.png",
                            &cNiveau.getTerrain()(2, 1), 0.9);
  dynamic_cast<AppFrame*>(vuePrincipale)->Show();
}

CJeu::~CJeu()
{
  delete vuePrincipale;
}

//------------------------------------------------------------
//=========================>Methods<==========================
//------------------------------------------------------------

//------------------------------------------------------------
//=====================>Getters&Setters<======================
//------------------------------------------------------------

