#include "EnemyManager.h"
#include "BulletManager.h"
#include "Soldier.h"
#include "Sniper.h"
#include "Turret.h"
#include "SuperTurret.h"
#include "GreenSoldier.h"
#include "Time.h"

#define SCREEN_X 32
#define SCREEN_Y 16

#define LEVEL01_TILE_WIDTH 77
#define LEVEL01_TILE_HEIGHT 8

#define GREEN_SOLDIER_CREATION_FRAME_INTERVAL 1000

#define GREEN_SOLDIERS_KILLED_TO_ADVANCE 5

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

void EnemyManager::loadSoldiers(string level, ShaderProgram &shaderProgram, TileMap *tileMap) 
{
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

void EnemyManager::loadGreenSoldiers(string level, ShaderProgram &shaderProgram)
{
	Enemy *enemy;
	enemy = new GreenSoldier();
	enemy->init(glm::ivec2(SCREEN_X, SCREEN_Y), shaderProgram);
	if ((rand() % 100) % 2 == 0) {
		enemy->setPosition(glm::vec2(384, 210));
		enemy->setAnimation(0);
	}
	else {
		enemy->setPosition(glm::vec2(230, 210));
		enemy->setAnimation(1);
	}
	enemies.push_back(enemy);
}

bool EnemyManager::canAdvance()
{
	return greenSoldiersKilled > GREEN_SOLDIERS_KILLED_TO_ADVANCE;
}

void EnemyManager::setCanAdvance(int i)
{
	greenSoldiersKilled = i;
}

void EnemyManager::initEnemies(GLuint nSoldier, GLuint nSniper, GLuint nTurrets, ShaderProgram &shaderProgram, TileMap *tileMap, string level) {
	if (level == "level01") {
		enemies = vector<Enemy *>();
		int nSoldiers = 0;
		int xTileInc = (LEVEL01_TILE_WIDTH - 10) / nSoldier;
		int xTileInterval = xTileInc, yTileInterval = 1;

		/*loadSnipers("", shaderProgram, tileMap);
		loadTurrets("", shaderProgram, tileMap);
		loadSuperTurrets("", shaderProgram, tileMap);*/
		loadSoldiers("", shaderProgram, tileMap);
	}
	this->shaderProgram = shaderProgram;
}

void EnemyManager::updateEnemies(glm::ivec2 &posPlayer1, glm::ivec2 &posPlayer2, int deltaTime, string level) {
	if (level == "level01") {
		for (int i = 0; i < enemies.size(); ++i) {
			Enemy *enemy = enemies[i];
			if (enemy != NULL) {
				enemy->update(posPlayer1, posPlayer2, deltaTime);
				glm::vec2 pos = enemy->getPosition();
				if (pos.x - posPlayer1.x <= -360) enemies[i] = NULL;
			}
		}
	}
	else {
		long long diff = Time::instance().NowToMili() - miliLastGreenSoldierCreated;
		if (diff > GREEN_SOLDIER_CREATION_FRAME_INTERVAL) {
			miliLastGreenSoldierCreated = Time::instance().NowToMili();
			loadGreenSoldiers("", shaderProgram);
		}
		for (int i = 0; i < enemies.size(); ++i) {
			Enemy *enemy = enemies[i];
			if (enemy != NULL) {
				// if enemy pos.x < 230 and enemy animation moveleft or enemy pos.x > 380 and enemy animation is move right
				if (((enemy->getPosition()).x < 230 && enemy->getAnimation() == 0) ||
					((enemy->getPosition()).x > 370 && enemy->getAnimation() == 1)) enemies[i] = NULL;
				else enemy->update(posPlayer1, posPlayer2, deltaTime);
			}
		}
	}
}

void EnemyManager::detectBulletCollisions(string level) {
	for (int i = 0; i < enemies.size(); ++i) {
		Enemy *enemy = enemies[i];
		if (enemy != NULL) {
			if (BulletManager::instance().existsBulletColision(enemy->getTopLeftPos(), (enemy->getSize()).x, (enemy->getSize()).y, enemy->type())) {
				enemies[i] = NULL;
				if (level == "level02") ++greenSoldiersKilled;
			}
		}

	}
}

void EnemyManager::render() {
	for (Enemy *enemy : enemies)
		if(enemy != NULL) enemy->render();
}

void EnemyManager::deleteAll() {
	enemies = vector<Enemy *>();
}