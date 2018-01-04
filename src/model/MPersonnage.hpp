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

#include "MRobot.hpp"

#include <map>
#include <string>

class MTuile;

class MPersonnage : public MEntite
{
//========================>Attributes<========================
private:
  std::map<std::string, MRobot> robots;
//=======================>Constructors<=======================
public:
  MPersonnage(std::string const& nom);
  // TODO: rule of five ? copyandswap
  virtual ~MPersonnage();

private:

//=========================>Methods<==========================
public:
  bool makeRobot(std::string const& nom, std::string const& texture, MTuile* tuile,
                 float taille);
private:

//=====================>Getters&Setters<======================
public:
  MRobot& getRobot(std::string const& nom);
private:

};
