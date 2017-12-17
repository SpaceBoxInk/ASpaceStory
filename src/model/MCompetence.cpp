/*
 * MCompetence.cpp
 *
 *  Created on: Dec 15, 2017
 *      Author: lucadeslot
 */

#include "MCompetence.hpp"

MCompetence::MCompetence() :
    vieMax(0), vie(0), force(0) //TODO : temporaire pour tests à modifier
{

}


int MCompetence::getForce() const
{
  return this->force;
}

int MCompetence::getVie() const
{
  return this->vie;
}

void MCompetence::addVie(int vieAjoutee)
{
  if (vieAjoutee + this->vie < vieMax)
  {
    this->vie = this->vie + vieAjoutee;
  }
  else
  {
    this->vie = this->vieMax;
  }
}

void MCompetence::enleveVie(int vieEnlevee)
{
  if (this->vie - vieEnlevee > 0)
  {
    this->vie = this->vie - vieEnlevee;
  }
  else
  {
    //TODO: Maseltov que faire ?
  }
}
