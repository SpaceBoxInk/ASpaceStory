/**
 * @file MRobot.hpp
 *
 * Early optimization is the root of all evil
 * DRY ! Don't repeat yourself
 *
 *  @date 14 déc. 2017
 *  @author FederAndInk
 *  @brief TODO complete
 */

#pragma once

#include "MEntite.hpp"

#include <string>

class MTuile;

class MPersonnage;

class MRobot : public MEntite
{
//========================>Attributes<========================
private:
  MPersonnage& proprietaire;
//=======================>Constructors<=======================
public:
  MRobot(MPersonnage* proprietaire, std::string const& nom, MTuile* tuile, float taille);
  // TODO: rule of five ? copyandswap
  virtual ~MRobot();

private:

//=========================>Methods<==========================
public:

private:

//=====================>Getters&Setters<======================
public:

private:

};
//------------------------------------------------------------
//=====================>Implementations<======================
//------------------------------------------------------------

