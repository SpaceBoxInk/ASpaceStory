/**
 * MMethodsLoader.cpp
 *
 * Early optimization is the root of all evil
 *
 *  Created on: 31 oct. 2017
 *      Author: nihil
 */

#include "../../editor/model/MMethodsLoader.hpp"

#include "../../editor/model/MParameters.hpp"
#include "../../editor/tools/utils.hpp"

#include <cstdio>
#include <regex>
#include <utility>

using namespace AssEditor;
using namespace std;

//------------------------------------------------------------
//========================>Constants<=========================
//------------------------------------------------------------

//------------------------------------------------------------
//=======================>Constructors<=======================
//------------------------------------------------------------

MMethodsLoader::MMethodsLoader(string const& section)
{
  loadMethods (section);
}


//------------------------------------------------------------
//=========================>Methods<==========================
//------------------------------------------------------------
void MMethodsLoader::loadMethods(std::string const & section)
{
  clearMethods();
  ifstream f(MParameters::getMethodsPath());
  findSection(section, f);
  readSection(f);
}

std::string MMethodsLoader::getMethod(std::string methodeName) const
{
  return methodsListMNameMBody.at(methodeName);
}


void MMethodsLoader::clearMethods()
{
  methodsListCatMEt.clear();
  methodsListMNameMBody.clear();
}

void MMethodsLoader::findSection(std::string section, std::ifstream& f)
{
  string line;
  regex re(section + "\\s*\\{");
  // define the worker to find the section
  function<void()> worker = [&line, &re, &f, &worker]() -> void
  {
    getline(f, line);
    if (!f.eof() && !regex_search(line, re))
    {
      worker();
    }
  };
  // call the worker
  worker();
}

void MMethodsLoader::readSection(std::ifstream& f)
{
  string curLine;
  getline(f, curLine);

  regex reEnd("\\s*\\}");

  function<void()> worker = [&]() -> void
  {
    readCategorie(curLine, f);
    if (!f.eof() && !regex_search(curLine, reEnd))
    {
      worker();
    }
  };
  worker();
}

void MMethodsLoader::readCategorie(string& curLine, std::ifstream& f)
{
  regex reCat("\\w*\\s*\\{");
  regex reEnd("\\s*\\}");
  cmatch result;
  regex_search(curLine.c_str(), result, reCat);

  string categorie = result[0].str().substr(0, result[0].str().size() - 1);
  categorie = trim(categorie);

  function<void()> worker = [&]() -> void
  {
    getline(f, curLine);
    if (!f.eof() && !regex_search(curLine, reEnd))
    {
      insertMethod(categorie, curLine);
      worker();
    }
    else
    {
      // on a fini de lire la catégorie, il faut avancer pour la suivante
      getline(f, curLine);
    }
  };
  worker();

}

void MMethodsLoader::insertMethod(std::string const & categorie, std::string const& strToParse)
{
  regex reMetName("(\\w+|\\w+\\s*)+(?=\\s*::=)");

  std::cmatch methodName;

  regex_search(strToParse.c_str(), methodName, reMetName);
  std::string methodBody = trim(methodName.suffix());
  methodBody = trim(methodBody.substr(3, methodBody.size()));

  printLog(
      "insert '" + methodName.str() + "' with body '" + methodBody + "' into " + categorie,
      LogType::INFO);
  methodsListCatMEt.try_emplace(categorie);
  methodsListCatMEt[categorie].push_back(methodName.str());
  methodsListMNameMBody[methodName.str()] = methodBody;
}
//------------------------------------------------------------
//=====================>Getters&Setters<======================
//------------------------------------------------------------

std::map<std::string, std::vector<std::string> > const & MMethodsLoader::getListCatMeth() const
{
  return methodsListCatMEt;
}

std::map<std::string, std::string> const & MMethodsLoader::getListMNameMBody() const
{
  return methodsListMNameMBody;
}
