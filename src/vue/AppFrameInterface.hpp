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

/**
 * interface pour contrôleur <-> vue
 */
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

//  virtual void setXp(int xp, int xpMax) = 0;
//  virtual void setVie(int vie, int vieMax) = 0;

  virtual void addEntite(std::string entityName, std::string file) = 0;
  virtual void move(std::string entityName, MCoordonnees const& offset,
                    Mouvement direction) = 0;
  virtual void setPositionOf(std::string entityName, MCoordonnees const& position,
                             Mouvement direction) = 0;
  virtual void parler(std::string entityTexture, std::string parole) = 0;
//  virtual void penser(std::string entityTexture, std::string parole) = 0;
  /**
   * fait parler une entité et propose des réponses à l'utilisateur
   * @param parole ce que dis l'entité
   * @param choix variable, l'utilisateur peux choisir un des choix
   * @return le @param choix de l'utilisateur
   */
//  virtual std::string discuter(std::string entityTexture, std::string parole, std::string choix...) =0;
  /**
   *
   * @param entityName l'entité qu'il faut faire taire
   */
//  virtual void arreterBulle(std::string entityTexture) = 0;
private:

//=====================>Getters&Setters<======================
public:

private:

};
//------------------------------------------------------------
//=====================>Implementations<======================
//------------------------------------------------------------

