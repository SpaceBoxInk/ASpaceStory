/**
 * @file MPartieCouche.hpp
 *
 * Early optimization is the root of all evil
 *
 *  @date 23 nov. 2017
 *  @author FederAndInk
 *  @brief TODO complete
 */

#pragma once

#include "MEntite.hpp"

#include <array>
#include <exception>
#include <functional>
#include <string>

enum class MTypeCouche
{
  SOL,
  ELEMENT,
  CIEL,
  SIZE
};

std::string to_string(MTypeCouche coucheT);


class MPartieCouche
{
//========================>Constants<=========================
public:
  static float constexpr PLACE_MAX = 1;

//========================>Attributes<========================
private:
  /**
   * l'id de couleur indexée définie par gimp pour le lien avec une image définie dans la *List (*=sol|element|ciel)
   */
  int id;
  MTypeCouche type;
  std::string name;
  std::string fichierImg;
  float placeDispo;

  /**
   * action set by lua
   * @see CLua#addActionPassage
   */
  std::function<void(std::string entite)> actionPassage;
  /**
   * action set by lua
   * @see CLua#addActionDeclenchement
   */
  std::function<void(std::string entite)> actionDeclenchement;

//=======================>Constructors<=======================
public:
  MPartieCouche(int id, MTypeCouche type, std::string name, std::string fichierImg,
                float placeDispo);
  MPartieCouche(MPartieCouche const&) = default;
  // TODO: rule of five ? copyandswap
  virtual ~MPartieCouche();

private:

//=========================>Methods<==========================
public:

  bool isTypeOf(MTypeCouche type) const;
  void passageDe(MEntite* entite);
  void declenchementDe(MEntite* entite);

  virtual void mine(MEntite* entite, int item, MCoordonnees minedCoords);

  bool isNull() const;
private:

//=====================>Getters&Setters<======================
public:
  int getId() const;

  MTypeCouche const& getType() const;
  std::string const& getName() const;
  std::string const& getFichierImg() const;
  float getPlaceDispo() const;
  virtual int getMiningLevel() const;

  void setFichierImg(std::string const & fichierImg);

  void setActionDeclenchement(std::function<void(std::string entite)> actionDeclenchement);
  void setActionPassage(std::function<void(std::string entite)> actionPassage);
  virtual void setActionMining(
      std::function<void(MEntite* entite, int item, int xMined, int yMined)> actionMining);
  void unSetActionDeclenchement();
  void unSetActionPassage();
  virtual void unSetActionMining();

private:

};
//--------------------------------------------------------------
//========================>Definitions<=========================
//--------------------------------------------------------------
inline int MPartieCouche::getId() const
{
  return id;
}

inline void MPartieCouche::setFichierImg(std::string const & fichierImg)
{
  this->fichierImg = fichierImg;
}

inline void MPartieCouche::setActionDeclenchement(
    std::function<void(std::string entite)> actionDeclenchement)
{
  this->actionDeclenchement = actionDeclenchement;
}

inline void MPartieCouche::setActionPassage(
    std::function<void(std::string entite)> actionPassage)
{
  this->actionPassage = actionPassage;
}

inline void MPartieCouche::unSetActionDeclenchement()
{
  actionDeclenchement = nullptr;
}

inline void MPartieCouche::unSetActionPassage()
{
  actionPassage = nullptr;
}
