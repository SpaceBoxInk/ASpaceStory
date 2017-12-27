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
  addAction<MTerrainEvents, MTypeCouche>(
      MTerrainEvents::COUCHE_LOADED,
      [this](MTypeCouche couche, Observed const& o)
      {
        vuePrincipale->loadFileIntoGround(&terrain.getImagesList(couche)[0], MParameters::getTextureFor(couche),
            couche, MParameters::getTailleTuile());
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

std::string CNiveau::getLevelMainFile()
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
}

std::string CNiveau::getScript() const
{
  return MParameters::getLevelPath() + "/" + levelFolder + "/" + levelMainFile;
}

MTerrain& CNiveau::getTerrain()
{
  return terrain;
}

