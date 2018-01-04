/*
 * VItem.cpp
 *
 *  Created on: 4 janv. 2018
 *      Author: lordofkawaiii
 */

#include "VItem.hpp"

//------------------------------------------------------------
//========================>Constants<=========================
//------------------------------------------------------------

//------------------------------------------------------------
//=======================>Constructors<=======================
//------------------------------------------------------------

VItem::VItem(wxFrame* parent, wxString file, wxBitmapType format, std::string nom,
             std::string description, unsigned long long int ID) :
    wxImagePanel(parent, file, format), nom(nom), description(description), ID(ID)
{
  // load the file... ideally add a check to see if loading was successful
}

std::string VItem::getNom()
{
  return this->nom;
}

std::string VItem::getDescription()
{
  return this->description;
}

unsigned long long int VItem::getID()
{
  return this->ID;
}

std::string VItem::getFile()
{
  return this->file;
}

void VItem::setNom(std::string nom)
{
  this->nom = nom;
}

void VItem::setDescription(std::string description)
{
  this->description = description;
}

void VItem::setID(unsigned long long int ID)
{
  this->ID = ID;
}

void VItem::setFile(std::string file)
{
  this->file = file;
}




VItem::~VItem()
{
  // TODO Auto-generated destructor stub
}

//------------------------------------------------------------
//=========================>Methods<==========================
//------------------------------------------------------------

//------------------------------------------------------------
//=====================>Getters&Setters<======================
//------------------------------------------------------------

