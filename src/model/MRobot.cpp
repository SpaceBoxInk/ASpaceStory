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
#include "MPersonnage.hpp"


//------------------------------------------------------------
//========================>Constants<=========================
//------------------------------------------------------------

//------------------------------------------------------------
//=======================>Constructors<=======================
//------------------------------------------------------------

MRobot::MRobot(MPersonnage* proprietaire, std::string const& nom, std::string const& texture,
               MTuile* tuile, float taille) :
    MEntite(nom, texture, tuile, taille), proprietaire(*proprietaire)
{
}

MRobot::~MRobot()
{
}

//------------------------------------------------------------
//=========================>Methods<==========================
//------------------------------------------------------------

//------------------------------------------------------------
//=====================>Getters&Setters<======================
//------------------------------------------------------------

