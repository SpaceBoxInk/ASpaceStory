/*
 * VPlayerInventory.cpp
 *
 *  Created on: 5 janv. 2018
 *      Author: lordofkawaiii
 */

#include "VPlayerInventory.hpp"

#include <wx/string.h>
#include <wx/window.h>
#include <algorithm>
#include <iterator>
#include <string>
#include <vector>

#include "../model/MAssException.hpp"
#include "../model/MCoordonnees.hpp"
#include "VItem.hpp"

//------------------------------------------------------------
//========================>Constants<=========================
//------------------------------------------------------------

//------------------------------------------------------------
//=======================>Constructors<=======================
//------------------------------------------------------------

VPlayerInventory::VPlayerInventory(wxString const & title, MCoordonnees coord) :
    VPlayerInventaireInterface(coord), VInventory(title, coord)
{

}

VPlayerInventory::~VPlayerInventory()
{
  // TODO Auto-generated destructor stub
}

void VPlayerInventory::addObjPlayerQuickInv(unsigned long long id, std::string name,
                                            std::string description, std::string image,
                                            int position)
{
  if (position != -1)
  {
    VItem* ite = Quick.at(position);
    ite->LoadImage(image);
    ite->SetName(name);
    ite->setDescription(description);
    ite->setID(id);
  }
  else
  {
    auto ite = std::find_if(Quick.begin(), Quick.end(), [id](VItem* item) -> bool
    {
      return item->getFile() == "nothingInventory.png";
    });
    if (ite == Quick.end())
    {
      throw MAssException("plus de place dans l'inventaire");
    }
    else
    {
      (*ite)->LoadImage(image);
      (*ite)->SetName(name);
      (*ite)->setDescription(description);
      (*ite)->setID(id);
    }
  }
}

void VPlayerInventory::delObjInv(unsigned long long id)
{
  try
  {
    VInventory::delObjInv(id);
  }
  catch (MAssException)
  {
    auto itemToDel = std::find_if(Quick.begin(), Quick.end(), [id](VItem* item) -> bool
        {
          return item->getID() == id;
        });
    if (itemToDel == Quick.end())
    {
      throw MAssException("je n'ai pas pu trouver l'objet à supprimer");
    }
    else
    {
      (*itemToDel)->LoadImage("nothingInventory.png");
    }
  }
}
//------------------------------------------------------------
//=========================>Methods<==========================
//------------------------------------------------------------

//------------------------------------------------------------
//=====================>Getters&Setters<======================
//------------------------------------------------------------

