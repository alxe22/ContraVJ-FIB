#include "BulletManager.h"

#define SCREEN_X 32
#define SCREEN_Y 16

void BulletManager::initBulletManager(ShaderProgram &shaderProgram, TileMap *tileMap)
{
	this->shaderProgram = shaderProgram;
	this->tileMap = tileMap;
}

void BulletManager::fire(vector<glm::ivec2> dir, vector<glm::ivec2> pos)
{
	for (int i = 0; i < dir.size() && i < pos.size(); ++i)
	{
		Bullet* bullet = new Bullet();
		bullet->init(glm::ivec2(SCREEN_X, SCREEN_Y), pos[i], dir[i], shaderProgram);
		bullet->setTileMap(tileMap);
		bullets.push_back(bullet);
	}
}

void BulletManager::update(glm::ivec2 &posPlayer1, glm::ivec2 &posPlayer2, int deltaTime)
{
	for (int i = 0; i < bullets.size(); ++i) {
		Bullet * bullet = bullets[i];
		if (bullet != NULL) {
			bullet->update(deltaTime);
			glm::vec2 pos = bullet->getPosition();
			if (pos.x - posPlayer1.x <= -360 || pos.x - posPlayer1.x > 360) bullets[i] = NULL;
		}
	}
}

void BulletManager::render()
{
	for (Bullet * bullet : bullets) {
		if (bullet != NULL) bullet->render();
	}
}