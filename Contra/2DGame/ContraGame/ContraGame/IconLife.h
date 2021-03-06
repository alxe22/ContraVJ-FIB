
#include "Sprite.h"
#include "TileMap.h"

using namespace std;
#pragma once

class IconLife
{
public:
	IconLife();
	~IconLife();

	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram);
	void update(int deltaTime);
	void render();

	void setTileMap(TileMap *tileMap);
	void setPosition(const glm::vec2 &pos);

private:
	glm::ivec2 tileMapDispl;
	TileMap *map;
	Texture spritesheet;
	Sprite *sprite;
};

