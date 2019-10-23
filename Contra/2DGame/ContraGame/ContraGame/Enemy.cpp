#include "Enemy.h"

void Enemy::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
}

void Enemy::update(glm::ivec2 &posPlayer1, glm::ivec2 &posPlayer2, int deltaTime)
{
}

void Enemy::render()
{
}


void Enemy::setTileMap(TileMap *tileMap)
{
}

void Enemy::setPosition(const glm::vec2 &pos)
{
}

void Enemy::setAnimation(int animNum) 
{
}

int Enemy::getAnimation() 
{
	return -1;
}

glm::ivec2 Enemy::getPosition()
{
	return glm::ivec2(-1, -1);
}

glm::ivec2 Enemy::getSize()
{
	return glm::ivec2(-1, -1);
}

string Enemy::type()
{
	return "";
}