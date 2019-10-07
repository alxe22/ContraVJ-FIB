#include "EnemyManager.h"
#include "Soldier.h"

void EnemyManager::initEnemies(GLuint nSoldier, GLuint nSniper, GLuint nTurrets) {
}

void EnemyManager::updateEnemies(glm::ivec2 &posPlayer1, glm::ivec2 &posPlayer2, int deltaTime) {
	for (Enemy *enemy : enemies) enemy->update(glm::ivec2(-1, -1), glm::ivec2(-1, -1), deltaTime);
}

