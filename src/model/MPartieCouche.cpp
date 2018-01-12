/**
 * @file MPartieCouche.cpp
 *
 * Early optimization is the root of all evil
 *
 *  @date 23 nov. 2017
 *  @author FederAndInk
 *  @brief TODO complete
 */

#include "MPartieCouche.hpp"
#include "MCoordonnees.hpp"
#include "MThreads.hpp"

#include <stdexcept>


//------------------------------------------------------------
//========================>Constants<=========================
//------------------------------------------------------------

//------------------------------------------------------------
//=======================>Constructors<=======================
//------------------------------------------------------------

MPartieCouche::MPartieCouche(int id, MTypeCouche type, std::string name,
                             std::string fichierImg,
                             float placeDispo) :
    id(id), type(type), name(name), fichierImg(fichierImg), placeDispo(placeDispo)
{
}

MPartieCouche::MPartieCouche(MPartieCouche const &other):
    id(other.id), type(other.type), name(other.name), fichierImg(other.fichierImg),
    placeDispo(other.placeDispo), actionPassage(other.actionPassage),
    actionDeclenchement(other.actionDeclenchement)
{
}

MPartieCouche& MPartieCouche::operator =(MPartieCouche const & other)
{
  id = other.id;
  type = other.type;
  name = other.name;
  fichierImg = other.fichierImg;
  placeDispo = other.placeDispo;
  actionPassage = other.actionPassage;
  actionDeclenchement = other.actionDeclenchement;
  return *this;
}

MPartieCouche::~MPartieCouche()
{
}

//------------------------------------------------------------
//=========================>Methods<==========================
//------------------------------------------------------------

bool MPartieCouche::isTypeOf(MTypeCouche type) const
{
  return getType() == type;
}

void MPartieCouche::passageDe(MEntite* entite)
{
  if (actionPassage)
  {
    MThreads::parallelize(actionPassage, entite->getNom());
  }
}

void MPartieCouche::declenchementDe(MEntite* entite)
{
  if (actionDeclenchement)
  {
    MThreads::parallelize(actionDeclenchement, entite->getNom());
  }
}

void MPartieCouche::mine(MEntite* entite, int item, MCoordonnees minedCoords)
{
  throw std::logic_error("Cannot call mine on couche isn't ELEMENT !");
}

bool MPartieCouche::isNull() const
{
  return id == 0;
}

//------------------------------------------------------------
//=====================>Getters&Setters<======================
//------------------------------------------------------------
MTypeCouche const& MPartieCouche::getType() const
{
  return type;
}

std::string const& MPartieCouche::getName() const
{
  return name;
}

std::string const& MPartieCouche::getFichierImg() const
{
  return fichierImg;
}

float MPartieCouche::getPlaceDispo() const
{
  return placeDispo;
}

int MPartieCouche::getMiningLevel() const
{
  throw std::logic_error("Cannot call getMiningLevel on couche isn't ELEMENT !");
}

void MPartieCouche::setActionMining(
    std::function<void(MEntite* entite, int item, int xMined, int yMined)> actionMining)
{
  throw std::logic_error("Cannot call setActionMining on couche isn't ELEMENT !");
}

void MPartieCouche::unSetActionMining()
{
  throw std::logic_error("Cannot call unSetActionMining on couche isn't ELEMENT !");
}

std::string to_string(MTypeCouche coucheT)
{
  std::array<char const *, 4> names { "Sol", "Element", "Ciel", "SIZE" };
  return names[(int)(coucheT)];
}
