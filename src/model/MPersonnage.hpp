/**
 * @file MPersonnage.hpp
 *
 * Early optimization is the root of all evil
 * DRY ! Don't repeat yourself
 *
 *  @date 3 déc. 2017
 *  @author FederAndInk
 *  @brief TODO complete
 */

#pragma once

#include "MEntite.hpp"

#include <string>

class MPersonnage : public MEntite
{
//========================>Attributes<========================
private:

//=======================>Constructors<=======================
public:
  MPersonnage(std::string const& nom, MTuile* tuile, float taille);
  // TODO: rule of five ? copyandswap
  virtual ~MPersonnage();

private:

//=========================>Methods<==========================
public:

private:

//=====================>Getters&Setters<======================
public:

private:

};
