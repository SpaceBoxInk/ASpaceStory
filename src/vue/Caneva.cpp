/*
 * Caneva.cpp
 *
 *  Created on: 15 déc. 2017
 *      Author: lordofkawaiii
 */

#include "Caneva.hpp"

#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <wx/window.h>
#include <iostream>
#include <utility>

Canvas::Canvas(wxWindow* parent, wxWindowID id, wxPoint position, wxSize size, long style) :
    wxSfmlCanvas(parent, id, position, size, style)
{
  x = size.x;
  y = size.y;
  int const level[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1,
      0, 0, 0, 2, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 0, 1, 0, 0, 2, 0,
      3, 3, 3, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 3, 3, 3, 0, 0, 0, 1, 1, 1, 2, 0, 0, 0, 0, 1, 0,
      3, 0, 2, 2, 0, 0, 1, 1, 1, 1, 2, 0, 2, 0, 1, 0, 3, 0, 2, 2, 2, 0, 1, 1, 1, 1, 1, 1, 0, 0,
      1, 0, 3, 2, 2, 2, 0, 0, 0, 0, 1, 1, 1, 1 };
  int const level2[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  this->LoadFileIntoGround(level, "texture4.png", 0, 32);
  this->LoadFileIntoGround(level2, "texture3.png", 1, 32);
  this->addEntite("Joseph Stalin", "joseph-staline.png");
  this->addEntite("24", "241890516020212.png");


  Connect(this->GetId(), wxEVT_SIZE, wxSizeEventHandler(Canvas::onResize));
  Connect(this->GetId(), wxEVT_RIGHT_DCLICK,
          wxMouseEventHandler(Canvas::onRight));
}

Canvas::~Canvas()
{
}


void Canvas::onUpdate()
{
  this->drawAll();
}

void Canvas::onResize(wxSizeEvent& event)
{
//  auto size = event.GetSize();
//
//  auto newCanvasWidth = size.x - (2 * kCanvasMargin);
//  auto newCanvasHeight = size.y - (2 * kCanvasMargin);
//
//  // Resize Canvas window
//  this->setwxWindowSize( { newCanvasWidth, newCanvasHeight });
//  this->setRenderWindowSize( { (unsigned int)newCanvasWidth, (unsigned int)newCanvasHeight });

//communication entre SFML et WxWidget
  sf::Vector2u si(GetSize().x, GetSize().y);
  sf::RenderWindow::setSize(si);
  drawAll();
}
void Canvas::LoadFileIntoGround(int const* file, std::string texture, int level,
                                int tailleTexture)
{
  //TODO : c'est un tableau
  if (level == 0)
    ground.load(texture, sf::Vector2u(tailleTexture, tailleTexture), file, x / tailleTexture,
                y / tailleTexture);
  if (level == 1)
    obj.load(texture, sf::Vector2u(tailleTexture, tailleTexture), file, x / tailleTexture,
             y / tailleTexture);
  if (level == 2)
    sky.load(texture, sf::Vector2u(tailleTexture, tailleTexture), file, x / tailleTexture,
             y / tailleTexture);

}

TileMap& Canvas::getGround()
{
  return ground;
}

TileMap& Canvas::getObj()
{
  return obj;
}

TileMap& Canvas::getSky()
{
  return sky;
}

int Canvas::getX()
{
  return x;
}

bool Canvas::open()
{
  return this->isOpen();
}

void Canvas::fermer()
{
  this->close();
}

//TODO set a rien, les events sont pas géré par sfml
bool Canvas::setEvent()
{
  sf::Event event;
  while (this->pollEvent(event))
  {
    switch (event.type) {
    case sf::Event::Closed:
      this->close();
      break;
    case sf::Event::MouseButtonPressed:
      switch (event.mouseButton.button) {
      case sf::Mouse::Right:

        std::cout << "meh";
      }
      break;
//    default:
//      std::cout << "wallah" << std::endl;
    }
  }
}

void Canvas::addEntite(std::string name, std::string file)
{
  setTexture(file);
  auto pair = sprites.try_emplace(name);
  if (pair.second)
  {
    sprites.at(name).setTexture(*getTexture(texture.size() - 1));
  }
}

void Canvas::setTexture(std::string const& file)
{
  texture.push_back(new sf::Texture());
  getTexture(texture.size() - 1)->loadFromFile(file);
}

sf::Texture* Canvas::getTexture(int index)
{
  return texture.at(index);
}

int Canvas::getY()
{
  return y;
}

void Canvas::drawAll()
{
  if (this->isOpen())
  {
    this->clear();
    this->draw(ground);
    this->draw(obj);
    this->draw(sky);
    for (auto& pair : sprites)
    {
      this->draw(sprites.at(pair.first));
    }

    this->display();
  }
}

void Canvas::onRight(wxMouseEvent& event)
{
  sf::Sprite& sp = getSprites().at("Joseph Stalin");
//  sp.setPosition(sp.getPosition().x + 10, sp.getPosition().y + 20);
  sp.move(20, 20);
  cout << getSprites().at("Joseph Stalin").getPosition().x << " " << sp.getPosition().x
      << endl;
  drawAll();
}


std::map<std::string, sf::Sprite>& Canvas::getSprites()
{
  return this->sprites;
}
