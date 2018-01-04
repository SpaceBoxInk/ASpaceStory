/*
 * VInventory.cpp
 *
 *  Created on: 4 janv. 2018
 *      Author: lordofkawaiii
 */

#include "VInventory.hpp"
#include "../model/MAssException.hpp"

//------------------------------------------------------------
//========================>Constants<=========================
//------------------------------------------------------------

//------------------------------------------------------------
//=======================>Constructors<=======================
//------------------------------------------------------------

VInventory::VInventory(wxString const & title,
                       MCoordonnees taille) :
    VInventaireInterface(taille),
    wxFrame(NULL, wxID_ANY, title, wxPoint(-1, -1), wxSize(500, 500),
    wxSTAY_ON_TOP | wxDEFAULT_FRAME_STYLE)
{
  wxBoxSizer* hbox = new wxBoxSizer(wxVERTICAL);
  wxGridSizer* grid = new wxGridSizer(taille.getX(), taille.getY(), 1, 1);

  for (int var = 0; var < taille.getX() * taille.getY(); ++var)
  {
    items.push_back(
        new VItem(this, wxT("nothingInventory.png"), wxBITMAP_TYPE_PNG, "rien", "rien", 0));
  }

  for (unsigned int var = 0; var < items.size(); ++var)
  {
    grid->Add(items.at(var), 1, wxEXPAND);
  }
//  grid->Add(new VItem(this, "nothingInventory.png", wxBITMAP_TYPE_PNG, "rien", "rien", 0),
//            wxEXPAND);
  hbox->Add(grid, 1, wxEXPAND);
  this->SetSizer(hbox);
}

VInventory::~VInventory()
{
  // TODO Auto-generated destructor stub
}


void VInventory::addObjInv(unsigned long long id, std::string name, std::string description,
                           std::string image, int position)
{
  if (position != -1)
  {
    VItem* ite = items.at(position);
    ite->LoadImage(image);
    ite->SetName(name);
    ite->setDescription(description);
    ite->setID(id);
  }
  else
  {
    VItem* itemToDel = *std::find_if(items.begin(), items.end(), [id](VItem* item) -> bool
    {
      return item->getFile() == "nothingInventory.png";
    });
    itemToDel->LoadImage(image);
    itemToDel->SetName(name);
    itemToDel->setDescription(description);
    itemToDel->setID(id);
  }
}


void VInventory::delObjInv(unsigned long long id)
{
  VItem* itemToDel = *std::find_if(items.begin(), items.end(), [id](VItem* item) -> bool
  {
    return item->getID() == id;
  });
  if (itemToDel == *items.end())
  {
    throw MAssException("je n'ai pas pu trouver l'objet à supprimer");
  }
  else
  {
    delete itemToDel;
  }
}

void VInventory::show(bool show)
{
  this->Show(show);
}
//------------------------------------------------------------
//=========================>Methods<==========================
//------------------------------------------------------------

//------------------------------------------------------------
//=====================>Getters&Setters<======================
//------------------------------------------------------------

