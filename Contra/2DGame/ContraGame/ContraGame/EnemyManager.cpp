#include "EnemyManager.h"
#include "BulletManager.h"
#include "Soldier.h"
#include "Sniper.h"
#include "Turret.h"
#include "SuperTurret.h"

#define SCREEN_X 32
#define SCREEN_Y 16

#define LEVEL01_TILE_WIDTH 77
#define LEVEL01_TILE_HEIGHT 8

void EnemyManager::loadSnipers(string level, ShaderProgram &shaderProgram, TileMap *tileMap) 
{
	Enemy *enemy;
	enemy = new Sniper();
	enemy->init(glm::ivec2(SCREEN_X, SCREEN_Y), shaderProgram);
	enemy->setPosition(glm::vec2(18 * tileMap->getTileSize(), 9 * tileMap->getTileSize()));
	enemy->setTileMap(tileMap);
	enemies.push_back(enemy);

	enemy = new Sniper();
	enemy->init(glm::ivec2(SCREEN_X, SCREEN_Y), shaderProgram);
	enemy->setPosition(glm::vec2(38 * tileMap->getTileSize(), 9 * tileMap->getTileSize()));
	enemy->setTileMap(tileMap);
	enemies.push_back(enemy);

	enemy = new Sniper();
	enemy->init(glm::ivec2(SCREEN_X, SCREEN_Y), shaderProgram);
	enemy->setPosition(glm::vec2(78 * tileMap->getTileSize(), 2 * tileMap->getTileSize()));
	enemy->setTileMap(tileMap);
	enemy->setAnimation(10);
	enemies.push_back(enemy);

	enemy = new Sniper();
	enemy->init(glm::ivec2(SCREEN_X, SCREEN_Y), shaderProgram);
	enemy->setPosition(glm::vec2(113 * tileMap->getTileSize(), 9 * tileMap->getTileSize()));
	enemy->setTileMap(tileMap);
	enemies.push_back(enemy);
}

void EnemyManager::loadTurrets(string level, ShaderProgram &shaderProgram, TileMap *tileMap) 
{
	Enemy *enemy;
	enemy = new Turret();
	enemy->init(glm::ivec2(SCREEN_X, SCREEN_Y), shaderProgram);
	enemy->setPosition(glm::vec2(77 * tileMap->getTileSize(), 8 * tileMap->getTileSize()));
	enemy->setTileMap(tileMap);
	enemies.push_back(enemy);

	enemy = new Turret();
	enemy->init(glm::ivec2(SCREEN_X, SCREEN_Y), shaderProgram);
	enemy->setPosition(glm::vec2(95 * tileMap->getTileSize(), 7 * tileMap->getTileSize()));
	enemy->setTileMap(tileMap);
	enemies.push_back(enemy);

	enemy = new Turret();
	enemy->init(glm::ivec2(SCREEN_X, SCREEN_Y), shaderProgram);
	enemy->setPosition(glm::vec2(121 * tileMap->getTileSize(), 8 * tileMap->getTileSize()));
	enemy->setTileMap(tileMap);
	enemies.push_back(enemy);

	enemy = new Turret();
	enemy->init(glm::ivec2(SCREEN_X, SCREEN_Y), shaderProgram);
	enemy->setPosition(glm::vec2(182 * tileMap->getTileSize(), 10 * tileMap->getTileSize()));
	enemy->setTileMap(tileMap);
	enemies.push_back(enemy);

	enemy = new Turret();
	enemy->init(glm::ivec2(SCREEN_X, SCREEN_Y), shaderProgram);
	enemy->setPosition(glm::vec2(192 * tileMap->getTileSize(), 11 * tileMap->getTileSize()));
	enemy->setTileMap(tileMap);
	enemies.push_back(enemy);
}

void EnemyManager::loadSuperTurrets(string level, ShaderProgram &shaderProgram, TileMap *tileMap)
{
	Enemy *enemy;
	enemy = new SuperTurret();
	enemy->init(glm::ivec2(SCREEN_X, SCREEN_Y), shaderProgram);
	enemy->setPosition(glm::vec2(124 * tileMap->getTileSize(), 7.5f * tileMap->getTileSize()));
	enemy->setTileMap(tileMap);
	enemies.push_back(enemy);

	enemy = new SuperTurret();
	enemy->init(glm::ivec2(SCREEN_X, SCREEN_Y), shaderProgram);
	enemy->setPosition(glm::vec2(132 * tileMap->getTileSize(), 1.5f * tileMap->getTileSize()));
	enemy->setTileMap(tileMap);
	enemies.push_back(enemy);

	enemy = new SuperTurret();
	enemy->init(glm::ivec2(SCREEN_X, SCREEN_Y), shaderProgram);
	enemy->setPosition(glm::vec2(168 * tileMap->getTileSize(), 5.5f * tileMap->getTileSize()));
	enemy->setTileMap(tileMap);
	enemies.push_back(enemy);
}

