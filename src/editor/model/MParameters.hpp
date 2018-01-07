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

namespace AssEditor
{
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
    static std::string programsPath;
    static auto constexpr configFile = "SbiEditor.conf";
    static std::string methodsListFile;
    static std::string keywordListFile;
    static std::string font;
    static std::string lang;
    static int keywordColor;

//========================>Methods<========================
  private:
    static bool checkConfFile(std::string path);

    static void setRootPath();

  public:
    static std::string const& getRootPath();

    static std::string getProgramsPath();

    static std::string getMethodsPath();
    static std::string getKeywordsPath();

    static std::string getConfPath();

    static std::string getFont();

    static int getKeywordColor();

    static std::string const& getLang();

    static void load(std::string exePath);
  };
}

