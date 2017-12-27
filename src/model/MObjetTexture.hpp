/**
 * @file MObjetTexture.hpp
 *
 * Early optimization is the root of all evil
 * DRY ! Don't repeat yourself
 *
 *  @date 25 déc. 2017
 *  @author FederAndInk
 *  @brief TODO complete
 */

#pragma once

#include <string>

class MObjetTexture
{
//========================>Attributes<========================
private:
  std::string texture;
//=======================>Constructors<=======================
public:
  MObjetTexture(std::string texture);
  // TODO: rule of five ? copyandswap
  virtual ~MObjetTexture();

private:

//=========================>Methods<==========================
public:

private:

//=====================>Getters&Setters<======================
public:
  std::string getTexture();
  void setTexture(std::string texture);

private:

};

inline std::string MObjetTexture::getTexture()
{
  return texture;
}

inline void MObjetTexture::setTexture(std::string texture)
{
  this->texture = texture;
}
//------------------------------------------------------------
//=====================>Implementations<======================
//------------------------------------------------------------

