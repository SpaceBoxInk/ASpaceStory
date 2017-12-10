/**
 * main.cpp
 *
 * Early optimization is the root of all evil
 *
 *  Created on: 11 nov. 2017
 *      Author: nihil
 */

#include "CJeu.hpp"

#include "../model/MParameters.hpp"

int main(int argc, char **argv)
{
  MParameters::load(argv[0]);

  new CJeu();

  return 0;
}
