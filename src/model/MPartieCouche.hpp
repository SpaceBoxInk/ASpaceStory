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

#include <string>

enum class MTypeCouche
{
  SOL,
  ELEMENT,
  CIEL,
};

class MPartieCouche
{
//========================>Attributes<========================
private:
  MTypeCouche type;
  std::string name;
  std::string fichierImg;
  float placeDispo;

//=======================>Constructors<=======================
public:
  MPartieCouche(MTypeCouche type, std::string name, float placeDispo);
  MPartieCouche(MPartieCouche const&) = default;
  // TODO: rule of five ? copyandswap
  virtual ~MPartieCouche();

private:

//=========================>Methods<==========================
public:

  bool isTypeOf(MTypeCouche type) const;
private:

//=====================>Getters&Setters<======================
public:
  MTypeCouche const& getType() const;
  std::string const& getName() const;
  float getPlaceDispo() const;

private:

};
