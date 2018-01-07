/*
 * editor.hpp
 *
 *  Created on: 3 nov. 2017
 *      Author: lordofkawaiii
 */

#pragma once

#include "../../outils/ObserverPattern/Observed.hpp"

#include <wx/wx.h>
#include <future>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#define wxUSE_UNICODE 1

class Edit;
class Methodes;

/**
 * classe principale de l'editeur qui contient une zone d'edition, de methodes, de retour et 3 boutons
 */
class Editor : public wxFrame, public Observed
{
private:
  //========================>Attributes<========================
  /**
   *
   */
  wxTextCtrl *m_edit;
  /**
   *
   */
  wxTextCtrl *m_res;
  /**
   *
   */
  Methodes *m_methode;
  /**
   *
   */
  std::future<void> thread;

public:
  //=======================>Constructors<=======================
  Editor(wxString const & title);

  //=========================>Methods<==========================
  static wxColour const* getDefaultColor();

  void OnQuit(wxCommandEvent & event);
  void OnAbort(wxCommandEvent & WXUNUSED(event));
  void OnAdd(wxCommandEvent & WXUNUSED(event));
  void OnChange(wxCommandEvent& event);

  void writeMet(std::string methode, wxColour const* color = getDefaultColor());
  void writeRes(std::string methode, wxColour const* color = getDefaultColor());
  void clearRes();

  void ajouterMethode(std::map<std::string, std::vector<std::string> > liste);
  void supprimerMethodes();

  char getChar(wxTextCoord pos) const;
  wxTextCoord* getMot(std::string& motRet) const;
  std::string getIndentation() const;
  //=====================>Getters&Setters<======================
  wxTextCtrl* getEdit() const;
  inline std::string getEditContent() const;
  wxTextCtrl* getRes() const;
  Methodes* getMethodes() const;
};

inline std::string Editor::getEditContent() const
{
  std::stringstream sstr;
  sstr << getEdit()->GetValue().mb_str(wxConvUTF8);
  return sstr.str();
}
