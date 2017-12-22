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

#include <array>
#include <string>

enum class MTypeCouche
{
  SOL,
  ELEMENT,
  CIEL,
  SIZE
};

constexpr char const* to_string(MTypeCouche coucheT)
{
  std::array<char const*, 4> names { "Sol", "Element", "Ciel", "SIZE" };
  return names[(int)coucheT];
}


class MPartieCouche
{
//========================>Constants<=========================
public:
  static float constexpr PLACE_MAX = 1;

//========================>Attributes<========================
private:
  int id;
  MTypeCouche type;
  std::string name;
  std::string fichierImg;
  float placeDispo;

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
private:

//=====================>Getters&Setters<======================
public:
  int getId() const;

  MTypeCouche const& getType() const;
  std::string const& getName() const;
  std::string const& getFichierImg() const;
  float getPlaceDispo() const;

  void setFichierImg(std::string const & fichierImg);
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
