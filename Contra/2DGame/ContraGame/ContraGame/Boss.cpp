#include "Boss.h"
#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"
#include "Time.h"
#include "BulletManager.h"



Boss::Boss()
{
}


Boss::~Boss()
{
}

void Boss::init(const glm::ivec2 & tileMapPos, ShaderProgram & shaderProgram)
{
	F = false;
	armshoot = 1;
	lastBullet = 0;
	fase2 = false;

	arm1 = new BossArm();
	arm2 = new BossArm();
	arm3 = new BossArm();
	arm4 = new BossArm();
	head = new BossArm();

	arm1->init(tileMapPos, shaderProgram);
	arm1->setPosition(glm::vec2(float(75), float(125)));
	arm2->init(tileMapPos, shaderProgram);
	arm2->setPosition(glm::vec2(float(5), float(190)));
	arm3->init(tileMapPos, shaderProgram);
	arm3->setPosition(glm::vec2(float(450), float(125)));
	arm4->init(tileMapPos, shaderProgram);
	arm4->setPosition(glm::vec2(float(515), float(190)));
	head->init(tileMapPos, shaderProgram);
	head->setPosition(glm::vec2(float(255), float(80)));

	Life = arm1->getLife() + arm2->getLife() + arm3->getLife() + arm4->getLife() + head->getLife();

	this->tileMapDispl = tileMapPos;
	this->shaderProgram = shaderProgram;
}

void Boss::createBullet(glm::vec2 pos, glm::vec2 dir, const glm::ivec2 & tileMapPos, ShaderProgram & shaderProgram)
{
	BossBullet* b = new BossBullet();
	b->init(pos, dir, tileMapPos, shaderProgram);
	bullets.push_back(b);
}

void Boss::update(int deltaTime, const glm::ivec2 & tileMapPos, ShaderProgram & shaderProgram)
{
	if (Life <= 20) fase2 = true;
	if (!fase2) {
		if (Time::instance().NowToMili() - lastBullet > 1000) {
			if (armshoot == 1) {
				if (arm1->getLife() > 0) createBullet(glm::vec2(float(75), float(125)), glm::vec2(0, 1), tileMapDispl, shaderProgram);
				lastBullet = Time::instance().NowToMili();
				armshoot = 2;
			}
			else if (armshoot == 2) {
				if (arm2->getLife() > 0) createBullet(glm::vec2(float(5), float(190)), glm::vec2(0, 1), tileMapDispl, shaderProgram);
				lastBullet = Time::instance().NowToMili();
				armshoot = 3;
			}
			else if (armshoot == 3) {
				if (arm3->getLife() > 0) createBullet(glm::vec2(float(450), float(125)), glm::vec2(0, 1), tileMapDispl, shaderProgram);
				lastBullet = Time::instance().NowToMili();
				armshoot = 4;
			}
			else if (armshoot == 4) {
				if (arm4->getLife() > 0) createBullet(glm::vec2(float(515), float(190)), glm::vec2(0, 1), tileMapDispl, shaderProgram);
				lastBullet = Time::instance().NowToMili();
				armshoot = 1;
			}
		}
		if (arm1->getLife() > 0)
			if (BulletManager::instance().existsBulletColision(glm::vec2(float(75), float(125)), 64, 64, "BOSS")) arm1->RestLife(2);
		if (arm2->getLife() > 0)
			if (BulletManager::instance().existsBulletColision(glm::vec2(float(5), float(190)), 64, 64, "BOSS")) arm2->RestLife(2);
		if (arm3->getLife() > 0)
			if (BulletManager::instance().existsBulletColision(glm::vec2(float(450), float(125)), 64, 64, "BOSS")) arm3->RestLife(2);
		if (arm4->getLife() > 0)
			if (BulletManager::instance().existsBulletColision(glm::vec2(float(515), float(190)), 64, 64, "BOSS")) arm4->RestLife(2);

		arm1->update(deltaTime);
		arm2->update(deltaTime);
		arm3->update(deltaTime);
		arm4->update(deltaTime);

		Life = arm1->getLife() + arm2->getLife() + arm3->getLife() + arm4->getLife() + 20;

		for (int i = 0; i < bullets.size(); ++i) {
			BossBullet * bullet = bullets[i];
			if (bullet != NULL) {
				bullet->update(deltaTime);
			}
			if (bullet->getPosition().y > SCREEN_HEIGHT) bullet = NULL;
		}
	}
	else {
		if (head->getLife() > 0) {
			if (Time::instance().NowToMili() - lastBullet > 1500) {
				createBullet(glm::vec2(float(255), float(80)), glm::vec2(0, 1), tileMapDispl, shaderProgram);
				createBullet(glm::vec2(float(255), float(80)), glm::vec2(-0.5, 0.5), tileMapDispl, shaderProgram);
				createBullet(glm::vec2(float(255), float(80)), glm::vec2(0.5, 0.5), tileMapDispl, shaderProgram);
				lastBullet = Time::instance().NowToMili();
			}
			if (BulletManager::instance().existsBulletColision(glm::vec2(float(255), float(80)), 64, 64, "BOSS")) head->RestLife(2);
			Life = arm1->getLife() + arm2->getLife() + arm3->getLife() + arm4->getLife() + head->getLife();
		}
		for (int i = 0; i < bullets.size(); ++i) {
			BossBullet * bullet = bullets[i];
			if (bullet != NULL) {
				bullet->update(deltaTime);
			}
			//if (bullet != NULL && bullet->getPosition().y > SCREEN_HEIGHT) bullet = NULL;
		}
	}
}

void Boss::render()
{
	arm1->render();
	arm2->render();
	arm3->render();
	arm4->render();
	for (BossBullet * bullet : bullets) {
		if (bullet != NULL) bullet->render();
	}
	if (fase2) head->render();
}


bool Boss::existsBulletColision(glm::vec2 topLeft, int width, int height)
{
	for (int i = 0; i < bullets.size(); ++i) {
		BossBullet * b = bullets[i];
		if (b != NULL) {
			glm::vec2 bPos = b->getPosition();
			if ((bPos.x + 60 > topLeft.x) && (bPos.x + 60 < topLeft.x + width) || (bPos.x > topLeft.x) && (bPos.x < topLeft.x + width)) {
				if ((bPos.y + 32 > topLeft.y) && (bPos.y + 32 < topLeft.y + height)) {
					return true;
				}
			}
		}
	}
	return false;
}

int Boss::getLifes()
{
	return Life;
}

void Boss::deleteBullets()
{
	bullets = vector<BossBullet *>();
}