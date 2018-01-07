/**
 * @file MSave.hpp
 *
 * Early optimization is the root of all evil
 *
 *  @date 22 nov. 2017
 *  @author FederAndInk
 *  @brief TODO complete
 */

#pragma once

#include <iostream>
#include <fstream>
#include <string>

class MSave
{
//========================>Attributes<========================
private:
  std::string fileName;
  std::fstream file;
//=======================>Constructors<=======================
public:
  MSave(std::string const& fileName);
  // TODO: rule of five ? copyandswap
  virtual ~MSave();

private:

//=========================>Methods<==========================
public:
  void save(std::string const& content);
  void load(std::string& content);
private:

//=====================>Getters&Setters<======================
public:
  void setFileName(std::string const& fileName);
  std::string getFilePath();
private:

};
