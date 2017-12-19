
#include "MParameters.hpp"

#include <bits/exception.h>
#include <fstream>
#include <iostream>

std::map<std::string, std::string> MParameters::conf;
std::string MParameters::rootPath;
std::map<char, Mouvement> MParameters::mouvKeys;
std::map<char, MActionsKey> MParameters::keys;

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

char MParameters::getKeyFor(std::string const & action)
{
  if (conf[action] == "space")
  {
    return ' ';
  }
  else
  {
    return conf[action][0];
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
  mouvKeys[getKeyFor("upKey")] = Mouvement::HAUT;
  mouvKeys[getKeyFor("downKey")] = Mouvement::BAS;
  mouvKeys[getKeyFor("leftKey")] = Mouvement::GAUCHE;
  mouvKeys[getKeyFor("rightKey")] = Mouvement::DROITE;

  keys[getKeyFor("interactEnvKey")] = MActionsKey::INTERACT_ENV_KEY;
  keys[getKeyFor("attackKey")] = MActionsKey::ATTACK;
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

MActionsKey MParameters::getActionFromKey(char key)
{
  return keys.at(key);
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

bool MParameters::isActionKey(char key)
try
{
  keys.at(key);
  return true;
}
catch (...)
{
  return false;
}
