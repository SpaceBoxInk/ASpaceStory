/**
 * @file MAssException.hpp
 *
 * Early optimization is the root of all evil
 *
 *  @date 23 nov. 2017
 *  @author FederAndInk
 *  @brief TODO complete
 */

#pragma once

#include "MCoordonnees.hpp"
#include "MPartieCouche.hpp"

#include <string>
#include <variant>

class MTuile;

class MAssException
{
//========================>Attributes<========================
private:

//=======================>Constructors<=======================
public:
  MAssException();
  // TODO: rule of five ? copyandswap
  virtual ~MAssException() = default;

  virtual std::string what() const noexcept;
};

class MExceptionEntiteNonPresente : public MAssException
{
private:
  MTuile const* tuile;
public:
  MExceptionEntiteNonPresente(MTuile const* tuile);
  // TODO: rule of five ? copyandswap
  virtual ~MExceptionEntiteNonPresente() = default;

  virtual std::string what() const noexcept override;
};

class MExceptionOutOfTerrain : public MAssException
{
private:
  std::variant<MCoordonnees, int> pos;
public:
  MExceptionOutOfTerrain(MCoordonnees const& coord);
  MExceptionOutOfTerrain(int index);
  // TODO: rule of five ? copyandswap
  virtual ~MExceptionOutOfTerrain() = default;

  virtual std::string what() const noexcept override;
};

class MExceptionInvalidTypeCouche : public MAssException
{
private:
  MTypeCouche expectedType;
  MTypeCouche type;
public:
  MExceptionInvalidTypeCouche(MTypeCouche expectedType, MTypeCouche type);
  // TODO: rule of five ? copyandswap
  virtual ~MExceptionInvalidTypeCouche() = default;

  virtual std::string what() const noexcept override;
};

class MExceptionFile : public MAssException
{
private:
  std::string file;
  std::string desc;
public:
  MExceptionFile(std::string file, std::string desc);
  // TODO: rule of five ? copyandswap
  virtual ~MExceptionFile() = default;

  virtual std::string what() const noexcept override;
};

