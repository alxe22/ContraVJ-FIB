
#include "Sprite.h"
#include "TileMap.h"

using namespace std;
#pragma once

class SpreadGun
{

public:
	SpreadGun();
	~SpreadGun();
	void initSpread(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram);
	bool PlayerColision(glm::vec2 topLeft, int width, int height);
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

