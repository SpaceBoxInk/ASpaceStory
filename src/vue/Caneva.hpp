/*
 * Caneva.hpp
 *
 *  Created on: 15 déc. 2017
 *      Author: lordofkawaiii
 */
#include "wxSFMLCanevas.hpp"
#include "Tilemap.cpp"
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

  virtual void onUpdate();

  //=========================>Methods<==========================
public:
  void LoadFileIntoGround(int const* file, std::string texture, int level, int tailleTexture);

  void drawAll();
  bool open();
  void fermer();
  bool setEvent();
  void addEntite(std::string name, std::string file);
private:

  void onResize(wxSizeEvent& event);
  void onRight(wxMouseEvent& event);
  //=====================>Getters&Setters<======================
public:
  TileMap getGround();
  TileMap getObj();
  TileMap getSky();
  sf::Texture getTexture();
  void setTexture(std::string file);
  int getX();
  int getY();
  std::map<std::string, sf::Sprite> getSprites();
private:
};
