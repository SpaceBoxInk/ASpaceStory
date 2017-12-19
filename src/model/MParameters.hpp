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

enum class MActionsKey
{
  INTERACT_ENV_KEY,
  ATTACK,
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
  static std::map<char, MActionsKey> keys;

//========================>Methods<========================
private:
  static bool checkConfFile(std::string path);

  static void setRootPath();

  static char getKeyFor(std::string const& action);
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
  static MActionsKey getActionFromKey(char key);
  static bool isMouvKey(char key);
  static bool isActionKey(char key);

  static void load(std::string exePath);
};
