/*
 * MCompetence.hpp
 *
 *  Created on: Dec 15, 2017
 *      Author: lucadeslot
 */

#ifndef SRC_MODEL_MCOMPETENCE_HPP_
#define SRC_MODEL_MCOMPETENCE_HPP_

class MCompetence
{
  //========================>Attributes<========================

public:

private:
  int vieMax;
  int vie;
  int force;
public:
  //=======================>Constructors<=======================

  MCompetence();

  //=========================>Methods<==========================
private:

public:
  int getForce() const;
  int getVie() const;
  void addVie(int vieAjoutee);
  void enleveVie(int vieEnlevee);

  //=====================>Getters&Setters<======================

};

//------------------------------------------------------------
//=====================>Implementations<======================
//------------------------------------------------------------

#endif /* SRC_MODEL_MCOMPETENCE_HPP_ */
