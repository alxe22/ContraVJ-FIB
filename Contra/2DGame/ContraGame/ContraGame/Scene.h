#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include <glm/glm.hpp>
#include <String.h>
#include "ShaderProgram.h"
#include "TileMap.h"
#include "Player.h"
#include "Enemy.h"
#include "SpreadGun.h"
#include "IconLife.h"

// Scene contains all the entities of our game.
// It is responsible for updating and render them.


class Scene
{

public:
	Scene();
	~Scene();
	void loadMenu();
	void loadControls();
	void menuUpdate(int deltaTime);
	void controlsUpdate(int deltaTime);
	void init();
	void update(int deltaTime);
	void CameraUpdate();
	void render();

private:
	void initShaders();

private:
	string state = "MENU"; // MENU, CONTROLS, PLAYING
	TileMap *map;
	Texture spritesheet, spritesheetSelector, spritesheetControls, spritesheetLifes, spritesheetPower;
	Sprite *sprite, *spriteSelector, *spriteControls, *spriteLifes, *spritePower;
	Player *player;
	ShaderProgram texProgram;
	Enemy *enemy;
	SpreadGun *spread;
	IconLife *Icon1,*Icon2, *Icon3;
	float currentTime;
	glm::mat4 projection;
	bool playing = false;
	float limitCamera;

};


#endif // _SCENE_INCLUDE

