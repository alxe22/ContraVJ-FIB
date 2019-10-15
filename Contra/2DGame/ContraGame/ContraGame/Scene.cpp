#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"
#include "Game.h"
#include "SoundSystem.h"
#include "Soldier.h"
#include "EnemyManager.h"
#include "BulletManager.h"

#define SCREEN_X 32
#define SCREEN_Y 16

#define INIT_PLAYER_X_TILES 4
#define INIT_PLAYER_Y_TILES 1


Scene::Scene()
{
	map = NULL;
	player = NULL;
}

Scene::~Scene()
{
	if(map != NULL)
		delete map;
	if(player != NULL)
		delete player;
}

void Scene::loadMenu() {
	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	
	// background
	spritesheet.loadFromFile("images/menu.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(640, 480), glm::vec2(1.f, 1.f), &spritesheet, &texProgram);
	sprite->setNumberAnimations(0);
	sprite->setPosition(glm::vec2(float(0), float(0)));
	
	// selector
	spritesheetSelector.loadFromFile("images/selector.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spriteSelector = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(1.f, 1.f), &spritesheetSelector, &texProgram);
	spriteSelector->setNumberAnimations(0);
	spriteSelector->setPosition(glm::vec2(float(200), float(263)));
}

void Scene::menuUpdate(int deltaTime) {
	sprite->update(deltaTime);
	if (Game::instance().getSpecialKey(GLUT_KEY_DOWN)) {
		glm::vec2 posSelector = spriteSelector->getPosition();
		if(posSelector.y < 293) posSelector.y += 15.f;
		//posSelector.y += 5.f;
		spriteSelector->setPosition(posSelector);
		spriteSelector->render();
	}
	else if (Game::instance().getSpecialKey(GLUT_KEY_UP)) {
		glm::vec2 posSelector = spriteSelector->getPosition();
		if (posSelector.y > 263) posSelector.y -= 15.f;
		//posSelector.y -= 5.f;
		spriteSelector->setPosition(posSelector);
		spriteSelector->render();
	}
	// return key == 13
	else if (Game::instance().getKey(13)) {
		if ((spriteSelector->getPosition()).y == 263 || 
			(spriteSelector->getPosition()).y == 278) state = "PLAYING";
		else state = "CONTROLS";
		init();
	}
}

void Scene::controlsUpdate(int deltaTime) {
	spriteControls->update(deltaTime);
	if (Game::instance().getKey('b') || Game::instance().getKey('B')) {
		state = "MENU";
		init();
	}
}

void Scene::loadControls() {
	// controls
	spritesheetControls.loadFromFile("images/controls.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spriteControls = Sprite::createSprite(glm::ivec2(640, 480), glm::vec2(1.f, 1.f), &spritesheetControls, &texProgram);
	spriteControls->setNumberAnimations(0);
	spriteControls->setPosition(glm::vec2(float(0), float(0)));
}

void Scene::init()
{
	initShaders();
	//map = TileMap::createTileMap("levels/level01.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	//el vector ens indica des d'on comencem a pintar el primer tile en la pantalla
	if (state == "MENU") loadMenu();
	else if (state == "CONTROLS") loadControls();
	else {
		map = TileMap::createTileMap("levels/leveltest.txt", glm::vec2(0, 0), texProgram);
		player = new Player();
		player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		player->setPosition(glm::vec2((INIT_PLAYER_X_TILES * map->getTileSize()) - 32, INIT_PLAYER_Y_TILES * map->getTileSize()));
		player->setTileMap(map);
		projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
		currentTime = 0.0f;
		//SoundSystem *sy = SoundSystem::createSoundSystem("level01");
		EnemyManager::instance().initEnemies(190, 0, 0, texProgram, map);
		BulletManager::instance().initBulletManager(texProgram, map);
	}
}

void Scene::update(int deltaTime)
{
	currentTime += deltaTime;
	if (state == "MENU") {
		menuUpdate(deltaTime);
	}
	else if (state == "CONTROLS") {
		controlsUpdate(deltaTime);
	}
	else {
		player->update(deltaTime);
		//enemy->update(glm::ivec2(-1, -1), glm::ivec2(-1, -1), deltaTime);
		EnemyManager::instance().updateEnemies(player->getPosition(), player->getPosition(), deltaTime);
		BulletManager::instance().update(player->getPosition(), player->getPosition(), deltaTime);
		CameraUpdate();
	}
}

void Scene::CameraUpdate()
{
	glm::ivec2 pos = player->getPosition();
	float posCameraX = 0.0f;
	if (pos.x >= 240) posCameraX = pos.x-240;

	projection = glm::ortho(posCameraX, float(SCREEN_WIDTH - 1)+posCameraX, float(SCREEN_HEIGHT - 1), 0.f);
}

void Scene::render()
{
	glm::mat4 modelview;

	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);
	if (state == "MENU") {
		sprite->render();
		spriteSelector->render();
	}
	else if (state == "CONTROLS") {
		spriteControls->render();
	}
	else {
		map->render();
		player->render();
		EnemyManager::instance().render();
		BulletManager::instance().render();
	}
}

void Scene::initShaders()
{
	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/texture.vert");
	if(!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/texture.frag");
	if(!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	texProgram.init();
	texProgram.addShader(vShader);
	texProgram.addShader(fShader);
	texProgram.link();
	if(!texProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << texProgram.log() << endl << endl;
	}
	texProgram.bindFragmentOutput("outColor");
	vShader.free();
	fShader.free();
}



