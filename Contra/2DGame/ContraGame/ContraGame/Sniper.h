#ifndef _SNIPER_INCLUDE
#define _SNIPER_INCLUDE

#include "Game.h"
#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Enemy.h"


class Sniper : public Enemy
{
public:

	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram) override;
	void update(glm::ivec2 &posPlayer1, glm::ivec2 &posPlayer2, int deltaTime) override;
	void render() override;

	void setTileMap(TileMap *tileMap) override;
	void setPosition(const glm::vec2 &pos) override;
	void setAnimation(int animNum) override;
	glm::ivec2 getPosition() override;
	glm::ivec2 getSize() override;
	string type() override;

	void decideFire(int playerAnim);

private:
	long long lastSecondFired = 0;
	bool bJumping;
	glm::ivec2 tileMapDispl, posPlayer;
	int jumpAngle, startY;
	Texture spritesheet;
	Sprite *sprite;
	TileMap *map;
	int count = 0;
};

#endif