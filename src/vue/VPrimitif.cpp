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

void VPrimitif::show()
{
  char mov;
  do
  {
    for (int i = 0; i < 100; ++i)
    {
      cout << marron << montagne << blanc;
    }
    cout << endl;

    // mouvements
    mov = mouvement();
    clearScreen();
  } while (mov != '!');
}

char VPrimitif::mouvement()
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

