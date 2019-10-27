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

bool BulletManager::existsBulletColision(glm::vec2 topLeft, int width, int height, string type)
{
	for (int i = 0; i < bullets.size(); ++i) {
		Bullet * b = bullets[i];
		if (b != NULL) {
			glm::vec2 bPos = b->getPosition();
			if (type == "GREEN_SOLDIER") {
				bPos.x = bPos.x + 32;
				bPos.y = bPos.y + 32;
			}
			else {
				bPos.x = bPos.x + 16;
				bPos.y = bPos.y + 16;
			}
			if ((bPos.x > topLeft.x) && (bPos.x < topLeft.x + width)) {
				if ((bPos.y > topLeft.y) && (bPos.y < topLeft.y + height)) {
					if (b->getFiredBy() == "CHARACTER") {
						if (type != "PLAYER") {
							if (b->getAnimation() != 1) b->changeBulletAnimation(1);
							return true;
						}
					}
					else {
						if (type == "PLAYER") {
							if (b->getAnimation() != 1) b->changeBulletAnimation(1);
							return true;
						}
					}
				}
			}
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
				int posXdiff = pos.x - posPlayer1.x;
				int posYdiff = pos.y - posPlayer1.y;
				if (posXdiff <= -550 || posXdiff > 550 ||
					posYdiff <= -550 || posYdiff > 550 | bullet->getAnimation() == 1) bullets[i] = NULL;
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
					if (bullet->getAnimation() == 1) bullets[i] = NULL;

					// it was 170 before. changed to 195 for testing pruposes
					if (pos.x >= 186 && pos.x <= 346 && pos.y < 190) bullets[i] = NULL;
					
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

vector<glm::ivec2> BulletManager::getPositionBullets()
{
	vector<glm::ivec2> res;
	for (Bullet *b: bullets) {
		glm::vec2 bPos = b->getPosition();
		bPos.x = bPos.x + 16;
		bPos.y = bPos.y + 16;
		res.push_back(bPos);
	}
	return res;
}