#include "Bullet.h"

enum PlayerAnims
{
	MOVE
};
void Bullet::init(const glm::ivec2 &tileMapPos, const glm::vec2 &pos, const glm::vec2 &dir, int speed, ShaderProgram &shaderProgram)
{
	spritesheet.loadFromFile("images/bullet.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(1.f / 4.f, 1.f / 4.f), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(0);
	sprite->setNumberAnimations(1);

	sprite->setAnimationSpeed(MOVE, 8);
	sprite->addKeyframe(MOVE, glm::vec2(2.f / 4.f, 0.f));

	sprite->changeAnimation(0);
	this->speed = speed;
	this->pos = pos;
	this->dir = dir;
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + this->pos.x), float(tileMapDispl.y + this->pos.y)));
}

void Bullet::update(int deltaTime)
{
	pos.x += dir.x * this->speed;
	pos.y += dir.y * this->speed;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + this->pos.x), float(tileMapDispl.y + this->pos.y)));
}

void Bullet::render()
{
	sprite->render();
}

void Bullet::setTileMap(TileMap *tileMap)
{
	map = tileMap;
}

glm::ivec2 Bullet::getPosition() const
{
	return pos;
}

void Bullet::setFiredBy(const string firedBy)
{
	this->firedBy = firedBy;
}

string Bullet::getFiredBy() const
{
	return this->firedBy;
}
