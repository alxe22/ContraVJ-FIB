#include "Boss.h"
#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"
#include "Time.h"



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

	arm1 = new BossArm();
	arm2 = new BossArm();
	arm3 = new BossArm();
	arm4 = new BossArm();

	arm1->init(tileMapPos, shaderProgram);
	arm1->setPosition(glm::vec2(float(105), float(145)));
	arm2->init(tileMapPos, shaderProgram);
	arm2->setPosition(glm::vec2(float(60), float(200)));
	arm3->init(tileMapPos, shaderProgram);
	arm3->setPosition(glm::vec2(float(470), float(145)));
	arm4->init(tileMapPos, shaderProgram);
	arm4->setPosition(glm::vec2(float(515), float(200)));

	Life = arm1->getLife() + arm2->getLife() + arm3->getLife() + arm4->getLife() + 20;

	this->tileMapDispl = tileMapPos;
	this->shaderProgram = shaderProgram;
}

void Boss::createBullet(glm::vec2 pos,const glm::ivec2 & tileMapPos, ShaderProgram & shaderProgram)
{
	BossBullet* b = new BossBullet();
	b->init(pos, glm::vec2(0,1), tileMapPos, shaderProgram);
	bullets.push_back(b);
}

void Boss::update(int deltaTime, const glm::ivec2 & tileMapPos, ShaderProgram & shaderProgram)
{
	if (Time::instance().NowToMili() - lastBullet > 1500) {
		if (armshoot == 1) {
			createBullet(glm::vec2(float(105), float(145)), tileMapDispl, shaderProgram);
			lastBullet = Time::instance().NowToMili();
			armshoot = 2;
		}
		else if (armshoot == 2) {
			createBullet(glm::vec2(float(60), float(200)), tileMapDispl, shaderProgram);
			lastBullet = Time::instance().NowToMili();
			armshoot = 3;
		}
		else if (armshoot == 3) {
			createBullet(glm::vec2(float(470), float(145)), tileMapDispl, shaderProgram);
			lastBullet = Time::instance().NowToMili();
			armshoot = 4;
		}
		else if (armshoot == 4) {
			createBullet(glm::vec2(float(515), float(200)), tileMapDispl, shaderProgram);
			lastBullet = Time::instance().NowToMili();
			armshoot = 1;
		}
	}

	arm1->update(deltaTime);
	arm2->update(deltaTime);
	arm3->update(deltaTime);
	arm4->update(deltaTime);

	for (int i = 0; i < bullets.size(); ++i) {
		BossBullet * bullet = bullets[i];
		if (bullet != NULL) {
			bullet->update(deltaTime);
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
}
