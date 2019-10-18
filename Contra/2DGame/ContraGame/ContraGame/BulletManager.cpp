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
					bullets[i] = NULL;
					return true;
				}
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
			if (pos.x - posPlayer1.x <= -550 || pos.x - posPlayer1.x > 550 || 
				pos.y - posPlayer1.y <= -550 || pos.y - posPlayer1.y > 550) bullets[i] = NULL;
		}
	}
}

void BulletManager::render()
{
	for (Bullet * bullet : bullets) {
		if (bullet != NULL) bullet->render();
	}
}