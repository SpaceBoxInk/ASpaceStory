/**
 * CPersonnage.cpp
 *
 * Early optimization is the root of all evil
 *
 *  Created on: 10 nov. 2017
 *      Author: nihil
 */

#include "CPersonnage.hpp"
#include "../model/MTerrain.hpp"

#include <cstdlib>
#include <string>


using namespace std;

//------------------------------------------------------------
//========================>Constants<=========================
//------------------------------------------------------------

//------------------------------------------------------------
//=======================>Constructors<=======================
//------------------------------------------------------------

CPersonnage::CPersonnage(VPrimitif* vuePrincipale, MTerrain* terrain) :
    vuePrincipale(vuePrincipale), positionJoueur(5, 4), terrain(terrain)
{
  setEventMethods();


  do
  {
    this->vuePrincipale->show(positionJoueur);
  } while (true);
}

CPersonnage::~CPersonnage()
{
  delete vuePrincipale;
}

//------------------------------------------------------------
//=========================>Methods<==========================
//------------------------------------------------------------
void CPersonnage::setEventMethods()
{
  vuePrincipale->addObserver(this);

  // action when keyboard input
  addAction<string, char>("keyEvent", [this](char const& inputChar, Observed const&)
  { switch (inputChar)
    {
      case '!':
      exit(0);
      break;
      case 'z':
      positionJoueur.deplacerDe(Mouvement::HAUT);
      break;
      case 'd':
      positionJoueur.deplacerDe(Mouvement::DROITE);
      break;
      case 's':
      positionJoueur.deplacerDe(Mouvement::BAS);
      break;
      case 'q':
      positionJoueur.deplacerDe(Mouvement::GAUCHE);
      break;
      default:
      break;
    }});
}

//------------------------------------------------------------
//=====================>Getters&Setters<======================
//------------------------------------------------------------

