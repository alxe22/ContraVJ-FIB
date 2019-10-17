#include "BulletManager.h"

#define SCREEN_X 32
#define SCREEN_Y 16

void BulletManager::initBulletManager(ShaderProgram &shaderProgram, TileMap *tileMap)
{
	this->shaderProgram = shaderProgram;
	this->tileMap = tileMap;
}

void BulletManager::fire(vector<glm::vec2> dir, vector<glm::vec2> pos, int speed)
{
	for (int i = 0; i < dir.size() && i < pos.size(); ++i)
	{
		Bullet* bullet = new Bullet();
		bullet->init(glm::ivec2(SCREEN_X, SCREEN_Y), pos[i], dir[i], speed, shaderProgram);
		bullet->setTileMap(tileMap);
		bullets.push_back(bullet);
	}
}

bool BulletManager::existsBulletColision(glm::vec2 topLeft, int width, int height)
{
	for (int i = 0; i < bullets.size(); ++i) {
		Bullet * b = bullets[i];
		if (b != NULL) {
			glm::vec2 bPos = b->getPosition();
			// bottom right point = (topLeft.x + width, topLeft.y + height)
			glm::vec2 bottomRight(topLeft.x + width, topLeft.y + height);
			// bottom left point = (topLeft.x, topLeft.y + hegiht)
			glm::vec2 bottomLeft(topLeft.x, topLeft.y + height);
			if (bPos.x < bottomRight.x && bPos.x > topLeft.x && bPos.y < bottomRight.y && bPos.y > topLeft.y) {
				bullets[i] = NULL;
				return true;
			}
			return false;
		}
	}
	return false;
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