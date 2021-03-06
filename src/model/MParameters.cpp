
#include "MParameters.hpp"
#include "MAssException.hpp"

#include <fstream>
#include <iostream>

std::map<std::string, std::string> MParameters::conf;
std::string MParameters::rootPath;
std::map<char, Mouvement> MParameters::mouvKeys;
std::map<char, MActionsKey> MParameters::keys;

/**
 * set and check the configroot path
 * @param path new path
 * @return true if we can open this new configRoot path
 */
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

/**
 * init the rootPath with the rootPath itself, it seeking for the rootFile in another known folders
 */
void MParameters::setRootPath()
{
  // check different location for config file
  if (!checkConfFile(rootPath))
    if (!checkConfFile(rootPath += "../src/ressources/"))
      if (!checkConfFile("/etc/Sbi/"))
        if (!checkConfFile("~/.local/share/Sbi/"))
        {
          throw MExceptionFile(configFile, "No config file found");
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


std::string MParameters::getRootPath()
{
  return rootPath;
}

std::string MParameters::getConfPath()
{
  return rootPath + configFile;
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

std::string MParameters::getTextureFor(MTypeCouche couche)
{
  return getTuilePath() + conf["textureCouche" + std::to_string((int)couche)];
}

int MParameters::getTailleTuile()
{
  return std::stoi(conf["tailleTuilePx"]);
}

int MParameters::getNbTuileX()
{
  return std::stoi(conf["nbTuileX"]);
}

int MParameters::getNbTuileY()
{
  return std::stoi(conf["nbTuileY"]);
}

std::string MParameters::getSpritesPath()
{
  return getRootPath() + conf["spritesPath"];;
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

  keys[getKeyFor("interactEnvKey")] = MActionsKey::INTERACT_ENV;
  keys[getKeyFor("interactEntityKey")] = MActionsKey::INTERACT_ENTITY_KEY;
  keys[getKeyFor("attackKey")] = MActionsKey::ATTACK;
  keys[getKeyFor("mineKey")] = MActionsKey::MINE;
  keys[getKeyFor("useKey")] = MActionsKey::USE_MAIN_OBJECT;
  keys[getKeyFor("openEditorKey")] = MActionsKey::OPEN_EDITOR;
  keys[getKeyFor("openInventoryKey")] = MActionsKey::OPEN_INVENTORY;
}

std::string MParameters::getKey(std::string action)
{
  return conf[action];
}
