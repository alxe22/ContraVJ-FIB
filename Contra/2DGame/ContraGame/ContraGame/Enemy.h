#ifndef _ENEMY_INCLUDE
#define _ENEMY_INCLUDE

#include "Sprite.h"
#include "TileMap.h"
#include <string>

using namespace std;

class Enemy
{
public:

	virtual void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram);
	virtual void update(glm::ivec2 &posPlayer1, glm::ivec2 &posPlayer2, int deltaTime);
	virtual void render();

	virtual void setTileMap(TileMap *tileMap);
	virtual void setPosition(const glm::vec2 &pos);
	virtual void setAnimation(int animNum);
	virtual int getAnimation();
	virtual glm::ivec2 getPosition();
	virtual glm::ivec2 getSize();
	virtual string type();
};

#endif