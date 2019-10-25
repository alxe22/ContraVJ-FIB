#include "Sprite.h"
#include "TileMap.h"
#include "BossBullet.h"

using namespace std;

#pragma once
class BossArm
{
public:
	BossArm();
	~BossArm();

	void init(const glm::ivec2 & tileMapPos, ShaderProgram & shaderProgram);
	int getLife();
	void createBullet(glm::vec2 dir, const glm::ivec2 & tileMapPos, ShaderProgram & shaderProgram);
	void update(int deltaTime);
	void render();

	void setTileMap(TileMap *tileMap);
	void setPosition(const glm::vec2 &pos);

private:
	glm::ivec2 tileMapDispl;
	TileMap *map;
	Texture spritesheet;
	Sprite *sprite;
	int Life;
	BossBullet *b;
	glm::vec2 pos;
	
};

