/**
 * VPrimitif.cpp
 *
 * Early optimization is the root of all evil
 *
 *  Created on: 10 nov. 2017
 *      Author: nihil
 */

#include "VPrimitif.hpp"

#include "../model/MEvents.hpp"

#include <bits/exception.h>
#include <cstdlib>
#include <ios>
#include <iostream>
#include <limits>

using namespace std;

//------------------------------------------------------------
//========================>Constants<=========================
//------------------------------------------------------------

std::string const VPrimitif::escC = "\e[";
std::string const VPrimitif::endC = "m";
std::string const VPrimitif::sepC = ";";
std::string const VPrimitif::foregroundRgb = "38;2;";

std::map<char, std::string> const VPrimitif::colors = { { '.', escC + "32" + endC }, { '#',
    escC + foregroundRgb + "107;73;54" + endC }, { '~', escC + "34" + endC }, { '=', escC
    + foregroundRgb + "107;73;74" + endC } };

std::string const VPrimitif::blanc = escC + "0" + endC;

//------------------------------------------------------------
//=======================>Constructors<=======================
//------------------------------------------------------------

VPrimitif::VPrimitif(MCoordonnees const& coordMax) :
    TAILLE_MAX(coordMax)
{

}

VPrimitif::~VPrimitif()
{
  std::cout << "remove vprim" << '\n';
}

//------------------------------------------------------------
//=========================>Methods<==========================
//------------------------------------------------------------
void clear(istream& in)
{
  in.clear();
  in.ignore(numeric_limits<streamsize>::max(), '\n');
}
void clearScreen()
{
  if (system("clear"))
  {
    system("CLS");
  }
}

void VPrimitif::printTile(char type)
{
  try
  {
    cout << colors.at(type) << type << blanc;
  }
  catch (exception& e)
  {
    cout << type;
  }
}

void VPrimitif::show(MCoordonnees positionJoueur)
{
  int nbTot = 0;
  int line = 0;
  int& x = nbTot;
  int& y = line;

  cout << '\n';
  cout.width(2);
  cout << right << line;
  for (std::string const* img : imgSols)
  {
    if (nbTot == TAILLE_MAX.getX())
    {
      ++line;
      cout << '\n';
      cout.width(2);
      cout << right << line;
      nbTot = 0;
    }

    if (MCoordonnees(x, y) == positionJoueur)
    {
      cout << perso;
    }
    else
    {
      printTile(img->at(0));
    }
    ++nbTot;
  }
  std::cout << endl;
// mouvements
  sendInput();
  clearScreen();
}

void VPrimitif::sendInput()
{
  char c;
  cin >> c;
  clear(cin);
  setChanged();
  notifyObservers(MUserEvents::KEY_PRESSED, c);
}

void VPrimitif::setImg(MTypeCouche const& typeCouche,
                       std::vector<std::string const*> const& imgs)
{
  switch (typeCouche) {
  case MTypeCouche::SOL:
    imgSols.clear();
    imgSols = imgs;
    break;
  case MTypeCouche::ELEMENT:
    imgElems.clear();
    imgElems = imgs;
    break;
  case MTypeCouche::CIEL:
    imgCiels.clear();
    imgCiels = imgs;
    break;
  }
}

//------------------------------------------------------------
//=====================>Getters&Setters<======================
//------------------------------------------------------------

