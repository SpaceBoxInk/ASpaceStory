/*
 * editor.cpp
 *
 *  Created on: 3 nov. 2017
 *      Author: lordofkawaiii
 */

#include "Editor.hpp"

#include "../model/MParameters.hpp"
#include "../view/zones.hpp"

#include "../controler/CEditor.hpp"
#include "../tools/utils.hpp"

#include <cctype>
#include <wx/wx.h>
#include <utility>

using namespace AssEditor;

/**
 *
 * @param title
 */
Editor::Editor(wxString const & title) :
    wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(830, 600), wxSTAY_ON_TOP)
{
  this->SetMinSize(wxSize(500, 300)); //la taille minimum

  //----------------------------------------------------------

  wxBoxSizer* hbox = new wxBoxSizer(wxVERTICAL); //le sizer generale
  wxBoxSizer* hbox2 = new wxBoxSizer(wxHORIZONTAL); //le sizer "du bas", contient la zone de retour et les boutons
  wxBoxSizer* hbox3 = new wxBoxSizer(wxVERTICAL); //le sizer des boutons
  wxBoxSizer* hbox4 = new wxBoxSizer(wxHORIZONTAL); //le sizer "du haut", contient les methodes et le zone d'edition

  wxPanel *haut = new wxPanel(this); //le panel "du haut", contient les methodes et le zone d'edition
  wxPanel *bas = new wxPanel(this); //le panel "du bas", contient la zone de retour et les boutons
  wxPanel *bouttons = new wxPanel(bas); //le panel des boutons

  m_methode = new Methodes(haut);
  m_edit = new wxTextCtrl(haut, wxID_EDIT, wxEmptyString, wxPoint(-1, -1), wxSize(-1, -1),
  wxTE_MULTILINE,
                          wxDefaultValidator, wxTextCtrlNameStr);

  wxFont font(wxFontInfo(10).FaceName(MParameters::getFont()));

  m_edit->SetFont(font);
  Connect(wxID_EDIT, wxEVT_TEXT, wxCommandEventHandler(Editor::OnChange));
  m_res = new wxTextCtrl(bas, -1, wxEmptyString, wxPoint(-1, -1), wxSize(-1, -1),
  wxTE_MULTILINE,
                         wxDefaultValidator, wxTextCtrlNameStr);

//  m_edit->SetFont(wxSystemSettings::GetFont(wxSYS_ANSI_FIXED_FONT));
  // FIXME : change or do something for encoding

  SetIcon(wxIcon(MParameters::getRootPath() + "/pictures/icon.png")); //on met le logo sympa

  //les boutons
  hbox3->Add(new wxButton(bouttons, wxID_ADD, wxT("Executer"), wxPoint(-1, -1)), 1, wxEXPAND);
  hbox3->Add(new wxButton(bouttons, wxID_CANCEL, wxT("Arreter/Recommencer"), wxPoint(-1, -1)),
             1, wxEXPAND);
  hbox3->Add(new wxButton(bouttons, wxID_EXIT, wxT("Fermer"), wxPoint(-1, -1)), 1, wxEXPAND);

  Connect(wxID_EXIT, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(Editor::OnQuit));
  Connect(wxID_CANCEL, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(Editor::OnAbort));
  Connect(wxID_ADD, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(Editor::OnAdd));

  //la zone du bas
  hbox2->Add(m_res, 3, wxEXPAND);
  hbox2->Add(bouttons, 1, wxEXPAND);

  //la zone du haut
  hbox4->Add(m_methode, 1, wxEXPAND);
  hbox4->Add(m_edit, 3, wxEXPAND);

  //la zone generale
  hbox->Add(haut, 5, wxEXPAND);
  hbox->Add(bas, 1, wxEXPAND);

  bouttons->SetSizer(hbox3);
  haut->SetSizer(hbox4);
  bas->SetSizer(hbox2);
  this->SetSizer(hbox);

  Centre();

}

/**
 *
 * @param
 */
void Editor::OnAbort(wxCommandEvent & WXUNUSED(event))
{
  setChanged();
  notifyObservers(Event::ABORT);
}

/**
 *
 * @param
 */
void Editor::OnAdd(wxCommandEvent & WXUNUSED(event))
{

  if (thread.valid())
  {
    thread.wait();
  }
  setChanged();
  thread = std::async(std::launch::async, [&]
  { notifyObservers(Event::EXECUTE_EDITOR, getEditContent());});
}
/**
 *
 * @param
 */
