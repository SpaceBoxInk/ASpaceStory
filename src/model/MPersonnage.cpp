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

//------------------------------------------------------------
//========================>Constants<=========================
//------------------------------------------------------------

//------------------------------------------------------------
//=======================>Constructors<=======================
//------------------------------------------------------------

MPersonnage::MPersonnage(std::string const& nom, MTuile* tuile, float taille) :
    MEntite(nom, tuile, taille)
{
}

MPersonnage::~MPersonnage()
{
}

//------------------------------------------------------------
//=========================>Methods<==========================
//------------------------------------------------------------

//------------------------------------------------------------
//=====================>Getters&Setters<======================
//------------------------------------------------------------

