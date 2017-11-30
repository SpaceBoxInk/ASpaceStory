
#include "MParameters.hpp"

#include <bits/exception.h>
#include <iostream>

std::string MParameters::rootPath;
std::string MParameters::resourcesPath;
std::string MParameters::levelPath;
std::string MParameters::tuileInfoPath;
std::string MParameters::solsInfo;
std::string MParameters::elementsInfo;
std::string MParameters::cielsInfo;


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

std::string MParameters::getConfPath()
{
  return rootPath + configFile;
}

void MParameters::load(std::string exePath)
{
  rootPath = exePath.substr(0, exePath.rfind('/') + 1);
  setRootPath();

  std::map < std::string, std::string > conf;
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
    std::cerr << "Impossible de charger le fichier de configuration " + getConfPath() << '\n';
  }
  file.close();
  //=========================================================================================
  // set configurations
  resourcesPath = conf["resourcesPath"];
  tuileInfoPath = conf["tuileInfoPath"];
  levelPath = conf["levelPath"];
  solsInfo = conf["solsInfo"];
  elementsInfo = conf["elementsInfo"];
  cielsInfo = conf["cielsInfo"];
}

std::string MParameters::getSolsPath()
{
  return getTuilePath() + solsInfo;
}

std::string MParameters::getElementsPath()
{
  return getTuilePath() + elementsInfo;
}

std::string MParameters::getCielsPath()
{
  return getTuilePath() + cielsInfo;
}

std::string MParameters::getTuilePath()
{
  return rootPath + resourcesPath + tuileInfoPath;
}
