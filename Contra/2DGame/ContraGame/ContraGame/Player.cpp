#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Player.h"
#include "Game.h"
#include "BulletManager.h"
#include "Time.h"


#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 96
#define FALL_STEP 4


enum PlayerAnims
{
	STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT, MOVESH_LEFT, MOVESH_RIGHT, JUMP_LEFT, JUMP_RIGHT, 
	LAY_LEFT, LAY_RIGHT, UP_LEFT, UP_RIGHT, DIE_LEFT, DIE_RIGHT, MOVEU45_LEFT, MOVEU45_RIGHT, MOVED45_LEFT, MOVED45_RIGHT,
	WAT_RUN_LEFT,WAT_RUN_RIGHT,WAT_UP_LEFT,WAT_UP_RIGHT,WAT_STAND_RIGHT,WAT_STAND_LEFT,WAT_RUNUP_RIGHT,WAT_RUNUP_LEFT,SPLASH
};

enum PlayerStates
{
	standing, running, laying, up, running_up, running_down, jumping, water_stand, water_up, water_run, water_runup, rip
};


void Player::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	PlayerState = standing;
	PlayerDir = "R";
	RestLifes = 3;
	F = false;
	shooting = false;
	swimming = false;
	spritesheet.loadFromFile("images/soldado.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(96, 96), glm::vec2(1/11.f, 1/11.f), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(27);
	
		sprite->setAnimationSpeed(STAND_LEFT, 8);
		sprite->addKeyframe(STAND_LEFT, glm::vec2(1/11.f,0.f));
		
		sprite->setAnimationSpeed(STAND_RIGHT, 8);
		sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.f, 0.f));
		
		sprite->setAnimationSpeed(MOVE_RIGHT, 8);
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(6/11.f, 3/11.f));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(7/11.f, 3/11.f));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(8/11.f, 3/11.f));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(9/11.f, 3/11.f));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(10/11.f, 2/11.f));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(10/11.f, 3/11.f));
		
		sprite->setAnimationSpeed(MOVE_LEFT, 8);
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(6/11.f, 4/11.f));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(6/11.f, 5/11.f));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(7/11.f, 4/11.f));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(8/11.f, 4/11.f));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(9/11.f, 4/11.f));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(10/11.f, 4/11.f));

		sprite->setAnimationSpeed(MOVESH_LEFT, 8);
		sprite->addKeyframe(MOVESH_LEFT, glm::vec2(5 / 11.f, 3 / 11.f));
		sprite->addKeyframe(MOVESH_LEFT, glm::vec2(4 / 11.f, 3 / 11.f));
		sprite->addKeyframe(MOVESH_LEFT, glm::vec2(3 / 11.f, 3 / 11.f));

		sprite->setAnimationSpeed(MOVESH_RIGHT, 8);
		sprite->addKeyframe(MOVESH_RIGHT, glm::vec2(0 / 11.f, 3 / 11.f));
		sprite->addKeyframe(MOVESH_RIGHT, glm::vec2(1 / 11.f, 3 / 11.f));
		sprite->addKeyframe(MOVESH_RIGHT, glm::vec2(2 / 11.f, 3 / 11.f));

		sprite->setAnimationSpeed(MOVEU45_RIGHT, 8);
		sprite->addKeyframe(MOVEU45_RIGHT, glm::vec2(0 / 11.f, 4 / 11.f));
		sprite->addKeyframe(MOVEU45_RIGHT, glm::vec2(1 / 11.f, 4 / 11.f));
		sprite->addKeyframe(MOVEU45_RIGHT, glm::vec2(2 / 11.f, 4 / 11.f));

		sprite->setAnimationSpeed(MOVED45_RIGHT, 8);
		sprite->addKeyframe(MOVED45_RIGHT, glm::vec2(0 / 11.f, 5 / 11.f));
		sprite->addKeyframe(MOVED45_RIGHT, glm::vec2(1 / 11.f, 5 / 11.f));
		sprite->addKeyframe(MOVED45_RIGHT, glm::vec2(2 / 11.f, 5 / 11.f));

		sprite->setAnimationSpeed(MOVEU45_LEFT, 8);
		sprite->addKeyframe(MOVEU45_LEFT, glm::vec2(3 / 11.f, 4 / 11.f));
		sprite->addKeyframe(MOVEU45_LEFT, glm::vec2(4 / 11.f, 4 / 11.f));
		sprite->addKeyframe(MOVEU45_LEFT, glm::vec2(5 / 11.f, 4 / 11.f));

		sprite->setAnimationSpeed(MOVED45_LEFT, 8);
		sprite->addKeyframe(MOVED45_LEFT, glm::vec2(3 / 11.f, 5 / 11.f));
		sprite->addKeyframe(MOVED45_LEFT, glm::vec2(4 / 11.f, 5 / 11.f));
		sprite->addKeyframe(MOVED45_LEFT, glm::vec2(5 / 11.f, 5 / 11.f));

		sprite->setAnimationSpeed(UP_LEFT, 8);
		sprite->addKeyframe(UP_LEFT, glm::vec2(3/11.f, 0.f));

		sprite->setAnimationSpeed(UP_RIGHT, 8);
		sprite->addKeyframe(UP_RIGHT, glm::vec2(2/11.f, 0.f));
		
		sprite->setAnimationSpeed(LAY_LEFT, 8);
		sprite->addKeyframe(LAY_LEFT, glm::vec2(5 / 11.f, 0.f));

		sprite->setAnimationSpeed(LAY_RIGHT, 8);
		sprite->addKeyframe(LAY_RIGHT, glm::vec2(4 / 11.f, 0.f));


		sprite->setAnimationSpeed(JUMP_RIGHT, 8);
		sprite->addKeyframe(JUMP_RIGHT, glm::vec2(0/16.f, 1/11.f));
		sprite->addKeyframe(JUMP_RIGHT, glm::vec2(1 / 11.f, 1/11.f));
		sprite->addKeyframe(JUMP_RIGHT, glm::vec2(2 / 11.f, 1/11.f));
		sprite->addKeyframe(JUMP_RIGHT, glm::vec2(3 / 11.f, 1/11.f));

		sprite->setAnimationSpeed(JUMP_LEFT, 8);
		sprite->addKeyframe(JUMP_LEFT, glm::vec2(7 / 11.f, 1 / 11.f));
		sprite->addKeyframe(JUMP_LEFT, glm::vec2(6 / 11.f, 1 / 11.f));
		sprite->addKeyframe(JUMP_LEFT, glm::vec2(5 / 11.f, 1 / 11.f));
		sprite->addKeyframe(JUMP_LEFT, glm::vec2(4 / 11.f, 1 / 11.f));

		sprite->setAnimationSpeed(DIE_RIGHT, 8);
		sprite->addKeyframe(DIE_RIGHT, glm::vec2(3 / 11.f, 2 / 11.f));
		sprite->addKeyframe(DIE_RIGHT, glm::vec2(2 / 11.f, 2 / 11.f));
		sprite->addKeyframe(DIE_RIGHT, glm::vec2(1 / 11.f, 2 / 11.f));
		sprite->addKeyframe(DIE_RIGHT, glm::vec2(0 / 11.f, 2 / 11.f));
		sprite->addKeyframe(DIE_RIGHT, glm::vec2(4 / 11.f, 2 / 11.f));

		sprite->setAnimationSpeed(DIE_LEFT, 8);
		sprite->addKeyframe(DIE_LEFT, glm::vec2(6 / 11.f, 2 / 11.f));
		sprite->addKeyframe(DIE_LEFT, glm::vec2(7 / 11.f, 2 / 11.f));
		sprite->addKeyframe(DIE_LEFT, glm::vec2(8 / 11.f, 2 / 11.f));
		sprite->addKeyframe(DIE_LEFT, glm::vec2(9 / 11.f, 2 / 11.f));
		sprite->addKeyframe(DIE_LEFT, glm::vec2(5 / 11.f, 2 / 11.f));

		sprite->setAnimationSpeed(WAT_STAND_LEFT, 8);
		sprite->addKeyframe(WAT_STAND_LEFT, glm::vec2(9 / 11.f, 6/11.f));

		sprite->setAnimationSpeed(WAT_STAND_RIGHT, 8);
		sprite->addKeyframe(WAT_STAND_RIGHT, glm::vec2(2 / 11.f, 6/11.f));
		
		sprite->setAnimationSpeed(WAT_RUN_LEFT, 8);
		sprite->addKeyframe(WAT_RUN_LEFT, glm::vec2(10 / 11.f, 6 / 11.f));
		
		sprite->setAnimationSpeed(WAT_RUN_RIGHT, 8);
		sprite->addKeyframe(WAT_RUN_RIGHT, glm::vec2(1 / 11.f, 6 / 11.f));

		sprite->setAnimationSpeed(WAT_RUNUP_LEFT, 8);
		sprite->addKeyframe(WAT_RUNUP_LEFT, glm::vec2(7 / 11.f, 6 / 11.f));

		sprite->setAnimationSpeed(WAT_RUNUP_RIGHT, 8);
		sprite->addKeyframe(WAT_RUNUP_RIGHT, glm::vec2(4 / 11.f, 6 / 11.f));
		
		sprite->setAnimationSpeed(WAT_UP_LEFT, 8);
		sprite->addKeyframe(WAT_UP_LEFT, glm::vec2(6 / 11.f, 6 / 11.f));

		sprite->setAnimationSpeed(WAT_UP_RIGHT, 8);
		sprite->addKeyframe(WAT_UP_RIGHT, glm::vec2(5 / 11.f, 6 / 11.f));

		sprite->setAnimationSpeed(SPLASH, 8);
		sprite->addKeyframe(SPLASH, glm::vec2(0 / 11.f, 6 / 11.f));
		

	sprite->changeAnimation(1);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	
}

