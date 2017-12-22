/*
 * Caneva.hpp
 *
 *  Created on: 15 déc. 2017
 *      Author: lordofkawaiii
 */

#pragma once

#include "Tilemap.cpp"
#include "wxSFMLCanevas.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <wx/event.h>
#include <wx/gdicmn.h>
#include <wx/windowid.h>
#include <map>
#include <string>
#include <vector>

class Canvas : public wxSfmlCanvas
{
  //========================>Attributes<========================
private:
  TileMap ground;
  TileMap obj;
  TileMap sky;
  int x;
  int y;
  std::vector<sf::Texture*> texture;
  std::map<std::string, sf::Sprite> sprites;
  //=======================>Constructors<=======================
public:
  Canvas(wxWindow* parent, wxWindowID id, wxPoint position, wxSize size, long style = 0);
  virtual ~Canvas();
  virtual void onUpdate();

  //=========================>Methods<==========================
public:
  void loadFileIntoGround(int const* idList, std::string texture, int level,
                          int tailleTexture);

  void drawAll();
  void fermer();
  bool setEvent();
  void addEntite(std::string name, std::string file);
private:

  void onResize(wxSizeEvent& event);
  void onRight(wxMouseEvent& event);
  //=====================>Getters&Setters<======================
public:
private:
  TileMap& getGround();
  TileMap& getObj();
  TileMap& getSky();
  sf::Texture* getTexture(int index);
  void setTexture(std::string const& file);
  std::map<std::string, sf::Sprite>& getSprites();
};
