/**
 * @file VInventaireInterface.hpp
 *
 * Early optimization is the root of all evil
 * DRY ! Don't repeat yourself
 *
 *  @date 22 déc. 2017
 *  @author FederAndInk
 *  @brief TODO complete
 */

#pragma once

#include "../outils/ObserverPattern/Observed.hpp"

class VInventaireInterface : public Observed
{
//========================>Attributes<========================
private:

//=======================>Constructors<=======================
public:
  VInventaireInterface() = default;
	// TODO: rule of five ? copyandswap
  virtual ~VInventaireInterface() = default;

private:

//=========================>Methods<==========================
public:
  /**
   * @param id id de l'objet
   * @param image image de l'objet
   * @param position la position dans l'inventaire ligne par ligne, si @a -1 l'objet va dans une case disponible
   */
//  virtual void ajouterObjInventaire(unsigned long long id, std::string name, std::string description, std::string image,
//                                    int position = -1) = 0;
//  virtual void ajouterObjInventaireRapid(unsigned long long id, std::string name, std::string description, std::string image,
//                                    int position = -1) = 0;
//  virtual void enleverObjInventaire(unsigned long long id) = 0;
private:

//=====================>Getters&Setters<======================
public:

private:

};
//------------------------------------------------------------
//=====================>Implementations<======================
//------------------------------------------------------------

