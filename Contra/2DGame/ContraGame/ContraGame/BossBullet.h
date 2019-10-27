#include "Sprite.h"
#include "TileMap.h"

using namespace std;

#pragma once
class BossBullet
{
public:
	BossBullet();
	~BossBullet();

	void init(glm::vec2 &pos, glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram);
	void update(int deltaTime, glm::vec2 dir);
	void render();

	void setTileMap(TileMap *tileMap);
	void setPosition(const glm::vec2 &pos);

private:
	glm::ivec2 tileMapDispl;
	TileMap *map;
	Texture spritesheet;
	Sprite *sprite;
	glm::vec2 pos;
};
