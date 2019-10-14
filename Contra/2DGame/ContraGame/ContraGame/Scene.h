#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "TileMap.h"
#include "Player.h"
#include "Enemy.h"

// Scene contains all the entities of our game.
// It is responsible for updating and render them.


class Scene
{

public:
	Scene();
	~Scene();
	void loadMenu();
	void menuUpdate(int deltaTime);
	void init();
	void update(int deltaTime);
	void CameraUpdate();
	void render();

private:
	void initShaders();

private:
	TileMap *map;
	Texture spritesheet, spritesheetSelector;
	Sprite *sprite, *spriteSelector;
	Player *player;
	ShaderProgram texProgram;
	Enemy *enemy;
	float currentTime;
	glm::mat4 projection;
	bool playing = false;

};


#endif // _SCENE_INCLUDE

