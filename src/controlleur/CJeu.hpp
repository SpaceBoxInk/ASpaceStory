/**
 * @file CJeu.hpp
 *
 * Early optimization is the root of all evil
 * DRY ! Don't repeat yourself
 *
 *  @date 8 déc. 2017
 *  @author FederAndInk
 *  @brief TODO complete
 */

#pragma once

#include "CLua.hpp"
#include "CNiveau.hpp"
#include "CPersonnage.hpp"

#include "../vue/AppFrame.hpp"

class CJeu
{
  friend class CLua;
//========================>Attributes<========================
private:
  AppFrameInterface* vuePrincipale;
  CNiveau cNiveau;
  CPersonnage cPersonnage;
  CLua cLua;
//=======================>Constructors<=======================
public:
  CJeu();
  // TODO: rule of five ? copyandswap
  virtual ~CJeu();

private:

//=========================>Methods<==========================
public:

private:

//=====================>Getters&Setters<======================
public:

private:

};
//------------------------------------------------------------
//=====================>Implementations<======================
//------------------------------------------------------------

