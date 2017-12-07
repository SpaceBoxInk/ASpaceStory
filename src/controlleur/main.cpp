/**
 * main.cpp
 *
 * Early optimization is the root of all evil
 *
 *  Created on: 11 nov. 2017
 *      Author: nihil
 */

#include "CPersonnage.hpp"

#include "../model/MParameters.hpp"
#include "../model/MPersonnage.hpp"
#include "../model/MTerrain.hpp"
#include "../vue/VPrimitif.hpp"

int main(int argc, char **argv)
{
  MParameters::load(argv[0]);

  MTerrain* terrain = new MTerrain();
  CPersonnage(
      new VPrimitif(terrain->getTailleMax()),
      terrain,
      new MPersonnage("Perso", &(*terrain)(2, 1), 0.9));

  return 0;
}
