#include "MParameters.hpp"
#include <exception>
#include <iostream>

namespace AssEditor
{

  std::string MParameters::rootPath;
  std::string MParameters::programsPath;
  std::string MParameters::methodsListFile;
  std::string MParameters::keywordListFile;
  std::string MParameters::font;
  std::string MParameters::lang;
  int MParameters::keywordColor;

  bool MParameters::checkConfFile(std::string path)
  {
    // set the new path
    rootPath = path;
    std::clog << "> check " << getConfPath() << " config file" << '\n';
    // check if file exist
    std::ifstream f;
    f.open(getConfPath());
    bool isOp = f.is_open();
    f.close();
    return isOp;
  }

  void MParameters::setRootPath()
  {
    // check different location for config file
    if (!checkConfFile(rootPath))
      if (!checkConfFile(rootPath += "../src/ressources/"))
        if (!checkConfFile("/etc/Sbi/"))
          if (!checkConfFile("~/.local/share/Sbi/"))
          {
            throw "No config file found";
          }
  }

  std::string const & MParameters::getRootPath()
  {
    return rootPath;
  }

  std::string MParameters::getProgramsPath()
  {
    return rootPath + programsPath;
  }

  std::string MParameters::getMethodsPath()
  {
    return rootPath + methodsListFile;
  }

  std::string MParameters::getConfPath()
  {
    return rootPath + configFile;
  }

  std::string MParameters::getFont()
  {
    return font;
  }

  void MParameters::load(std::string exePath)
  {
    rootPath = exePath.substr(0, exePath.rfind('/') + 1);
    setRootPath();

    std::map<std::string, std::string> conf;
    // load file
    std::ifstream file;
    try
    {
      file.open(getConfPath());
      if (file.is_open())
      {
        while (!file.eof())
        {
          std::string key;
          std::string val;
          file >> key >> val >> val;
          conf[key] = val;
        }
      }
      else
      {
        std::cerr << "Impossible de charger le fichier de configuration " + getConfPath()
            << '\n';
      }
    }
    catch (std::exception& e)
    {
      std::cerr << "Impossible de charger le fichier de configuration " + getConfPath()
          << '\n';
    }
    file.close();
    //=========================================================================================
    // set configurations
    methodsListFile = conf["methodsListFile"];
    keywordListFile = conf["keywordListFile"];
    programsPath = conf["programsPath"];
    font = conf["font"];
    lang = conf["lang"];
    keywordColor = std::stoi(conf["keywordColor"], nullptr, 16);
  }

  std::string const& MParameters::getLang()
  {
    return lang;
  }

  int MParameters::getKeywordColor()
  {
    return keywordColor;
  }

  std::string MParameters::getKeywordsPath()
  {
    return rootPath + keywordListFile;
  }
}

