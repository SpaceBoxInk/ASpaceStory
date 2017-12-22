/**
 * @file AppFrameInterface.hpp
 *
 * Early optimization is the root of all evil
 * DRY ! Don't repeat yourself
 *
 *  @date 22 déc. 2017
 *  @author FederAndInk
 *  @brief TODO complete
 */

#pragma once

#include "../model/MPartieCouche.hpp"
#include "../outils/ObserverPattern/Observed.hpp"

#include <string>


class AppFrameInterface : public Observed
{
//========================>Attributes<========================
private:

//=======================>Constructors<=======================
public:
  AppFrameInterface() = default;
  virtual ~AppFrameInterface() = default;
private:

//=========================>Methods<==========================
public:
  virtual void loadFileIntoGround(int const* idList, std::string texture, MTypeCouche level,
                          int tailleTexture) = 0;
//  virtual void loadTextureFile(std::string texture, MTypeCouche level, int tailleTexture) = 0;
//  virtual void loadGround(int const* idList, MTypeCouche level) = 0;

  virtual void addEntite(std::string name, std::string file) = 0;
//  virtual void move(std::string entityName, MCoordonnees offset) = 0;
//  virtual void setPositionOf(std::string entityName, MCoordonnees position) = 0;

private:

//=====================>Getters&Setters<======================
public:

private:

};
//------------------------------------------------------------
//=====================>Implementations<======================
//------------------------------------------------------------

