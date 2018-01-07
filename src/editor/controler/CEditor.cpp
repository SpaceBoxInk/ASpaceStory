/**
 * CMethods.cpp
 *
 * Early optimization is the root of all evil
 *
 *  Created on: 5 nov. 2017
 *      Author: nihil
 */

#include "CEditor.hpp"

#include "../model/MParameters.hpp"
#include "../tools/utils.hpp"
#include "../view/Editor.hpp"
#include "../view/zones.hpp"

#include <stddef.h>
#include <wx/chartype.h>
#include <wx/gtk/colour.h>
#include <wx/gtk/textctrl.h>
#include <wx/gtk/toplevel.h>
#include <wx/textentry.h>
#include <cctype>
#include <fstream>
#include <map>
#include <regex>
#include <utility>

class MTerrain;

using namespace AssEditor;
using namespace std;

//------------------------------------------------------------
//========================>Constants<=========================
//------------------------------------------------------------

wxColour CEditor::keywordColor;

//------------------------------------------------------------
//=======================>Constructors<=======================
//------------------------------------------------------------

CEditor::CEditor(MTerrain* terrain) :
    methodsLoader("all" + MParameters::getLang()), save("defaultProgram.lua"),
    ihmEditor(new Editor(wxT("Editeur"))), luaInterpreter(terrain, ihmEditor)
{
  keywordColor = wxColour(MParameters::getKeywordColor());
  addEvents();

  std::ifstream keywords;
  keywords.open(MParameters::getKeywordsPath());
  std::string line;
  while (!keywords.eof())
  {
    std::getline(keywords, line);
    listeKey.insert(line);
  }
  keywords.close();

  // IHM init
  ihmEditor->getMethodes()->addObserver(this);
  ihmEditor->addObserver(this);
  ihmEditor->ajouterMethode(methodsLoader.getListCatMeth());

  string loaded;
  save.load(loaded);
  writeColoredMet(loaded);
}

CEditor::~CEditor()
{
}

void CEditor::addEvents()
{
  // Action pour quand l'utilisateur clic sur une methode fournie
  // dans l'arbre
  addAction<Event, string>(Event::METHOD_INPUT, [&](string content, Observed const&) -> void
  {
    string method = methodsLoader.getMethod(content);
    vector<wxTextCoord> wordRepList;
    formatMethod(method, wordRepList);
    writeColoredMet(method);
    if (!wordRepList.empty())
    {
      ihmEditor->getEdit()->SetSelection(wordRepList[0], wordRepList[1]);
    }
  });

  addAction<Event>(
      Event::SYNTAX,
      [&](Observed const&)
      {
        std::string mot;

        wxTextCoord* coo = ihmEditor->getMot(mot);
        if (listeKey.find(mot) != listeKey.end())
        {
          printLog(string("coords : ") + to_string(coo[0]) + string(" ") + to_string(coo[1]) + " : colored", LogType::DEBUG);
          ihmEditor->getEdit()->SetStyle(coo[0],coo[1], (wxTextAttr)keywordColor);
        }
        else
        {
          printLog(string("coords : ") + to_string(coo[0]) + string(" ") + to_string(coo[1]) + " : not colored", LogType::DEBUG);
          ihmEditor->getEdit()->SetStyle(coo[0],coo[1], (wxTextAttr)*Editor::getDefaultColor());
        }
      });

  addAction<Event, string>(Event::SAVE_AND_CLOSE_EDITOR, [&](string content, Observed const&)
  {
    printLog("Save and quit : Bye", LogType::INFO);
    save.save(content);
  });

  addAction<Event, string>(Event::EXECUTE_EDITOR, [&](string content, Observed const&)
  {
    printLog("Save and execute : yeah", LogType::INFO);
    save.save(content);
    ihmEditor->clearRes();
    luaInterpreter.execute(save.getFilePath());
  });

  addAction(Event::ABORT, [&](Observed const&)
  {
    luaInterpreter.interrupt();
  });
}

void CEditor::writeColoredMet(std::string const& method)
{
  string motCur = "";
  for (char c : method)
  {
    if (isalnum(c) || c < 0)
    {
      motCur += c;
    }
    else
    {
      writeColoredMot(motCur);
      ihmEditor->writeMet(string() + c);
      motCur = "";
    }
  }
  writeColoredMot(motCur);
}

void CEditor::writeColoredMot(std::string const& mot)
{
  // FIXME : coloration faite 2 fois :/
  if (listeKey.find(mot) != listeKey.end())
  {
    ihmEditor->writeMet(mot, &keywordColor);
  }
  else
  {
    ihmEditor->writeMet(mot);
  }
}

/**
 *
 * @param method
 * @return the position of the cursor
 */
wxTextCoord CEditor::formatMethod(std::string& method, vector<wxTextCoord> & wordRepCoord)
{
  printLog("Parsing : " + method);
  regex reNli("\\$\\[nli\\]");
  regex reNl("\\$\\[nl\\]");
  regex reTab("\\$\\[tab\\]");
  regex reCursor("\\$\\[cursor\\]");

  regex reOthers("\\$\\[((\\w|\\d)+)\\]");

  method = regex_replace(method, reNli, "\n" + ihmEditor->getIndentation());
  method = regex_replace(method, reNl, "\n");
  method = regex_replace(method, reTab, "\t");
  method = regex_replace(method, reCursor, "");

  smatch mOthers;
  if (regex_search(method, mOthers, reOthers))
  {
    size_t pos = mOthers.prefix().str().size() + ihmEditor->getEdit()->GetInsertionPoint();
    printLog("Pos of first other word : " + to_string(pos), LogType::DEBUG);
    wordRepCoord.push_back(pos);
    // insert the position to end of first Other word (minus 3 for "$[]")
    wordRepCoord.push_back(mOthers[0].str().size() - 3 + pos);
  }

  method = regex_replace(method, reOthers, "$1"); //TODO complete for tab ;)

  printLog("Transformation : " + method);
}

void CEditor::setProgramName(std::string programName, MRobot* robot)
{
  luaInterpreter.setRobot(robot);

  save.save(ihmEditor->getEditContent());

  save.setFileName(programName);

  std::string content;
  save.load(content);

  ihmEditor->getEdit()->Clear();
  ihmEditor->SetLabel("Editeur : " + programName);
  writeColoredMet(content);
}

void CEditor::loadMethods(std::string method)
{
  methodsLoader.loadMethods(method);
}

void CEditor::showEditor(bool show)
{
  if (ihmEditor->GetLabel() != "Editeur")
    ihmEditor->Show(show);
}
//------------------------------------------------------------
//=====================>Getters&Setters<======================
//------------------------------------------------------------

