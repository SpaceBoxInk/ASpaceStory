#include "zones.hpp"
#include "Editor.hpp"

#include "../controler/CEditor.hpp"

#include <wx/wx.h>

#include <string>

Edit::Edit(wxFrame *parent) :
    wxPanel(parent, -1)
{
  text = new wxTextCtrl(parent, -1, wxEmptyString, wxPoint(parent->GetSize().x / 2, -1),
                        wxSize(-1, -1), wxTE_MULTILINE, wxDefaultValidator, wxTextCtrlNameStr);
}

Edit::Edit(wxPanel *parent) :
    wxPanel(parent, -1)
{
  text = new wxTextCtrl(parent, -1, wxEmptyString, wxPoint(parent->GetSize().x / 2, -1),
                        wxSize(-1, -1),
                        wxTE_MULTILINE,
                        wxDefaultValidator, wxTextCtrlNameStr);
}

wxTextCtrl* Edit::getText()
{
  return text;
}

//-----------------------------------------------------------------------------------------
//----------------------------------zone methode-------------------------------------------
//-----------------------------------------------------------------------------------------

/**
 *constructeur de la zone des methodes
 * @param parent
 */
Methodes::Methodes(wxPanel *parent) :
    wxTreeCtrl(parent, -1, wxPoint(-1, -1), wxSize(-1, -1),
    wxTR_HAS_BUTTONS)
{
  Connect(wxID_ANY, wxID_ANY, wxEVT_TREE_ITEM_ACTIVATED,
          wxTreeEventHandler(Methodes::OnTreeClick));

  wxTreeItemId categor = this->AddRoot("Fonctions", -1, -1, nullptr);
  this->Expand(categor);
}

/**
 *gere l'evenement : clique sur le bouton methode 1
 *met meh a la fin de la zone d'edition
 * @param
 */
void Methodes::OnTreeClick(wxTreeEvent & event)
{

  wxTreeItemId itemId = event.GetItem();
  if (GetItemData(itemId))
  {
    MyTreeItemData *item = dynamic_cast<MyTreeItemData *>(GetItemData(itemId)); //on recupere l'item(avec une description)
    std::string meth = item->GetDesc().ToStdString();

    // Envoie du message à l'observeur
    setChanged();
    notifyObservers(Event::METHOD_INPUT, meth);
    UnselectAll(); // plus jolie après avoir écrit
  }
  else
  {
    if (IsExpanded(itemId))
    {
      Collapse(itemId);
    }
    else
    {
      this->Expand(itemId);
    }
  }
}

//void Methodes::OnMethode1(wxCommandEvent & WXUNUSED(event))
//{
//  Editor *comm = (Editor *)this->GetParent();
//  wxTextCtrl *texte = comm->m_edit->text;
//  *texte << "meh" << "\n";
//}
///**
// *gere l'evenement : clique sur le bouton methode 2
// *met wallah a la fin de la zone d'edition
// * @param
// */
//void Methodes::OnMethode2(wxCommandEvent & WXUNUSED(event))
//{
//  Editor *comm = (Editor *)this->GetParent();
//  wxTextCtrl *texte = comm->m_edit->text;
//  *texte << "wallah" << "\n";
//}
