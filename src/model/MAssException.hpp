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

#include <string>
#include <variant>

struct lua_State;

class MTuile;
enum class MTypeCouche
;

/**
 * Exception generique du jeu
 */
class MAssException
{
//========================>Attributes<========================
private:
  std::string desc;
//=======================>Constructors<=======================
public:
  MAssException(std::string desc = "");
  // TODO: rule of five ? copyandswap
  virtual ~MAssException() = default;

  virtual std::string what() const noexcept;
};

/**
 * Exception lorsque qu'une entité n'est pas présente à un endroit (#MTuile)
 */
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

/**
 * Lorsque l'on demande quelque chose (MTuile/MCoordonnees) qui est en dehors du MTerrain
 */
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

/**
 * Lorsque qu'un certain #MTypeCouche est attendu et qu'un autre est donné
 */
class MExceptionInvalidTypeCouche : public MAssException
{
private:
  MTypeCouche const& expectedType;
  MTypeCouche const& type;
public:
  MExceptionInvalidTypeCouche(MTypeCouche expectedType, MTypeCouche type);
  // TODO: rule of five ? copyandswap
  virtual ~MExceptionInvalidTypeCouche() = default;

  virtual std::string what() const noexcept override;
};

/**
 * Exception relative aux fichiers\
 * format\
 * ouverture
 */
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

class MExceptionLuaArguments : public MAssException
{
private:
  std::string desc;
public:
  MExceptionLuaArguments(std::string desc, int nbArgs);
  // TODO: rule of five ? copyandswap
  virtual ~MExceptionLuaArguments() = default;

  virtual std::string what() const noexcept override;
};

class MExceptionEntiteInexistante : public MAssException
{
private:
  std::string entite;
public:
  MExceptionEntiteInexistante(std::string entite);
  // TODO: rule of five ? copyandswap
  virtual ~MExceptionEntiteInexistante() = default;

  virtual std::string what() const noexcept override;
};

class MExceptionEntiteDejaCreee : public MAssException
{
private:
  std::string entite;
public:
  MExceptionEntiteDejaCreee(std::string entite);
  // TODO: rule of five ? copyandswap
  virtual ~MExceptionEntiteDejaCreee() = default;

  virtual std::string what() const noexcept override;
};

