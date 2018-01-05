/*
 * inventory.cpp
 *
 *  Created on: 22 déc. 2017
 *      Author: lordofkawaiii
 */

#include "VEnigma.hpp"

//------------------------------------------------------------
//========================>Constants<=========================
//------------------------------------------------------------

//------------------------------------------------------------
//=======================>Constructors<=======================
//------------------------------------------------------------

VEnigma::VEnigma(wxString const & title, wxString file, std::string texte) :
    wxFrame(NULL, wxID_ANY, title, wxPoint(-1, -1), wxSize(340, 340),
            wxSTAY_ON_TOP | wxDEFAULT_FRAME_STYLE)
{
  picture = new wxImagePanel(this, file, wxBITMAP_TYPE_PNG);
  text = new wxTextCtrl(this, wxID_ANY, texte, wxPoint(-1, -1), wxSize(20, 20), wxTE_READONLY);
  wxBoxSizer* hbox = new wxBoxSizer(wxVERTICAL);

  hbox->Add(picture, 9, wxEXPAND);
  hbox->Add(text, 1, wxEXPAND);
  hbox->Add(new wxButton(this, wxID_EXIT, wxT("Ok"), wxPoint(-1, -1)), 1, wxEXPAND);

  Connect(wxID_EXIT, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(VEnigma::OnQuit));

  this->SetSizer(hbox);
}

VEnigma::~VEnigma()
{
  delete text;
  delete picture;
}

void VEnigma::OnQuit(wxCommandEvent&)
{
  Show(false);
}
//------------------------------------------------------------
//=========================>Methods<==========================
//------------------------------------------------------------

//------------------------------------------------------------
//=====================>Getters&Setters<======================
//------------------------------------------------------------

