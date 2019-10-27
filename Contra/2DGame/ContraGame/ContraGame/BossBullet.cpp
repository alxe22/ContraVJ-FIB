#include "BossBullet.h"
#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"



BossBullet::BossBullet()
{
}


BossBullet::~BossBullet()
{
}

void BossBullet::init(glm::vec2 &pos, glm::ivec2 & tileMapPos, ShaderProgram & shaderProgram)
{
	spritesheet.loadFromFile("images/bub.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(1 / 4.f, 1 / 4.f), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(0);
	this->pos = pos;
}

void BossBullet::update(int deltaTime, glm::vec2 dir)
{
	sprite->update(deltaTime);

}

void BossBullet::render()
{
	sprite->render();
}

void BossBullet::setTileMap(TileMap * tileMap)
{
	map = tileMap;
}

void BossBullet::setPosition(const glm::vec2 & pos)
{
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + pos.x), float(tileMapDispl.y + pos.y)));
}