/**
 * MMethodsLoader.hpp
 *
 * Early optimization is the root of all evil
 *
 *  Created on: 31 oct. 2017
 *      Author: nihil
 */

#ifndef SRC_EDITOR_MODEL_MMETHODSLOADER_HPP_
#define SRC_EDITOR_MODEL_MMETHODSLOADER_HPP_

#include <iostream>
#include <map>
#include <string>
#include <vector>

class MMethodsLoader
{
//========================>Attributes<========================
private:
  std::map<std::string, std::vector<std::string>> methodsListCatMEt;
  std::map<std::string, std::string> methodsListMNameMBody;
//=======================>Constructors<=======================
public:
  MMethodsLoader(std::string const& section);
  // TODO: rule of five ? copyandswap
  virtual ~MMethodsLoader() = default;

private:

//=========================>Methods<==========================
public:
  void loadMethods(std::string const& section);
  std::string getMethod(std::string methodeName) const;

private:
  void clearMethods();

  void findSection(std::string section, std::ifstream& f);
  void readSection(std::ifstream& f);
  void readCategorie(std::string& curLine, std::ifstream& f);

  void insertMethod(std::string const& categorie, std::string const& strToParse);
//=====================>Getters&Setters<======================
public:
  std::map<std::string, std::vector<std::string>> const& getListCatMeth() const;
  std::map<std::string, std::string> const& getListMNameMBody() const;

private:

};

#endif /* SRC_EDITOR_MODEL_MMETHODSLOADER_HPP_ */