void EnemyManager::loadSoldiers(string level, ShaderProgram &shaderProgram, TileMap *tileMap) {
	Enemy *enemy;
	enemy = new Soldier();
	enemy->init(glm::ivec2(SCREEN_X, SCREEN_Y), shaderProgram);
	enemy->setPosition(glm::vec2(25 * tileMap->getTileSize(), 5 * tileMap->getTileSize()));
	enemy->setTileMap(tileMap);
	enemies.push_back(enemy);

	enemy = new Soldier();
	enemy->init(glm::ivec2(SCREEN_X, SCREEN_Y), shaderProgram);
	enemy->setPosition(glm::vec2(26 * tileMap->getTileSize(), 5 * tileMap->getTileSize()));
	enemy->setTileMap(tileMap);
	enemies.push_back(enemy);

	enemy = new Soldier();
	enemy->init(glm::ivec2(SCREEN_X, SCREEN_Y), shaderProgram);
	enemy->setPosition(glm::vec2(27 * tileMap->getTileSize(), 5 * tileMap->getTileSize()));
	enemy->setTileMap(tileMap);
	enemies.push_back(enemy);

	enemy = new Soldier();
	enemy->init(glm::ivec2(SCREEN_X, SCREEN_Y), shaderProgram);
	enemy->setPosition(glm::vec2(30 * tileMap->getTileSize(), 5 * tileMap->getTileSize()));
	enemy->setTileMap(tileMap);
	enemies.push_back(enemy);

	enemy = new Soldier();
	enemy->init(glm::ivec2(SCREEN_X, SCREEN_Y), shaderProgram);
	enemy->setPosition(glm::vec2(45 * tileMap->getTileSize(), 5 * tileMap->getTileSize()));
	enemy->setTileMap(tileMap);
	enemies.push_back(enemy);

	enemy = new Soldier();
	enemy->init(glm::ivec2(SCREEN_X, SCREEN_Y), shaderProgram);
	enemy->setPosition(glm::vec2(48 * tileMap->getTileSize(), 5 * tileMap->getTileSize()));
	enemy->setTileMap(tileMap);
	enemies.push_back(enemy);

	enemy = new Soldier();
	enemy->init(glm::ivec2(SCREEN_X, SCREEN_Y), shaderProgram);
	enemy->setPosition(glm::vec2(95 * tileMap->getTileSize(), 3 * tileMap->getTileSize()));
	enemy->setTileMap(tileMap);
	enemies.push_back(enemy);

	enemy = new Soldier();
	enemy->init(glm::ivec2(SCREEN_X, SCREEN_Y), shaderProgram);
	enemy->setPosition(glm::vec2(100 * tileMap->getTileSize(), 3 * tileMap->getTileSize()));
	enemy->setTileMap(tileMap);
	enemies.push_back(enemy);

	enemy = new Soldier();
	enemy->init(glm::ivec2(SCREEN_X, SCREEN_Y), shaderProgram);
	enemy->setPosition(glm::vec2(107 * tileMap->getTileSize(), 3 * tileMap->getTileSize()));
	enemy->setTileMap(tileMap);
	enemies.push_back(enemy);

	enemy = new Soldier();
	enemy->init(glm::ivec2(SCREEN_X, SCREEN_Y), shaderProgram);
	enemy->setPosition(glm::vec2(108 * tileMap->getTileSize(), 3 * tileMap->getTileSize()));
	enemy->setTileMap(tileMap);
	enemies.push_back(enemy);
}

void EnemyManager::initEnemies(GLuint nSoldier, GLuint nSniper, GLuint nTurrets, ShaderProgram &shaderProgram, TileMap *tileMap) {
	int nSoldiers = 0;
	int xTileInc = (LEVEL01_TILE_WIDTH - 10) / nSoldier;
	int xTileInterval = xTileInc, yTileInterval = 1;
	
	//loadSnipers("", shaderProgram, tileMap);
	//loadTurrets("", shaderProgram, tileMap);
	//loadSuperTurrets("", shaderProgram, tileMap);
	loadSoldiers("", shaderProgram, tileMap);
}

void EnemyManager::updateEnemies(glm::ivec2 &posPlayer1, glm::ivec2 &posPlayer2, int deltaTime) {
	for (int i = 0; i < enemies.size(); ++i) {
		Enemy *enemy = enemies[i];
		if (enemy != NULL) {
			enemy->update(posPlayer1, posPlayer2, deltaTime);
			glm::vec2 pos = enemy->getPosition();
			if (pos.x - posPlayer1.x <= -360) enemies[i] = NULL;
		}

	}
}

void EnemyManager::detectBulletCollisions() {
	for (int i = 0; i < enemies.size(); ++i) {
		Enemy *enemy = enemies[i];
		if (enemy != NULL) {
			// start by checking collisions against soldiers only
			if (dynamic_cast<Soldier *>(enemy) != nullptr) {
				if (BulletManager::instance().existsBulletColision(enemy->getPosition(), (enemy->getSize()).x, (enemy->getSize()).y))
					enemies[i] = NULL;
			}
		}

	}
}

void EnemyManager::render() {
	for (Enemy *enemy : enemies)
		if(enemy != NULL) enemy->render();
}