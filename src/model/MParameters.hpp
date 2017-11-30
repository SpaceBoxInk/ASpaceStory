/**
 * MParameters.hpp
 *
 * Early optimization is the root of all evil
 *
 *  Created on: 5 nov. 2017
 *      Author: nihil
 */

#pragma once

#include <string>
#include <map>
#include <fstream>

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

  static std::string rootPath;
  static std::string resourcesPath;
  static std::string levelPath;
  static std::string tuileInfoPath;

  static std::string solsInfo;
  static std::string elementsInfo;
  static std::string cielsInfo;
  static auto constexpr configFile = "SbiAss.conf";

//========================>Methods<========================
private:
  static bool checkConfFile(std::string path);

  static void setRootPath();

public:
  static std::string const& getRootPath();

  static std::string getConfPath();
  static std::string getTuilePath();
  static std::string getSolsPath();
  static std::string getElementsPath();
  static std::string getCielsPath();

  static void load(std::string exePath);
};
