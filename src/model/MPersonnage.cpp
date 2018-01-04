/**
 * @file MPersonnage.cpp
 *
 * Early optimization is the root of all evil
 * DRY ! Don't repeat yourself
 *
 *  @date 3 déc. 2017
 *  @author FederAndInk
 *  @brief TODO complete
 */

#include "MPersonnage.hpp"
#include "MAssException.hpp"
#include "MItem.hpp"

#include <utility>

class MTuile;

//------------------------------------------------------------
//========================>Constants<=========================
//------------------------------------------------------------

//------------------------------------------------------------
//=======================>Constructors<=======================
//------------------------------------------------------------

MPersonnage::MPersonnage(std::string const& nom) :
    MEntite(nom, "")
{
}

MPersonnage::~MPersonnage()
{
}

bool MPersonnage::makeRobot(std::string const& nom, std::string const& texture,
                                      MTuile* tuile,
                            float taille)
{
  return robots.try_emplace(nom, this, nom, texture, tuile, taille).second;
}

MRobot& MPersonnage::getRobot(std::string const & nom)
{
  if (robots.count(nom))
  {
    return robots.at(nom);
  }
  else
  {
    throw MExceptionEntiteInexistante(nom);
  }
}

//------------------------------------------------------------
//=========================>Methods<==========================
//------------------------------------------------------------

//------------------------------------------------------------
//=====================>Getters&Setters<======================
//------------------------------------------------------------

