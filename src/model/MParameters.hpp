/**
 * MParameters.hpp
 *
 * Early optimization is the root of all evil
 *
 *  Created on: 5 nov. 2017
 *      Author: nihil
 */

#pragma once

#include "MCoordonnees.hpp"

#include <map>
#include <string>

/**
 * Enum for languages
 */
enum class Lang
{
  EN, //!< EN
  FR, //!< FR
};

/**
 * List of parameters for editor
 */
class MParameters
{
//========================>Constant<========================
private:

  static std::map<std::string, std::string> conf;
  static auto constexpr configFile = "SbiAss.conf";
  static std::string rootPath;

  static std::map<char, Mouvement> mouvKeys;

//========================>Methods<========================
private:
  static bool checkConfFile(std::string path);

  static void setRootPath();

public:
  static std::string const& getRootPath();

  static std::string getConfPath();
  static std::string getTuilePath();
  static std::string getLevelPath();

  static std::string getMainScriptFolder();
  static std::string getMainScript();

  static std::string getSolsPath();
  static std::string getElementsPath();
  static std::string getCielsPath();

  static Mouvement getMouvFromKey(char key);
  static bool isMouvKey(char key);

  static void load(std::string exePath);
};
