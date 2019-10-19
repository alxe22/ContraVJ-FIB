#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include <glm/glm.hpp>
#include <String.h>
#include "ShaderProgram.h"
#include "SoundSystem.h"
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
	Texture spritesheet, spritesheetSelector, spritesheetControls;
	Sprite *sprite, *spriteSelector, *spriteControls;
	Player *player;
	ShaderProgram texProgram;
	Enemy *enemy;
	float currentTime;
	glm::mat4 projection;
	bool playing = false;
	// testing only
	long long lastSecondFired = 0;

};


#endif // _SCENE_INCLUDE

