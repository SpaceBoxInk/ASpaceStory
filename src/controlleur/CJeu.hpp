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

#include <future>
#include <string>

/**
 * Controller for controllers
 */
class CJeu
{
  friend class CLua;
//========================>Attributes<========================
private:
  AppFrameInterface* vuePrincipale;
  CNiveau cNiveau;
  CPersonnage cPersonnage;
  CLua cLua;

  std::future<void> thread;
//=======================>Constructors<=======================
public:
  CJeu();
  // TODO: rule of five ? copyandswap
  virtual ~CJeu();

private:

//=========================>Methods<==========================
public:
  MEntite* getEntite(std::string name);
  MPersonnage* getPersonnage(std::string name);
private:
//=====================>Getters&Setters<======================
public:

private:

};
//------------------------------------------------------------
//=====================>Implementations<======================
//------------------------------------------------------------

