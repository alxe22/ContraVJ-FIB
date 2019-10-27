#ifndef _PLAYER_INCLUDE
#define _PLAYER_INCLUDE


#include "Sprite.h"
#include "TileMap.h"



// Player is basically a Sprite that represents the player. As such it has
// all properties it needs to track its movement, jumping, and collisions.


class Player
{

public:
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram);
	void initlevel2(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram);
	void update(int deltaTime);
	void updateLv2(int deltaTime, bool canMoveForward);
	void render();
	
	void setTileMap(TileMap *tileMap);
	void setPosition(const glm::vec2 &pos);
	void setPositionLv2(const glm::vec2 &pos);
	glm::ivec2 getPosition();
	int getLifes();
	bool getPower();
	
private:
	bool hasShoot = false;
	int count = 0;
	int PlayerState;
	string PlayerDir;
	glm::ivec2 tileMapDispl, posPlayer;
	int jumpAngle, startY;
	Texture spritesheet;
	Sprite *sprite;
	TileMap *map;
	int RestLifes;
	bool F;
	bool reviving;
	bool swimming;
	bool shooting;
	bool powerup;
	bool RageMode;
	float RageLevel;
	long long DieSec;
	int angle_aux;

};


#endif // _PLAYER_INCLUDE