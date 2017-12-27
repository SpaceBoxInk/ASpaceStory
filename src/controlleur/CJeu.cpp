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
    vuePrincipale(new AppFrame("A Space Story", wxPoint(0, 0), wxSize(1536, 1020), 32)),
    cNiveau(vuePrincipale), cPersonnage(vuePrincipale, &cNiveau.getTerrain()), cLua(this)
{
  cPersonnage.addPersonnage("name");
  cPersonnage.setPersonnage("name");
  try
  {
    cLua.executeScript(cNiveau.getScript());
  }
  catch (MAssException& e)
  {
    std::cout << e.what() << '\n';
  }
  // TODO : to change (lua)
  vuePrincipale->addEntite(cPersonnage.getCurrentPerso()->getNom(),
                           cPersonnage.getCurrentPerso()->getTexture());
  vuePrincipale->setPositionOf(cPersonnage.getCurrentPerso()->getNom(),
                               cPersonnage.getCurrentPerso()->getTuile()->getPosition());
  dynamic_cast<AppFrame*>(vuePrincipale)->Show();
}

CJeu::~CJeu()
{
  delete vuePrincipale;
}

MEntite* CJeu::getEntite(std::string name)
{
  MEntite* ent = cNiveau.getEntite(name);
  return ent;
}

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

