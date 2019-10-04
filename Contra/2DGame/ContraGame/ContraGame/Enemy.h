#ifndef _ENEMY_INCLUDE
#define _ENEMY_INCLUDE

#include "Sprite.h"
#include "TileMap.h"

class Enemy
{
public:

	virtual void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram);
	virtual void update(int deltaTime);
	virtual void render();

	virtual void setTileMap(TileMap *tileMap);
	virtual void setPosition(const glm::vec2 &pos);
	virtual glm::ivec2 getPosition();
};

#endif