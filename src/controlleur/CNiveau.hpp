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

#include "../model/MParameters.hpp"
#include "../model/MTerrain.hpp"
#include "../outils/ObserverPattern/Observer.hpp"

#include <string>

class VPrimitif;

class CNiveau : public Observer
{
//========================>Attributes<========================
private:
  MTerrain terrain;
  std::map<std::string, MEntite*> entites;
  VPrimitif* vuePrincipale;
  /**
   * folder for level resources
   */
  std::string levelFolder;
  /**
   * main level script, executed to construct the level
   */
  std::string levelMainFile;
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
private:
  void setEventMethods();
//=====================>Getters&Setters<======================
public:
  MTerrain& getTerrain();

  void setScriptFolder(std::string levelFolder);
  std::string getLevelFolder() const;
  void setLevelMainFile(std::string levelMainFile);
  std::string getScript() const;
private:

};
