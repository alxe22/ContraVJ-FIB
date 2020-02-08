#include "SpreadGun.h"
#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Player.h"
#include "Game.h"



SpreadGun::SpreadGun()
{
}

void SpreadGun::initSpread(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	spritesheet.loadFromFile("images/spreadv2.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(48, 30), glm::vec2(1.f, 1.f), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(0);
	sprite->setPosition(glm::vec2(float(126*32+5), float(126)));
}

bool SpreadGun::PlayerColision(glm::vec2 topLeft, int width, int height)
{
	return false;
}

void SpreadGun::update(int deltaTime)
{
	sprite->update(deltaTime);
}

void SpreadGun::render()
{
	sprite->render();
}

void SpreadGun::setTileMap(TileMap * tileMap)
{
	map = tileMap;
}

void SpreadGun::setPosition(const glm::vec2 & pos)
{
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + pos.x), float(tileMapDispl.y + pos.y)));
}


SpreadGun::~SpreadGun()
{
}
