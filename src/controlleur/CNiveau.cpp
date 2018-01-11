/**
 * @file CNiveau.cpp
 *
 * Early optimization is the root of all evil
 * DRY ! Don't repeat yourself
 *
 *  @date 1 déc. 2017
 *  @author FederAndInk
 *  @brief TODO complete
 */

#include "CNiveau.hpp"

#include <iostream>

#include "../model/MAssException.hpp"
#include "../model/MEvents.hpp"
#include "../model/MPartieCouche.hpp"
#include "../vue/AppFrameInterface.hpp"

#include <utility>

//------------------------------------------------------------
//========================>Constants<=========================
//------------------------------------------------------------

//------------------------------------------------------------
//=======================>Constructors<=======================
//------------------------------------------------------------

CNiveau::CNiveau(AppFrameInterface* vuePrincipale, std::string levelFolder,
                 std::string levelMainFile) :
    vuePrincipale(vuePrincipale), levelFolder(levelFolder), levelMainFile(levelMainFile)
{
  terrain.addObserver(this);
  setEventMethods();
}

CNiveau::~CNiveau()
{
}

//------------------------------------------------------------
//=========================>Methods<==========================
//------------------------------------------------------------
void CNiveau::setEventMethods()
{
  addAction<MModelEvents, MTypeCouche>(
      MModelEvents::COUCHE_LOADED,
      [this](MTypeCouche couche, Observed const& o)
      {
        vuePrincipale->loadFileIntoGround(&terrain.getImagesList(couche)[0], MParameters::getTextureFor(couche),
            couche, MParameters::getTailleTuile());
      });
  addAction<MModelEvents, MEntite>(
      MModelEvents::ENTITY_MOVED, [this](MEntite const& entity, Observed const&)
      {
        vuePrincipale->setPositionOf(entity.getNom(), entity.getTuile()->getPosition(), entity.getDirection());
      });
}

//------------------------------------------------------------
//=====================>Getters&Setters<======================
//------------------------------------------------------------
void CNiveau::setScriptFolder(std::string levelFolder)
{
  this->levelFolder = levelFolder;
}

std::string CNiveau::getScriptFolder() const
{
  return MParameters::getLevelPath() + levelFolder + "/";
}

void CNiveau::setLevelMainFile(std::string levelMainFile)
{
  this->levelMainFile = levelMainFile;
}

std::string CNiveau::getLevelMainFile() const
{
  return levelMainFile;
}

MEntite* CNiveau::getEntite(std::string name)
try
{
  return &entites.at(name);
}
catch (...)
{
  return nullptr;
}

void CNiveau::addEntite(std::string name, std::string texture, MTuile* tuile, float taille)
{
  auto [it, isInserted] = entites.try_emplace(name, name, texture, tuile, taille);
  if (!isInserted)
    throw MExceptionEntiteDejaCreee(name);
  else
  {
    it->second.addObserver(this);
    vuePrincipale->addEntite(name, texture);
    vuePrincipale->setPositionOf(name, tuile->getPosition(), entites.at(name).getDirection());
  }
}

/**
 *
 * @return le chemin du script lua du niveau courrant
 */
std::string CNiveau::getScript() const
{
  return MParameters::getLevelPath() + "/" + levelFolder + "/" + levelMainFile;
}

MTerrain& CNiveau::getTerrain()
{
  return terrain;
}

void CNiveau::addEnigme(std::string nom, std::string description, std::string image)
{
  if (enigmes.count(nom) == 0)
  {
    enigmes.insert( { nom, new VEnigma(nom, image, description) });
  }
}

void CNiveau::afficherEnigme(std::string nom)
{
  enigmes.at(nom)->Show();
}
