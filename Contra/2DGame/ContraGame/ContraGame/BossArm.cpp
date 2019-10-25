#include "BossArm.h"
#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"


BossArm::BossArm()
{
}


BossArm::~BossArm()
{
}

void BossArm::init(const glm::ivec2 & tileMapPos, ShaderProgram & shaderProgram)
{
	Life = 20;
	spritesheet.loadFromFile("images/electric_ball.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(64, 64), glm::vec2(1/4.f, 1/4.f), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(0);
}

int BossArm::getLife()
{
	return Life;
}

void BossArm::createBullet(glm::vec2 dir, const glm::ivec2 & tileMapPos, ShaderProgram & shaderProgram)
{
	//b->init(pos,tileMapPos, shaderProgram);
}

void BossArm::update(int deltaTime)
{
	sprite->update(deltaTime);
}

void BossArm::render()
{
	sprite->render();
}

void BossArm::setTileMap(TileMap * tileMap)
{
	map = tileMap;
}

void BossArm::setPosition(const glm::vec2 & pos)
{
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + pos.x), float(tileMapDispl.y + pos.y)));
	this->pos = pos;
}
