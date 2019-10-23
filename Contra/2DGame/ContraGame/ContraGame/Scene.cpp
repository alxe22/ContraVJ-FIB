#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"
#include "Game.h"
#include "Soldier.h"
#include "EnemyManager.h"
#include "BulletManager.h"
#include "Time.h"

#define SCREEN_X 32
#define SCREEN_Y 16

#define INIT_PLAYER_X_TILES 4
#define INIT_PLAYER_Y_TILES 1

// testing only
# define FIRE_FRAME_INTERVAL 500

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
		if(posSelector.y < 293) posSelector.y += 30.f;
		//posSelector.y += 5.f;
		spriteSelector->setPosition(posSelector);
		spriteSelector->render();
	}
	else if (Game::instance().getSpecialKey(GLUT_KEY_UP)) {
		glm::vec2 posSelector = spriteSelector->getPosition();
		if (posSelector.y > 263) posSelector.y -= 30.f;
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
	if (state == "MENU") {
		loadMenu();
		SoundSystem::instance().playMusic("", "MENU");
	}
	else if (state == "CONTROLS") loadControls();
	else {
		/*map = TileMap::createTileMap("levels/leveltest.txt", glm::vec2(0, 0), texProgram);
		player = new Player();
		player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		player->setPosition(glm::vec2((INIT_PLAYER_X_TILES * map->getTileSize()) - 32, INIT_PLAYER_Y_TILES * map->getTileSize()));
		player->setTileMap(map);
		projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
		currentTime = 0.0f;
		SoundSystem::instance().playMusic("level01", state);
		BulletManager::instance().initBulletManager(texProgram, map);*/
		EnemyManager::instance().initEnemies(190, 0, 0, texProgram, map);
		BulletManager::instance().initBulletManager(texProgram, map);
		spritesheet.loadFromFile("images/stage2v4.png", TEXTURE_PIXEL_FORMAT_RGBA);
		sprite = Sprite::createSprite(glm::ivec2(640, 480), glm::vec2(1.f / 4.f, 1.f / 5.f), &spritesheet, &texProgram);
		sprite->setNumberAnimations(20);
		
		sprite->setAnimationSpeed(0, 8);
		sprite->addKeyframe(0, glm::vec2(0 / 4.f, 0.f / 5.f));

		sprite->setAnimationSpeed(1, 8);
		sprite->addKeyframe(1, glm::vec2(1 / 4.f, 0.f / 5.f));

		sprite->setAnimationSpeed(2, 8);
		sprite->addKeyframe(2, glm::vec2(2 / 4.f, 0.f / 5.f));

		sprite->setAnimationSpeed(3, 8);
		sprite->addKeyframe(3, glm::vec2(3 / 4.f, 0.f / 5.f));

		//

		sprite->setAnimationSpeed(4, 8);
		sprite->addKeyframe(4, glm::vec2(0 / 4.f, 1.f / 5.f));

		sprite->setAnimationSpeed(5, 8);
		sprite->addKeyframe(5, glm::vec2(1 / 4.f, 0.f / 5.f));

		sprite->setAnimationSpeed(6, 8);
		sprite->addKeyframe(6, glm::vec2(2 / 4.f, 0.f / 5.f));

		sprite->setAnimationSpeed(7, 8);
		sprite->addKeyframe(7, glm::vec2(3 / 4.f, 0.f / 5.f));

		//

		sprite->setAnimationSpeed(8, 8);
		sprite->addKeyframe(8, glm::vec2(0 / 4.f, 2.f / 5.f));

		sprite->setAnimationSpeed(9, 8);
		sprite->addKeyframe(9, glm::vec2(1 / 4.f, 0.f / 5.f));

		sprite->setAnimationSpeed(10, 8);
		sprite->addKeyframe(10, glm::vec2(2 / 4.f, 0.f / 5.f));

		sprite->setAnimationSpeed(11, 8);
		sprite->addKeyframe(11, glm::vec2(3 / 4.f, 0.f / 5.f));

		//

		sprite->setAnimationSpeed(12, 8);
		sprite->addKeyframe(12, glm::vec2(0 / 4.f, 3.f / 5.f));

		sprite->setAnimationSpeed(13, 8);
		sprite->addKeyframe(13, glm::vec2(1 / 4.f, 0.f / 5.f));

		sprite->setAnimationSpeed(14, 8);
		sprite->addKeyframe(14, glm::vec2(2 / 4.f, 0.f / 5.f));

		sprite->setAnimationSpeed(15, 8);
		sprite->addKeyframe(15, glm::vec2(3 / 4.f, 0.f / 5.f));

		//

		sprite->setAnimationSpeed(16, 8);
		sprite->addKeyframe(16, glm::vec2(0 / 4.f, 4.f / 5.f));

		sprite->setAnimationSpeed(17, 8);
		sprite->addKeyframe(17, glm::vec2(1 / 4.f, 0.f / 5.f));

		sprite->setAnimationSpeed(18, 8);
		sprite->addKeyframe(18, glm::vec2(2 / 4.f, 0.f / 5.f));

		sprite->setAnimationSpeed(19, 8);
		sprite->addKeyframe(19, glm::vec2(3 / 4.f, 0.f / 5.f));

		sprite->changeAnimation(0);

		sprite->setPosition(glm::vec2(float(0), float(0)));

		player = new Player();
		player->initlevel2(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		player->setPosition(glm::vec2((2 * 32), 9 * 32));
		projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
		currentTime = 0.0f;
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
		/*player->update(deltaTime);
		EnemyManager::instance().updateEnemies(player->getPosition(), player->getPosition(), deltaTime, "level01");
		BulletManager::instance().update(player->getPosition(), player->getPosition(), deltaTime, "level01");
		EnemyManager::instance().detectBulletCollisions();
		CameraUpdate();*/
		player->updateLv2(deltaTime, false);
		EnemyManager::instance().updateEnemies(player->getPosition(), player->getPosition(), deltaTime, "level02");
		BulletManager::instance().update(player->getPosition(), player->getPosition(), deltaTime, "level02");
		long long diff = Time::instance().NowToMili() - lastSecondFired;
		if (diff > FIRE_FRAME_INTERVAL) {
			lastSecondFired = Time::instance().NowToMili();
			if (Game::instance().getSpecialKey(GLUT_KEY_UP)) sprite->changeAnimation(sprite->animation() + 1);
			else if (Game::instance().getSpecialKey(GLUT_KEY_DOWN)) sprite->changeAnimation(sprite->animation() - 1);
		}
	}
}

void Scene::CameraUpdate()
{
	glm::ivec2 pos = player->getPosition();
	float posCameraX = 0.0f;
	if (pos.x >= 240) posCameraX = pos.x-240;

	projection = glm::ortho(posCameraX, float(SCREEN_WIDTH - 1)+posCameraX, float(SCREEN_HEIGHT - 1), 0.f);
}

void Scene::level2Update(int deltaTime)
{
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
		/*map->render();
		player->render();
		EnemyManager::instance().render();
		BulletManager::instance().render();*/
		sprite->render(); //coment this line when testing level01
		player->render(); //coment this line when testing level01
		EnemyManager::instance().render(); //coment this line when testing level01
		BulletManager::instance().render(); //coment this line when testing level01
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



