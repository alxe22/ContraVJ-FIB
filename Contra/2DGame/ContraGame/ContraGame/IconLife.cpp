#include "IconLife.h"
#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"


IconLife::IconLife()
{
}


IconLife::~IconLife()
{
}

void IconLife::init(const glm::ivec2 & tileMapPos, ShaderProgram & shaderProgram)
{
	spritesheet.loadFromFile("images/lifes.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(1.f, 1.f), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(0);
}

void IconLife::update(int deltaTime)
{
	sprite->update(deltaTime);
}

void IconLife::render()
{
	sprite->render();
}

void IconLife::setTileMap(TileMap * tileMap)
{
	map = tileMap;
}

void IconLife::setPosition(const glm::vec2 & pos)
{
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + pos.x), float(tileMapDispl.y + pos.y)));
}
