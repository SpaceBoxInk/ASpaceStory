/*
 * Caneva.cpp
 *
 *  Created on: 15 déc. 2017
 *      Author: lordofkawaiii
 */

#include "Caneva.hpp"

Canvas::Canvas(wxWindow* parent, wxWindowID id, wxPoint position, wxSize size, long style) :
    wxSfmlCanvas(parent, id, position, size, style)
{
  x = size.x;
  y = size.y;
}

void Canvas::onUpdate()
{
  std::ofstream myfile;
  myfile.open("wallah.txt");
  myfile
      << "1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 0 1 1 1 1 1 1 1 0 0 0 2 0 0 0 0 1 1 0 0 0 0 0 0 3 3 3 3 3 3 3 3 0 1 0 0 2 0 3 3 3 0 1 1 1 0 0 0 0 1 1 0 3 3 3 0 0 0 1 1 1 2 0 0 0 0 1 0 3 0 2 2 0 0 1 1 1 1 2 0 2 0 1 0 3 0 2 2 2 0 1 1 1 1 1 1 0 0 1 0 3 2 2 2 0 0 0 0 1 1 1 1";
  myfile.close();
  std::ofstream h2;
  h2.open("obj.txt");
  h2
      << "0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
  h2.close();
  int const level[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1,
      0, 0, 0, 2, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 0, 1, 0, 0, 2, 0,
      3, 3, 3, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 3, 3, 3, 0, 0, 0, 1, 1, 1, 2, 0, 0, 0, 0, 1, 0,
      3, 0, 2, 2, 0, 0, 1, 1, 1, 1, 2, 0, 2, 0, 1, 0, 3, 0, 2, 2, 2, 0, 1, 1, 1, 1, 1, 1, 0, 0,
      1, 0, 3, 2, 2, 2, 0, 0, 0, 0, 1, 1, 1, 1 };
//  int const level2[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  this->LoadFileIntoGround(level, "texture4.png", 0, 32);
//  meh->LoadFileIntoGround(level2, "texture3.png", 1, 32);
//  meh->addSprite("joseph-staline.png");
//  meh->addSprite("241890516020212.png");
//  meh->setEvent();
  this->clear();
  this->draw(ground);
  this->draw(obj);
  this->draw(sky);
  for (int var = 0; var < sprites.size(); ++var)
  {
    sprites.at(var).setPosition(var * 100, var * 100);
    this->draw(sprites.at(var));
  }

//  this->display();
}

void Canvas::onResize(wxSizeEvent& event)
{
  auto size = event.GetSize();

  auto newCanvasWidth = size.x - (2 * kCanvasMargin);
  auto newCanvasHeight = size.y - (2 * kCanvasMargin);

  // Resize Canvas window
  this->setwxWindowSize( { newCanvasWidth, newCanvasHeight });
  this->setRenderWindowSize( { (unsigned int)newCanvasWidth, (unsigned int)newCanvasHeight });
}
void Canvas::LoadFileIntoGround(int const* file, std::string texture, int level,
                                int tailleTexture)
{
  //TODO : c'est un tableau
  if (level == 0)
    ground.load(texture, sf::Vector2u(tailleTexture, tailleTexture), file, x / tailleTexture,
                y / tailleTexture);
  if (level == 1)
    obj.load(texture, sf::Vector2u(tailleTexture, tailleTexture), file, x, y);
  if (level == 2)
    sky.load(texture, sf::Vector2u(tailleTexture, tailleTexture), file, x, y);

}

TileMap Canvas::getGround()
{
  return ground;
}

TileMap Canvas::getObj()
{
  return obj;
}

TileMap Canvas::getSky()
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

void Canvas::addSprite(std::string file)
{
  setTexture(file);
  sprites.emplace_back();
  sprites.at(sprites.size() - 1).setTexture(*texture.at(texture.size() - 1));
}

void Canvas::setTexture(std::string file)
{
  texture.push_back(new sf::Texture());
  texture.at(texture.size() - 1)->loadFromFile(file);
}

sf::Texture Canvas::getTexture()
{
  return *texture.at(0);
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
    for (int var = 0; var < sprites.size(); ++var)
    {
      std::cout << sprites.size() << std::endl;
      sprites.at(var).setPosition(var * 100, var * 100);
      this->draw(sprites.at(var));
    }

    this->display();
  }
}
