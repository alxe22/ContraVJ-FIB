#include "EnemyManager.h"
#include "Soldier.h"

#define SCREEN_X 32
#define SCREEN_Y 16

#define LEVEL01_TILE_WIDTH 208
#define LEVEL01_TILE_HEIGHT 15

void EnemyManager::initEnemies(GLuint nSoldier, GLuint nSniper, GLuint nTurrets, ShaderProgram &shaderProgram, TileMap *tileMap) {
	int nSoldiers = 0;
	int xTileInc = (LEVEL01_TILE_WIDTH - 10) / nSoldier;
	int xTileInterval = xTileInc, yTileInterval = 1;

	while (nSoldiers < nSoldier) {
		Enemy *enemy;
		enemy = new Soldier();
		enemy->init(glm::ivec2(SCREEN_X, SCREEN_Y), shaderProgram);
		enemy->setPosition(glm::vec2(xTileInterval * tileMap->getTileSize(), yTileInterval * tileMap->getTileSize()));
		//enemy->setPosition(glm::vec2(xTileInterval * tileMap->getTileSize(), yTileInterval * tileMap->getTileSize()));
		enemy->setTileMap(tileMap);
		xTileInterval += xTileInc;
		++nSoldiers;
		enemies.push_back(enemy);
	}
	/*Enemy *enemy;
	enemy = new Soldier();
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