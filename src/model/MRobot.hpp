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

#include "MCoordonnees.hpp"
#include "MEntite.hpp"

#include <chrono>
#include <string>

class MTuile;

class MPersonnage;

/**
 * Nothing special, maybe some specific behavior is becoming later
 */
class MRobot : public MEntite
{
//========================>Attributes<========================
private:
  MPersonnage& proprietaire;
  std::chrono::seconds speed;
  MTuile* posDepart;
  Mouvement dirDepart;
//=======================>Constructors<=======================
public:
  MRobot(MPersonnage* proprietaire, std::string const& texture, std::string const& nom,
         MTuile* tuile, float taille);
  // TODO: rule of five ? copyandswap
  virtual ~MRobot();

private:

//=========================>Methods<==========================
public:
  bool launch();
  bool reset();
  bool isReset();
private:

//=====================>Getters&Setters<======================
public:
  std::chrono::seconds const & getSpeed() const;
  MTuile const* getBeginPos() const;
private:
  void setSpeed(std::chrono::seconds const & speed);

};
//------------------------------------------------------------
//=====================>Implementations<======================
//------------------------------------------------------------

inline std::chrono::seconds const & MRobot::getSpeed() const
{
  return speed;
}

inline MTuile const * MRobot::getBeginPos() const
{
  return posDepart;
}

inline void MRobot::setSpeed(std::chrono::seconds const & speed)
{
  this->speed = speed;
}

