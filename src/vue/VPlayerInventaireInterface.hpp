/**
 * @file VPlayerInventaireInterface.hpp
 *
 * Early optimization is the root of all evil
 * DRY ! Don't repeat yourself
 *
 *  @date 22 déc. 2017
 *  @author FederAndInk
 *  @brief TODO complete
 */

#pragma once

#include "VInventaireInterface.hpp"

class MCoordonnees;


class VPlayerInventaireInterface : public virtual VInventaireInterface
{
//========================>Attributes<========================
private:

//=======================>Constructors<=======================
public:
  /**
   *
   * @param size définie la taille de l'inventaire, et aussi le x définie la taille du quickInventaire\
   * Il y a donc x*(y+1) cases\
   *
   * eg : x = 3, y = 2, il y a au total 3*(2+1) cases\
   * □□□ // inventaire
   * □□□
   *
   * □□□ // barre d'inventaire rapide
   */
  VPlayerInventaireInterface(MCoordonnees const& size) :
      VInventaireInterface(size)
  {
  }
	// TODO: rule of five ? copyandswap
  virtual ~VPlayerInventaireInterface() = default;

private:

//=========================>Methods<==========================
public:
  /**
   * @param id id de l'objet
   * @param image image de l'objet
   * @param position la position dans l'inventaire ligne par ligne, si @a -1 l'objet va dans la première case disponible
   */
  virtual void addObjPlayerQuickInv(unsigned long long id, std::string name,
                                    std::string description, std::string image, int position =
                                        -1) = 0;
private:

//=====================>Getters&Setters<======================
public:

private:

};
//------------------------------------------------------------
//=====================>Implementations<======================
//------------------------------------------------------------

