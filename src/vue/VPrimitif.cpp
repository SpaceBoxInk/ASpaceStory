/**
 * VPrimitif.cpp
 *
 * Early optimization is the root of all evil
 *
 *  Created on: 10 nov. 2017
 *      Author: nihil
 */

#include "VPrimitif.hpp"
#include <iostream>

using namespace std;

//------------------------------------------------------------
//========================>Constants<=========================
//------------------------------------------------------------

std::string const VPrimitif::escC = "\e[";
std::string const VPrimitif::endC = "m";
std::string const VPrimitif::sepC = ";";
std::string const VPrimitif::foregroundRgb = "38;2;";

std::string const VPrimitif::vert = escC + "32" + endC;
std::string const VPrimitif::marron = escC + foregroundRgb + "107;73;54" + endC;
std::string const VPrimitif::blanc = escC + "0" + endC;

//------------------------------------------------------------
//=======================>Constructors<=======================
//------------------------------------------------------------

VPrimitif::VPrimitif()
{
}

VPrimitif::~VPrimitif()
{
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
  system("CLS");
  system("clear");
}

void VPrimitif::printTile(char type)
{
  switch (type) {
  case 'm':
    cout << marron << montagne << blanc;
    break;
  case 'h':
    cout << vert << terrainHerbe << blanc;
    break;
  }
}

void VPrimitif::show()
{
  //char input;
  int nbTot = 0;
  int line = 0;
  int nb;
  char type;
  ifstream fichier("src/ressources/niveaux/test.nbg");
  if (fichier)  // si l'ouverture a réussi
  {
    // instructions
    cout.width(2);
    cout << endl << right << line++;
    while (!fichier.eof())
    {
      fichier >> type >> nb;
      for (int a = 0; a < nb; ++a, ++nbTot)
      {
        if (nbTot == TAILLE_MAX)
        {
          cout.width(2);
          cout << endl << right << line;
          nbTot = 0;
          ++line;
        }
        printTile(type);
      }
      type = 0;
      nb = 0;
    }
    cout << endl;

    fichier.close();  // on ferme le fichier
  }
  else
// sinon
    cerr << "Impossible d'ouvrir le fichier !" << endl;
//  do
//  {
//    for (int i = 0; i < 100; ++i)
//    {
//      cout << marron << montagne << blanc;
//    }
//    cout << endl;
//
//    // mouvements
//		input = getInput();
//    clearScreen();
//	} while (input != '!');
}

char VPrimitif::getInput()
{
  char c;
  cin >> c;
  cout << c << endl;
  clear(cin);
  return c;
// TODO : do something
}

//------------------------------------------------------------
//=====================>Getters&Setters<======================
//------------------------------------------------------------

