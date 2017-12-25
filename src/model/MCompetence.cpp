/*
 * MCompetence.cpp
 *
 *  Created on: Dec 15, 2017
 *      Author: lucadeslot
 */

#include "MCompetence.hpp"

MCompetence::MCompetence() :
    vieMax(20), vie(20), force(5) //TODO : temporaire pour tests à modifier
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
  this->vie = this->vie - vieEnlevee;
}
