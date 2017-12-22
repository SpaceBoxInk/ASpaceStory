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

//  virtual void setXp(int xp, int xpMax) = 0;
//  virtual void setVie(int vie, int vieMax) = 0;

  virtual void addEntite(std::string entityName, std::string file) = 0;
//  virtual void move(std::string entityName, MCoordonnees offset) = 0;
//  virtual void setPositionOf(std::string entityName, MCoordonnees position) = 0;
//  virtual void parler(std::string entityName, std::string parole) = 0;
//  virtual void penser(std::string entityName, std::string parole) = 0;
  /**
   * fait parler une entité et propose des réponses à l'utilisateur
   * @param parole ce que dis l'entité
   * @param choix variable, l'utilisateur peux choisir un des choix
   * @return le @param choix de l'utilisateur
   */
//  virtual std::string discuter(std::string entityName, std::string parole, std::string choix...) =0;
  /**
   *
   * @param entityName l'entité qu'il faut faire taire
   */
//  virtual void arreterBulle(std::string entityName) = 0;

  /**
   * affiche une enigme avec une image et une description
   * un bouton ok et indice(optionnel) est recommendé
   *
   * @param image chemin vers l'image
   * @param description texte
   */
//  virtual void afficherEnigme(std::string image, std::string description, bool indice = false) = 0;
//  virtual void afficherInventaire() = 0;
//  virtual void afficherEditeur() = 0;
private:

//=====================>Getters&Setters<======================
public:

private:

};
//------------------------------------------------------------
//=====================>Implementations<======================
//------------------------------------------------------------

