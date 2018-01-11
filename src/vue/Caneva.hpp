/*
 * Caneva.hpp
 *
 *  Created on: 15 déc. 2017
 *      Author: lordofkawaiii
 */

#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <wx/event.h>
#include <wx/gdicmn.h>
#include <wx/windowid.h>
#include <map>
#include <string>
#include <vector>

#include "Tilemap.cpp"
#include "wxSFMLCanevas.hpp"

#include "../model/MCoordonnees.hpp";

class Canvas : public wxSfmlCanvas
{
  //========================>Attributes<========================
private:
  TileMap ground;
  TileMap obj;
  TileMap sky;
  int x;
  int y;
  std::vector<sf::Texture*> textures;
  std::map<std::string, sf::Sprite> sprites;
  int tailleTexture;
  //=======================>Constructors<=======================
public:
  Canvas(wxWindow* parent, wxWindowID id, wxPoint position, wxSize size, long style = 0,
         int TailleTexture = 32);
  virtual ~Canvas();
  virtual void onUpdate();
  std::map<std::string, sf::Sprite>& getSprites();

  //=========================>Methods<==========================
public:
  void loadFileIntoGround(int const* idList, std::string texture, int level,
                          int tailleTexture);

  void drawAll();
  void fermer();
  bool setEvent();
  void addEntite(std::string name, std::string file);
  void move(std::string entityName, MCoordonnees const& offset, Mouvement direction);
  void setPositionOf(std::string entityName, MCoordonnees const& position,
                     Mouvement direction);

private:

  void onResize(wxSizeEvent& event);
  void onRight(wxMouseEvent& event);
  void onCursor(wxMouseEvent& event);
  //=====================>Getters&Setters<======================
public:
private:
  TileMap& getGround();
  TileMap& getObj();
  TileMap& getSky();
  void setTailleTexture(int taille);
  int getTailleTexture();
  sf::Texture* getTexture(int index);
  void setTexture(std::string const& file);
};