void Player::update(int deltaTime)
{
	sprite->update(deltaTime);
	
	if (Game::instance().getKey('z')) {
		if (!shooting) {
			if (PlayerState != running) shooting = true;
			int speed = 4;
			vector<glm::vec2> dir;
			vector<glm::vec2> pos;
			glm::ivec2 d = glm::ivec2(1, 0);
			if (PlayerDir == "L") d = glm::ivec2(-1, 0);
			switch (PlayerState)
			{
			case standing:
				dir.push_back(d);
				dir.push_back(glm::vec2(-0.5, 0));
				if (PlayerDir == "R") pos.push_back(glm::ivec2(posPlayer.x + 64, posPlayer.y + 28));
				else pos.push_back(glm::ivec2(posPlayer.x + 6, posPlayer.y + 28));
				break;
			case laying:
				dir.push_back(d);
				if (PlayerDir == "R") pos.push_back(glm::ivec2(posPlayer.x + 68, posPlayer.y + 58));	//fix
				else pos.push_back(glm::ivec2(posPlayer.x - 4, posPlayer.y + 58));
				break;
			case up:
				dir.push_back(glm::ivec2(0, -1));
				if (PlayerDir == "R") pos.push_back(glm::ivec2(posPlayer.x + 38, posPlayer.y - 6));
				else pos.push_back(glm::ivec2(posPlayer.x + 28, posPlayer.y - 6));
				break;
			case running_up:
				dir.push_back(glm::vec2(0.75*d.x, -0.25));
				if (PlayerDir == "R") pos.push_back(glm::ivec2(posPlayer.x + 55, posPlayer.y + 5));
				else pos.push_back(glm::ivec2(posPlayer.x + 15, posPlayer.y + 5));
				break;
			case running_down:
				dir.push_back(glm::vec2(0.75*d.x, 0.25));
				if (PlayerDir == "R") pos.push_back(glm::ivec2(posPlayer.x + 55, posPlayer.y + 40));	//fix
				else pos.push_back(glm::ivec2(posPlayer.x + 15, posPlayer.y + 40));
				break;
			case jumping:
				dir.push_back(d);
				pos.push_back(glm::ivec2(posPlayer.x + 32, posPlayer.y + 32));
				break;
			}
			BulletManager::instance().fire(dir, pos, speed);
		}
	}
	else shooting = false;
	if (!swimming) {
		if (PlayerState == standing || PlayerState == running_down || PlayerState == running_up || PlayerState == running || PlayerState == up || PlayerState == laying) {
			if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT) && Game::instance().getSpecialKey(GLUT_KEY_UP))
			{
				if (sprite->animation() != MOVEU45_RIGHT)
					sprite->changeAnimation(MOVEU45_RIGHT);
				PlayerState = running_up;
				PlayerDir = "R";
				posPlayer.x += 2;
				if (map->collisionMoveRight(posPlayer, glm::ivec2(64, 92)))
				{
					posPlayer.x -= 2;
				}
			}
			else if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT) && Game::instance().getSpecialKey(GLUT_KEY_DOWN))
			{
				if (sprite->animation() != MOVED45_RIGHT)
					sprite->changeAnimation(MOVED45_RIGHT);
				PlayerState = running_down;
				PlayerDir = "R";
				posPlayer.x += 2;
				if (map->collisionMoveRight(posPlayer, glm::ivec2(64, 92)))
				{
					posPlayer.x -= 2;
				}
			}
			else if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT) && Game::instance().getKey('z'))
			{
				if (sprite->animation() != MOVESH_RIGHT)
					sprite->changeAnimation(MOVESH_RIGHT);
				PlayerState = running;
				PlayerDir = "R";
				posPlayer.x += 2;
				if (map->collisionMoveRight(posPlayer, glm::ivec2(64, 92)))
				{
					posPlayer.x -= 2;
				}
				if (!shooting) {
					shooting = true;
					vector<glm::vec2> dir;
					vector<glm::vec2> pos;
					pos.push_back(glm::ivec2(posPlayer.x + 60, posPlayer.y + 22));
					dir.push_back(glm::ivec2(1, 0));
					BulletManager::instance().fire(dir, pos, 4);
				}
			}
			else if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT))
			{
				if (sprite->animation() != MOVE_RIGHT)
					sprite->changeAnimation(MOVE_RIGHT);
				PlayerState = running;
				PlayerDir = "R";
				posPlayer.x += 2;
				shooting = false;
				if (map->collisionMoveRight(posPlayer, glm::ivec2(64, 92)))
				{
					posPlayer.x -= 2;
				}
			}
			else if (Game::instance().getSpecialKey(GLUT_KEY_LEFT) && Game::instance().getSpecialKey(GLUT_KEY_DOWN))
			{
				if (sprite->animation() != MOVED45_LEFT)
					sprite->changeAnimation(MOVED45_LEFT);
				PlayerState = running_down;
				PlayerDir = "L";
				posPlayer.x -= 2;
				if (map->collisionMoveLeft(posPlayer, glm::ivec2(64, 92)))
				{
					posPlayer.x += 2;
				}
			}
			else if (Game::instance().getSpecialKey(GLUT_KEY_LEFT) && Game::instance().getSpecialKey(GLUT_KEY_UP))
			{
				if (sprite->animation() != MOVEU45_LEFT)
					sprite->changeAnimation(MOVEU45_LEFT);
				PlayerState = running_up;
				PlayerDir = "L";
				posPlayer.x -= 2;
				if (map->collisionMoveLeft(posPlayer, glm::ivec2(64, 92)))
				{
					posPlayer.x += 2;
				}
			}
			else if (Game::instance().getSpecialKey(GLUT_KEY_LEFT) && Game::instance().getKey('z'))
			{
				if (sprite->animation() != MOVESH_LEFT)
					sprite->changeAnimation(MOVESH_LEFT);
				PlayerState = running;
				PlayerDir = "L";
				posPlayer.x -= 2;
				if (map->collisionMoveLeft(posPlayer, glm::ivec2(64, 92)))
				{
					posPlayer.x += 2;
				}
				if (!shooting) {
					shooting = true;
					vector<glm::vec2> dir;
					vector<glm::vec2> pos;
					pos.push_back(glm::ivec2(posPlayer.x + 4, posPlayer.y + 22));
					dir.push_back(glm::ivec2(-1, 0));
					BulletManager::instance().fire(dir, pos, 4);
				}
			}
			else if (Game::instance().getSpecialKey(GLUT_KEY_LEFT))
			{
				if (sprite->animation() != MOVE_LEFT)
					sprite->changeAnimation(MOVE_LEFT);
				PlayerState = running;
				PlayerDir = "L";
				posPlayer.x -= 2;
				shooting = false;
				if (map->collisionMoveLeft(posPlayer, glm::ivec2(64, 92)))
				{
					posPlayer.x += 2;
				}
			}

			else if (Game::instance().getSpecialKey(GLUT_KEY_UP))
			{
				if (PlayerDir == "L") {
					if (sprite->animation() != UP_LEFT)
						sprite->changeAnimation(UP_LEFT);
					PlayerState = up;
				}
				else {
					if (sprite->animation() != UP_RIGHT)
						sprite->changeAnimation(UP_RIGHT);
					PlayerState = up;
				}
			}
			else if (Game::instance().getSpecialKey(GLUT_KEY_DOWN))
			{
				if (PlayerDir == "L") {
					if (sprite->animation() != LAY_LEFT)
						sprite->changeAnimation(LAY_LEFT);
					PlayerState = laying;
				}
				else {
					if (sprite->animation() != LAY_RIGHT)
						sprite->changeAnimation(LAY_RIGHT);
					PlayerState = laying;
				}
			}
			else {
				if (sprite->animation() != STAND_LEFT && sprite->animation() != STAND_RIGHT)
				{
					if (PlayerDir == "R") sprite->changeAnimation(STAND_RIGHT);
					else sprite->changeAnimation(STAND_LEFT);
				}
				PlayerState = standing;
			}
		}
		if (PlayerState == jumping)
		{
			jumpAngle += JUMP_ANGLE_STEP;
			if (jumpAngle == 180) {
				PlayerState = standing;
				posPlayer.y = startY;
			}
			else
			{
				if (!map->collisionMoveDown(glm::vec2(posPlayer.x + 64, posPlayer.y), glm::ivec2(32, 96), &posPlayer.y)) posPlayer.y = int(startY - 96 * sin(3.14159f * jumpAngle / 180.f));
				else PlayerState = standing;
			}
			if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT)) posPlayer.x += 2;
			else if (Game::instance().getSpecialKey(GLUT_KEY_LEFT)) posPlayer.x -= 2;

		}
		else
		{
			posPlayer.y += FALL_STEP;
			if (map->collisionWater(glm::vec2(posPlayer.x + 64, posPlayer.y), glm::ivec2(32, 96), &posPlayer.y)) {
				swimming = true;
				PlayerState = water_stand;
				if (sprite->animation() != SPLASH)sprite->changeAnimation(SPLASH);
			}
			else if (map->collisionMoveDown(glm::vec2(posPlayer.x + 64, posPlayer.y), glm::ivec2(32, 96), &posPlayer.y)) {
				if (Game::instance().getKey(VK_SPACE) && PlayerState != laying) {
					startY = posPlayer.y;
					jumpAngle = 0;
					PlayerState = jumping;
					if (PlayerDir == "L") {
						if (sprite->animation() != JUMP_LEFT)sprite->changeAnimation(JUMP_LEFT);
					}
					else {
						if (sprite->animation() != JUMP_RIGHT) sprite->changeAnimation(JUMP_RIGHT);
					}
				}
			}
		}
	}
	else {
		if (PlayerState == water_stand || PlayerState == water_run || PlayerState == water_runup || PlayerState == water_up) {
			if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT) && Game::instance().getSpecialKey(GLUT_KEY_UP))
			{
				if (sprite->animation() != WAT_RUNUP_RIGHT)
					sprite->changeAnimation(WAT_RUNUP_RIGHT);
				PlayerState = water_runup;
				PlayerDir = "R";
				posPlayer.x += 2;
				if (map->collisionMoveRight(posPlayer, glm::ivec2(64, 92)))
				{
					posPlayer.x -= 2;
				}
			}
			else if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT) && Game::instance().getKey('z'))
			{
				if (sprite->animation() != MOVESH_RIGHT)
					sprite->changeAnimation(MOVESH_RIGHT);
				PlayerState = running;
				PlayerDir = "R";
				posPlayer.x += 2;
				if (map->collisionMoveRight(posPlayer, glm::ivec2(64, 92)))
				{
					posPlayer.x -= 2;
				}
				if (!shooting) {
					shooting = true;
					vector<glm::vec2> dir;
					vector<glm::vec2> pos;
					pos.push_back(glm::ivec2(posPlayer.x + 60, posPlayer.y + 22));
					dir.push_back(glm::ivec2(1, 0));
					BulletManager::instance().fire(dir, pos, 4);
				}
			}
			else if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT))
			{
				if (sprite->animation() != WAT_RUN_RIGHT)
					sprite->changeAnimation(WAT_RUN_RIGHT);
				PlayerState = water_run;
				PlayerDir = "R";
				posPlayer.x += 2;
				shooting = false;
				if (map->collisionMoveRight(posPlayer, glm::ivec2(64, 92)))
				{
					posPlayer.x -= 2;
				}
			}
			else if (Game::instance().getSpecialKey(GLUT_KEY_LEFT) && Game::instance().getSpecialKey(GLUT_KEY_UP))
			{
				if (sprite->animation() != WAT_RUNUP_LEFT)
					sprite->changeAnimation(WAT_RUNUP_LEFT);
				PlayerState = water_runup;
				PlayerDir = "L";
				posPlayer.x -= 2;
				if (map->collisionMoveLeft(posPlayer, glm::ivec2(64, 92)))
				{
					posPlayer.x += 2;
				}
			}
			else if (Game::instance().getSpecialKey(GLUT_KEY_LEFT) && Game::instance().getKey('z'))
			{
				if (sprite->animation() != MOVESH_RIGHT)
					sprite->changeAnimation(MOVESH_RIGHT);
				PlayerState = running;
				PlayerDir = "L";
				posPlayer.x += 2;
				if (map->collisionMoveRight(posPlayer, glm::ivec2(64, 92)))
				{
					posPlayer.x -= 2;
				}
				if (!shooting) {
					shooting = true;
					vector<glm::vec2> dir;
					vector<glm::vec2> pos;
					pos.push_back(glm::ivec2(posPlayer.x + 60, posPlayer.y + 22));
					dir.push_back(glm::ivec2(1, 0));
					BulletManager::instance().fire(dir, pos, 4);
				}
			}
			else if (Game::instance().getSpecialKey(GLUT_KEY_LEFT))
			{
				if (sprite->animation() != WAT_RUN_LEFT)
					sprite->changeAnimation(WAT_RUN_LEFT);
				PlayerState = water_run;
				PlayerDir = "L";
				posPlayer.x -= 2;
				shooting = false;
				if (map->collisionMoveLeft(posPlayer, glm::ivec2(64, 92)))
				{
					posPlayer.x += 2;
				}
			}
			else if (Game::instance().getSpecialKey(GLUT_KEY_UP))
			{
				if (PlayerDir == "L") {
					if (sprite->animation() != WAT_UP_LEFT)
						sprite->changeAnimation(WAT_UP_LEFT);
					PlayerState = water_up;
				}
				else {
					if (sprite->animation() != WAT_UP_RIGHT)
						sprite->changeAnimation(WAT_UP_RIGHT);
					PlayerState = water_up;
				}
			}
			else {
				if (sprite->animation() != WAT_STAND_LEFT && sprite->animation() != WAT_STAND_RIGHT)
				{
					if (PlayerDir == "R") sprite->changeAnimation(WAT_STAND_RIGHT);
					else sprite->changeAnimation(WAT_STAND_LEFT);
				}
				PlayerState = water_stand;
			}
		}
	}
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

void Player::render()
{
	sprite->render();
}

void Player::setTileMap(TileMap *tileMap)
{
	map = tileMap;
}

void Player::setPosition(const glm::vec2 &pos)
{
	posPlayer = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

glm::ivec2 Player::getPosition()
{
	return posPlayer;
}

int Player::getLifes()
{
	return RestLifes;
}