void Editor::OnChange(wxCommandEvent& event)
{
  printLog("j'appuie sur une lettre", LogType::DEBUG);
  setChanged();
  notifyObservers(Event::SYNTAX);
}
/**
 *
 * @param
 */
void Editor::OnQuit(wxCommandEvent & WXUNUSED(event))
{
  setChanged();
  notifyObservers(Event::SAVE_AND_CLOSE_EDITOR, getEditContent());
  Show(false);
}

/**
 *
 * @return
 */
wxTextCtrl* Editor::getRes() const
{
  return m_res;
}

/**
 *
 * @return
 */
wxTextCtrl* Editor::getEdit() const
{
  return m_edit;
}

/**
 *
 * @param pos la position que l'on veut
 * @return le caractere à la position pour 0 -> 'c' :c'est
 */
char Editor::getChar(wxTextCoord pos) const
{
  if (pos >= 0)
  {
    return m_edit->GetRange(pos, pos + 1).ToStdString()[0];
  }
  return 0;
}

/**
 *
 */
wxTextCoord* Editor::getMot(std::string& mot) const
{
  long point = m_edit->GetInsertionPoint();
  long pointp = point;
  long pointm = point - 1;
  char c = getChar(pointp);
  while (isalnum(c) || c == '_') //on pushback la lettre suivante
  {
    mot.push_back(c);
    ++pointp;
    c = getChar(pointp);
  } //on a fini les caracteres suivants
  //on fait le même chose avec les lettre devant la position initiale

  c = getChar(pointm);
  while ((isalnum(c) || c == '_')) //on pushback la lettre precedente
  {
    mot = c + mot;
    --pointm;
    c = getChar(pointm);
  }
  wxTextCoord* range = new wxTextCoord[2];
  range[0] = pointm + 1;
  range[1] = pointp;
  return range;
}

/**
 *
 * @return
 */
Methodes* Editor::getMethodes() const
{
  return m_methode;
}

/**
 *
 * @param methode
 */
void Editor::writeMet(std::string methode, wxColour const* color)
{
  wxTextCtrl* text = getEdit(); //on recupere la zone d'edition
  wxTextAttr att = wxTextAttr(*color);
  att.SetAlignment(wxTextAttrAlignment::wxTEXT_ALIGNMENT_JUSTIFIED);
  att.SetFontEncoding(wxFontEncoding::wxFONTENCODING_UTF8);
  text->SetDefaultStyle(att);
  text->WriteText(wxString(methode.c_str(), wxConvUTF8));
//  text->AppendText(methode);
  text->SetFocus(); // SEE : pratique ;) pour donner le focus au texte après les methodes
}

/**
 *
 * @param retur
 */
void Editor::writeRes(std::string retur, wxColour const* color)
{
  wxTextCtrl* text = getRes(); //on recupere la zone de retour
  // SEE : to call with parallelism !
  text->CallAfter([&, color, retur]
  {
    getRes()->SetDefaultStyle(wxTextAttr(*color));
    getRes()->AppendText(wxString(retur.c_str(), wxConvUTF8));
  });
}

void Editor::clearRes()
{
  wxTextCtrl* text = getRes(); //on recupere la zone de retour
  text->Clear();
}

void Editor::ajouterMethode(std::map<std::string, std::vector<std::string> > liste)
{
  supprimerMethodes();
  wxTreeItemId categor = m_methode->GetRootItem();
  for (auto categorie : liste)
  {
    wxTreeItemId catego = m_methode->AppendItem(categor, categorie.first, -1, -1, nullptr);
    for (std::string methode : categorie.second)
    {
      // wxTreeItemId truc =
      m_methode->AppendItem(catego, methode, -1, -1, new MyTreeItemData(methode));
    }
  }
  m_methode->Expand(categor);
}

void Editor::supprimerMethodes()
{
  m_methode->CollapseAndReset(m_methode->GetRootItem());
}

wxColour const * Editor::getDefaultColor()
{
  static auto defCol = wxSystemSettings::GetColour(wxSystemColour::wxSYS_COLOUR_WINDOWTEXT);
  return &defCol;
}

std::string Editor::getIndentation() const
{
  std::string indent;
  long pos = m_edit->GetInsertionPoint() - 1;

  printLog("Current char : " + std::to_string((int)getChar(pos)), LogType::DEBUG);
  for (int i = 0; isblank(getChar(pos)); ++i, --pos)
  {
    indent += getChar(pos);
    printLog(std::string("Current char : ") + getChar(pos), LogType::DEBUG);
  }
  printLog("indent size : " + std::to_string(indent.size()), LogType::DEBUG);
  return indent;
}
