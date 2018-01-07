/**
 * @file MSave.cpp
 *
 * Early optimization is the root of all evil
 *
 *  @date 22 nov. 2017
 *  @author FederAndInk
 *  @brief TODO complete
 */

#include "../../editor/model/MSave.hpp"

#include "../../editor/model/MParameters.hpp"
#include "../../editor/tools/utils.hpp"

#include <sstream>
#include <stdexcept>

using namespace AssEditor;

//------------------------------------------------------------
//========================>Constants<=========================
//------------------------------------------------------------

//------------------------------------------------------------
//=======================>Constructors<=======================
//------------------------------------------------------------

MSave::MSave(std::string const& fileName)
{
  setFileName(fileName);
}

MSave::~MSave()
{
}

//------------------------------------------------------------
//=========================>Methods<==========================
//------------------------------------------------------------
void MSave::save(std::string const& content)
{
  file.open(getFilePath(), std::ios::out);
  std::cout << content << '\n';
  file << content;
  if (!file.fail())
  {
    printLog("Program Saved", LogType::OK);
  }
  else
  {
    printLog("Fail to save Program !!", LogType::ERROR);
  }
  file.close();
}

void MSave::load(std::string& content)
{
  file.open(getFilePath(), std::ios::in);
  content = "";
  std::string buf;
  while (!file.eof())
  {
    std::getline(file, buf);
    content += buf + (!file.eof() ? "\n" : "");
  }
  file.close();
}


//------------------------------------------------------------
//=====================>Getters&Setters<======================
//------------------------------------------------------------
void MSave::setFileName(std::string const& fileName)
{
  if (std::fstream(MParameters::getProgramsPath() + fileName, std::ios::app).good())
  {
    this->fileName = fileName;
    printLog("Program File : " + getFilePath(), LogType::OK);
  }
  else
  {
    throw
  std::invalid_argument(
        "Can not acces to file" + getFilePath());
  }
}

std::string MSave::getFilePath()
{
  return MParameters::getProgramsPath() + fileName;
}
