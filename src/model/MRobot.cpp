/**
 * @file MRobot.cpp
 *
 * Early optimization is the root of all evil
 * DRY ! Don't repeat yourself
 *
 *  @date 14 déc. 2017
 *  @author FederAndInk
 *  @brief TODO complete
 */

#include "MRobot.hpp"
#include "MAssException.hpp"
#include "MEvents.hpp"
#include "MTuile.hpp"

class MPersonnage;

using namespace std::chrono_literals;

//------------------------------------------------------------
//========================>Constants<=========================
//------------------------------------------------------------

//------------------------------------------------------------
//=======================>Constructors<=======================
//------------------------------------------------------------

MRobot::MRobot(MPersonnage* proprietaire, std::string const& nom, std::string const& texture,
               MTuile* tuile, float taille) :
    MEntite(nom, texture, tuile, taille), proprietaire(*proprietaire), speed(500ms),
    posDepart(tuile), dirDepart(getDirection())
{
}

MRobot::~MRobot()
{
}
//------------------------------------------------------------
//=========================>Methods<==========================
//------------------------------------------------------------

bool MRobot::launch()
{
  return reset();
}

bool MRobot::reset()
try
{
  if (!isReset())
  {
    setDirection(dirDepart);
    setTuile(posDepart);
    setChanged();
    notifyObservers(MModelEvents::ENTITY_MOVED, *dynamic_cast<MEntite*>(this));
  }
  return isReset();
}
catch (MAssException& e)
{
  return false;
}

bool MRobot::isReset()
{
  return getTuile()->getPosition() == posDepart->getPosition() && dirDepart == getDirection();
}
//------------------------------------------------------------
//=====================>Getters&Setters<======================
//------------------------------------------------------------

