#include "Boss.h"
#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"



Boss::Boss()
{
}


Boss::~Boss()
{
}

void Boss::init(const glm::ivec2 & tileMapPos, ShaderProgram & shaderProgram)
{
	F = false;

	arm1 = new BossArm();
	arm2 = new BossArm();
	arm3 = new BossArm();
	arm4 = new BossArm();

	arm1->init(tileMapPos, shaderProgram);
	arm1->setPosition(glm::vec2(float(95), float(145)));
	arm2->init(tileMapPos, shaderProgram);
	arm2->setPosition(glm::vec2(float(50), float(200)));
	arm3->init(tileMapPos, shaderProgram);
	arm3->setPosition(glm::vec2(float(460), float(145)));
	arm4->init(tileMapPos, shaderProgram);
	arm4->setPosition(glm::vec2(float(505), float(200)));

	Life = arm1->getLife() + arm2->getLife() + arm3->getLife() + arm4->getLife() + 20;
}

void Boss::update(int deltaTime, const glm::ivec2 & tileMapPos, ShaderProgram & shaderProgram)
{
	arm1->update(deltaTime);
	arm2->update(deltaTime);
	arm3->update(deltaTime);
	arm4->update(deltaTime);

	//arm1->createBullet(glm::vec2(277 - 95, 400 - 145), tileMapPos, shaderProgram);
}

void Boss::render()
{
	arm1->render();
	arm2->render();
	arm3->render();
	arm4->render();
}
