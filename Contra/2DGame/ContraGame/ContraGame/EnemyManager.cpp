#include "EnemyManager.h"
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

void EnemyManager::initEnemies(GLuint nSoldier, GLuint nSniper, GLuint nTurrets, ShaderProgram &shaderProgram, TileMap *tileMap) {
	int nSoldiers = 0;
	int xTileInc = (LEVEL01_TILE_WIDTH - 10) / nSoldier;
	int xTileInterval = xTileInc, yTileInterval = 1;
	
	//snipers
	loadSnipers("", shaderProgram, tileMap);
	loadTurrets("", shaderProgram, tileMap);
	loadSuperTurrets("", shaderProgram, tileMap);
	
	Enemy *enemy;
	enemy = new Soldier();
	enemy->init(glm::ivec2(SCREEN_X, SCREEN_Y), shaderProgram);
	enemy->setPosition(glm::vec2(7 * tileMap->getTileSize(), 5 * tileMap->getTileSize()));
	enemy->setTileMap(tileMap);
	enemies.push_back(enemy);
	

	/*while (nSoldiers < nSoldier) {
		Enemy *enemy;
		enemy = new Soldier();
		enemy->init(glm::ivec2(SCREEN_X, SCREEN_Y), shaderProgram);
		enemy->setPosition(glm::vec2(xTileInterval * tileMap->getTileSize(), yTileInterval * tileMap->getTileSize()));
		//enemy->setPosition(glm::vec2(xTileInterval * tileMap->getTileSize(), yTileInterval * tileMap->getTileSize()));
		enemy->setTileMap(tileMap);
		xTileInterval += xTileInc;
		++nSoldiers;
		enemies.push_back(enemy);
	}*/
	/*Enemy *enemy;
	enemy = new Soldier();
	enemy->init(glm::ivec2(SCREEN_X, SCREEN_Y), shaderProgram);
	enemy->setPosition(glm::vec2(4 * tileMap->getTileSize(), 0 * tileMap->getTileSize()));
	enemy->setTileMap(tileMap);
	enemies.push_back(enemy);*/
	/*Enemy *enemy;
	enemy = new Sniper();
	enemy->init(glm::ivec2(SCREEN_X, SCREEN_Y), shaderProgram);
	enemy->setPosition(glm::vec2(4 * tileMap->getTileSize(), 0 * tileMap->getTileSize()));
	enemy->setTileMap(tileMap);
	enemies.push_back(enemy);*/
	/*Enemy *enemy;
	enemy = new Turret();
	enemy->init(glm::ivec2(SCREEN_X, SCREEN_Y), shaderProgram);
	enemy->setPosition(glm::vec2(4 * tileMap->getTileSize(), 0 * tileMap->getTileSize()));
	enemy->setTileMap(tileMap);
	enemies.push_back(enemy);*/
}

void EnemyManager::updateEnemies(glm::ivec2 &posPlayer1, glm::ivec2 &posPlayer2, int deltaTime) {
	for (Enemy *enemy : enemies) enemy->update(posPlayer1, posPlayer2, deltaTime);
}

void EnemyManager::render() {
	for (Enemy *enemy : enemies) enemy->render();
}