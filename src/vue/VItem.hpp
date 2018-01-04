/*
 * VItem.hpp
 *
 *  Created on: 4 janv. 2018
 *      Author: lordofkawaiii
 */

#pragma once

#include <wx/wx.h>
#include <wx/string.h>
#include <string>

#include "ImagePanel.hpp"


class VItem : public wxImagePanel
{
//========================>Attributes<========================
private:
  std::string nom;
  std::string description;
  unsigned long long int ID;
  std::string file;
//=======================>Constructors<=======================
public:
  VItem(wxFrame* parent, wxString file, wxBitmapType format, std::string nom = "hitler",
        std::string description = "dictateur allemand", unsigned long long int ID = 1);
  // TODO: rule of five ? copyandswap
  virtual ~VItem();

private:

//=========================>Methods<==========================
public:
  std::string getNom();
  std::string getDescription();
  unsigned long long int getID();
  std::string getFile();

  void setNom(std::string nom);
  void setDescription(std::string description);
  void setID(unsigned long long int ID);
  void setFile(std::string file);

private:

//=====================>Getters&Setters<======================
public:

private:

};
