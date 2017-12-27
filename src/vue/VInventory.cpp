/*
 * inventory.cpp
 *
 *  Created on: 22 déc. 2017
 *      Author: lordofkawaiii
 */

#include "VInventory.hpp"

//------------------------------------------------------------
//========================>Constants<=========================
//------------------------------------------------------------

//------------------------------------------------------------
//=======================>Constructors<=======================
//------------------------------------------------------------

inventory::inventory(wxString const & title, wxString file, std::string texte) :
    wxFrame(NULL, wxID_ANY, title, wxPoint(-1, -1), wxSize(340, 340), wxSTAY_ON_TOP)
{
  picture = new wxImagePanel(this, file, wxBITMAP_TYPE_PNG);
  text = new wxTextCtrl(this, wxID_ANY, texte, wxPoint(-1, -1), wxSize(20, 20), wxTE_READONLY);
  wxBoxSizer* hbox = new wxBoxSizer(wxVERTICAL);

  hbox->Add(picture, 9, wxEXPAND);
  hbox->Add(text, 1, wxEXPAND);
  hbox->Add(new wxButton(this, wxID_EXIT, wxT("ok"), wxPoint(-1, -1)), 1, wxEXPAND);

  Connect(wxID_EXIT, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(inventory::OnQuit));

  this->SetSizer(hbox);
}

inventory::~inventory()
{
  // TODO Auto-generated destructor stub
}

void inventory::OnQuit(wxCommandEvent&)
{
  Close(true);
}
//------------------------------------------------------------
//=========================>Methods<==========================
//------------------------------------------------------------

//------------------------------------------------------------
//=====================>Getters&Setters<======================
//------------------------------------------------------------

