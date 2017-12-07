/**
 * @file MAssException.cpp
 *
 * Early optimization is the root of all evil
 *
 *  @date 23 nov. 2017
 *  @author FederAndInk
 *  @brief TODO complete
 */

#include "MAssException.hpp"
#include "MPartieCouche.hpp"
#include "MTuile.hpp"

//------------------------------------------------------------
//=======================>MAssException<======================
//------------------------------------------------------------

MAssException::MAssException()
{
}

std::string MAssException::what() const noexcept
{
  return "Exception from A Space Story game !\n";
}

//------------------------------------------------------------
//================>MExceptionEntiteNonPresente================
//------------------------------------------------------------

MExceptionEntiteNonPresente::MExceptionEntiteNonPresente(MTuile const * tuile) :
    tuile(tuile)
{
}

std::string MExceptionEntiteNonPresente::what() const noexcept
{
  return "Entité non présente sur : " + tuile->getPartieCouche(MTypeCouche::SOL)->getName()
      + " en " + tuile->getPosition().str() + '\n';
}

//------------------------------------------------------------
//===================>MExceptionOutOfTerrain==================
//------------------------------------------------------------
MExceptionOutOfTerrain::MExceptionOutOfTerrain(MCoordonnees const & coord) :
    pos(coord)
{
}

MExceptionOutOfTerrain::MExceptionOutOfTerrain(int index) :
    pos(index)
{
}

std::string MExceptionOutOfTerrain::what() const noexcept
{
  std::string posStr;
  if (auto posC = std::get_if<MCoordonnees>(&pos))
  {
    posStr = posC->str();
  }
  else
  {
    auto posI = std::get_if<int>(&pos);
    posStr = std::to_string(*posI);
  }

  return "Coordonnées non valides ! : " + posStr + '\n';
}

//------------------------------------------------------------
//===============>MExceptionInvalidTypeCouche=================
//------------------------------------------------------------
MExceptionInvalidTypeCouche::MExceptionInvalidTypeCouche(MTypeCouche expectedType,
                                                         MTypeCouche type) :
    expectedType(expectedType), type(type)
{
}

std::string MExceptionInvalidTypeCouche::what() const noexcept
{
  return std::string("Type couche invalide, type attendu : ") + to_string(type) + '\n';
}

//------------------------------------------------------------
//=====================>MExceptionFile<=======================
//------------------------------------------------------------
MExceptionFile::MExceptionFile(std::string file, std::string desc) :
    file(file), desc(desc)
{
}

std::string MExceptionFile::what() const noexcept
{
  return "File " + file + " is not valid\nCauses : " + desc + '\n';
}