/**
 * @file CNiveau.hpp
 *
 * Early optimization is the root of all evil
 * DRY ! Don't repeat yourself
 *
 *  @date 1 déc. 2017
 *  @author FederAndInk
 *  @brief TODO complete
 */

#pragma once

#include "../model/MEntite.hpp"
#include "../model/MParameters.hpp"
#include "../model/MTerrain.hpp"
#include "../outils/ObserverPattern/Observer.hpp"
#include "../model/MEnigme.hpp"

#include <map>
#include <string>


class VPrimitif;

class CNiveau : public Observer
{
//========================>Attributes<========================
private:
  MTerrain terrain;
  std::map<std::string, MEntite> entites;
  VPrimitif* vuePrincipale;
  /**
   * folder for level resources
   */
  std::string levelFolder;
  /**
   * main level script, executed to construct the level
   */
  std::string levelMainFile;
  std::map<std::string, MEnigme> enigmes;
//=======================>Constructors<=======================
public:
  CNiveau(VPrimitif* vuePrincipale, std::string levelFolder =
              MParameters::getMainScriptFolder(),
          std::string levelMainFile = MParameters::getMainScript());
  // TODO: rule of five ? copyandswap
  virtual ~CNiveau();

private:

//=========================>Methods<==========================
public:
  MEntite* getEntite(std::string name);
  void addEntite(std::string name, MTuile* tuile, float taille);
  void addEnigme(std::string nom, std::string description, std::string image);
  void afficherEnigme(std::string nom);
private:
  void setEventMethods();
//=====================>Getters&Setters<======================
public:
  MTerrain& getTerrain();

  void setScriptFolder(std::string levelFolder);
  std::string getScriptFolder() const;
  void setLevelMainFile(std::string levelMainFile);
  std::string getLevelMainFile() const;

  std::string getScript() const;
private:

};
