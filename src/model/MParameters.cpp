
#include "MParameters.hpp"

#include <bits/exception.h>
#include <fstream>
#include <iostream>

std::map<std::string, std::string> MParameters::conf;
std::string MParameters::rootPath;
std::map<char, Mouvement> MParameters::mouvKeys;

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
  mouvKeys[conf["upKey"][0]] = Mouvement::HAUT;
  mouvKeys[conf["downKey"][0]] = Mouvement::BAS;
  mouvKeys[conf["leftKey"][0]] = Mouvement::GAUCHE;
  mouvKeys[conf["rightKey"][0]] = Mouvement::DROITE;
}

std::string MParameters::getSolsPath()
{
  return getTuilePath() + conf["solsInfo"];
}

std::string MParameters::getElementsPath()
{
  return getTuilePath() + conf["elementsInfo"];
}

std::string MParameters::getCielsPath()
{
  return getTuilePath() + conf["cielsInfo"];
}

std::string MParameters::getTuilePath()
{
  return rootPath + conf["tuileInfoPath"] + "/";
}

std::string MParameters::getLevelPath()
{
  return rootPath + conf["levelPath"] + "/";
}

std::string MParameters::getMainScriptFolder()
{
  return conf["mainScriptFolder"] + "/";
}

std::string MParameters::getMainScript()
{
  return conf["mainScript"];
}

Mouvement MParameters::getMouvFromKey(char key)
{
  return mouvKeys.at(key);
}

bool MParameters::isMouvKey(char key)
try
{
  mouvKeys.at(key);
  return true;
}
catch (...)
{
  return false;
}
