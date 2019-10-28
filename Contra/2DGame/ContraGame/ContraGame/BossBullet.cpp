#include "BossBullet.h"
#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"



enum BulletAnims
{
	CREATING
};

BossBullet::BossBullet()
{
}


BossBullet::~BossBullet()
{
}

void BossBullet::init(glm::vec2 &pos, glm::vec2 &dir, const glm::ivec2 &tileMapPos, ShaderProgram & shaderProgram)
{
	spritesheet.loadFromFile("images/electric_ball.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(64, 64), glm::vec2(1.f, 1 / 3.f), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(1);

	sprite->setAnimationSpeed(CREATING, 8);
	sprite->addKeyframe(CREATING, glm::vec2(0.f, 0 / 3.f));
	sprite->addKeyframe(CREATING, glm::vec2(0.f, 1 / 3.f));
	sprite->addKeyframe(CREATING, glm::vec2(0.f, 2 / 3.f));

	sprite->changeAnimation(1);
	tileMapDispl = tileMapPos;
	this->pos = pos;
	this->dir = dir;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + this->pos.x), float(tileMapDispl.y + this->pos.y)));
}

void BossBullet::update(int deltaTime)
{
	sprite->update(deltaTime);
	pos.x += dir.x * 3;
	pos.y += dir.y * 3;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + this->pos.x), float(tileMapDispl.y + this->pos.y)));
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