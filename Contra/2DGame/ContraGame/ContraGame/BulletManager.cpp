#include "BulletManager.h"

#define SCREEN_X 32
#define SCREEN_Y 16

void BulletManager::initBulletManager(ShaderProgram &shaderProgram, TileMap *tileMap)
{
	this->shaderProgram = shaderProgram;
	this->tileMap = tileMap;
}

void BulletManager::fire(vector<glm::vec2> dir, vector<glm::vec2> pos, int speed, string firedBy)
{
for (int i = 0; i < dir.size() && i < pos.size(); ++i)
	{
		Bullet* bullet = new Bullet();
		bullet->init(glm::ivec2(SCREEN_X, SCREEN_Y), pos[i], dir[i], speed, shaderProgram);
		bullet->setTileMap(tileMap);
		bullet->setFiredBy(firedBy);
		bullets.push_back(bullet);
	}
}

bool BulletManager::existsBulletColision(glm::vec2 bottomLeft, int width, int height, string type)
{
	for (int i = 0; i < bullets.size(); ++i) {
		Bullet * b = bullets[i];
		if (b != NULL) {
			glm::vec2 bPos = b->getPosition();
			//offset
			if (type == "SOLDIER") {
				bPos.x = bPos.x - 10;
				bPos.y = bPos.y - 16;
			}
			else if (type == "SNIPER") {
				bPos.x = bPos.x - 10;
				bPos.y = bPos.y - 120;
			}
			else if (type == "TURRET") {
				bPos.x = bPos.x + 16;
				bPos.y = bPos.y - height - 16;
			}
			else if (type == "SUPER_TURRET") {
				bPos.x = bPos.x + 16;
				bPos.y = bPos.y - height - 32;
				bottomLeft.x += 16.f;
				bottomLeft.y -= 16.f;
			}
			// bPos.x < bottomRight.x && bPos.x > bottomLeft.x && bPos.y < bottomRight.y && bPos.y > bottomLeft.y - height
			if (bPos.x > bottomLeft.x && bPos.x < bottomLeft.x + width) {
				if (bPos.y< bottomLeft.y && bPos.y > bottomLeft.y - height) {
					if (b->getFiredBy() == "CHARACTER") {
						if (b->getAnimation() != 1) b->changeBulletAnimation(1);
						else if (b->getAnimation() == 1)
							bullets[i] = NULL;
						return true;
					}
					else return false;
				}
			}
			return false;
		}
	}
	return false;
}


void BulletManager::update(glm::ivec2 &posPlayer1, glm::ivec2 &posPlayer2, int deltaTime, string level)
{
	if (level == "level01") {
		for (int i = 0; i < bullets.size(); ++i) {
			Bullet * bullet = bullets[i];
			if (bullet != NULL) {
				bullet->update(deltaTime);
				glm::vec2 pos = bullet->getPosition();
				if (pos.x - posPlayer1.x <= -550 || pos.x - posPlayer1.x > 550 ||
					pos.y - posPlayer1.y <= -550 || pos.y - posPlayer1.y > 550) bullets[i] = NULL;
			}
		}
	}
	else {
		for (int i = 0; i < bullets.size(); ++i) {
			Bullet * bullet = bullets[i];
			if (bullet != NULL) {
				bullet->update(deltaTime);
				glm::vec2 pos = bullet->getPosition();
				if (bullet->getFiredBy() == "CHARACTER") {
					if (pos.x >= 186 && pos.x <= 346 && pos.y < 170) bullets[i] = NULL;
					
					else if (pos.x >= 150 && pos.x <= 185 && pos.y < 185) bullets[i] = NULL;
					else if (pos.x >= 139 && pos.x <= 184 && pos.y < 200) bullets[i] = NULL;
					else if (pos.x >= 64 && pos.x <= 139 && pos.y < 215) bullets[i] = NULL;

					else if (pos.x >= 346 && pos.x <= 384 && pos.y < 185) bullets[i] = NULL;
					else if (pos.x >= 385 && pos.x <= 430 && pos.y < 200) bullets[i] = NULL;
					else if (pos.x >= 430 && pos.x <= 476 && pos.y < 215) bullets[i] = NULL;
				}
				if (bullet->getFiredBy() == "ENEMY" && pos.y >= 350) bullets[i] = NULL;
			}
		}
	}
}

void BulletManager::render()
{
	for (Bullet * bullet : bullets) {
		if (bullet != NULL) bullet->render();
	}
}