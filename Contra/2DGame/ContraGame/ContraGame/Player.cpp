#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Player.h"
#include "Game.h"
#include "BulletManager.h"
#include "EnemyManager.h"
#include "Time.h"
#include "Boss.h"
#include "SoundSystem.h"
#include <Windows.h>
#include <stdio.h>
#include <cstdlib>


#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 96
#define FALL_STEP 4


enum PlayerAnims
{
	STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT, MOVESH_LEFT, MOVESH_RIGHT, JUMP_LEFT, JUMP_RIGHT, 
	LAY_LEFT, LAY_RIGHT, UP_LEFT, UP_RIGHT, DIE_LEFT, DIE_RIGHT, MOVEU45_LEFT, MOVEU45_RIGHT, MOVED45_LEFT, MOVED45_RIGHT,
	WAT_RUN_LEFT,WAT_RUN_RIGHT,WAT_UP_LEFT,WAT_UP_RIGHT,WAT_STAND_RIGHT,WAT_STAND_LEFT,WAT_RUNUP_RIGHT,WAT_RUNUP_LEFT,SPLASH, WAT_SHOOT_RIGHT, WAT_SHOOT_LEFT
};

enum PlayerStates
{
	standing, running, laying, up, running_up, running_down, jumping, water_stand, water_up, water_run, water_runup, rip
};


void Player::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram, bool level)
{
	PlayerState = standing;
	PlayerDir = "R";
	RestLifes = 3;
	F = false;
	reviving = false;
	angle_aux = 0;
	shooting = false;
	swimming = false;
	powerup = false;
	RageMode = false;
	level1 = level;
	RageLevel = 1;
	spritesheet.loadFromFile("images/soldado.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(96, 96), glm::vec2(1/11.f, 1/11.f), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(29);
	
		sprite->setAnimationSpeed(STAND_LEFT, 8);
		sprite->addKeyframe(STAND_LEFT, glm::vec2(1/11.f,0.f));
		
		sprite->setAnimationSpeed(STAND_RIGHT, 8);
		sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.f, 0.f));
		
		sprite->setAnimationSpeed(MOVE_RIGHT, 8*RageLevel);
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(6/11.f, 3/11.f));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(7/11.f, 3/11.f));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(8/11.f, 3/11.f));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(9/11.f, 3/11.f));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(10/11.f, 2/11.f));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(10/11.f, 3/11.f));
		
		sprite->setAnimationSpeed(MOVE_LEFT, 8 * RageLevel);
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(6/11.f, 4/11.f));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(6/11.f, 5/11.f));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(7/11.f, 4/11.f));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(8/11.f, 4/11.f));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(9/11.f, 4/11.f));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(10/11.f, 4/11.f));

		sprite->setAnimationSpeed(MOVESH_LEFT, 8 * RageLevel);
		sprite->addKeyframe(MOVESH_LEFT, glm::vec2(5 / 11.f, 3 / 11.f));
		sprite->addKeyframe(MOVESH_LEFT, glm::vec2(4 / 11.f, 3 / 11.f));
		sprite->addKeyframe(MOVESH_LEFT, glm::vec2(3 / 11.f, 3 / 11.f));

		sprite->setAnimationSpeed(MOVESH_RIGHT, 8 * RageLevel);
		sprite->addKeyframe(MOVESH_RIGHT, glm::vec2(0 / 11.f, 3 / 11.f));
		sprite->addKeyframe(MOVESH_RIGHT, glm::vec2(1 / 11.f, 3 / 11.f));
		sprite->addKeyframe(MOVESH_RIGHT, glm::vec2(2 / 11.f, 3 / 11.f));

		sprite->setAnimationSpeed(MOVEU45_RIGHT, 8 * RageLevel);
		sprite->addKeyframe(MOVEU45_RIGHT, glm::vec2(0 / 11.f, 4 / 11.f));
		sprite->addKeyframe(MOVEU45_RIGHT, glm::vec2(1 / 11.f, 4 / 11.f));
		sprite->addKeyframe(MOVEU45_RIGHT, glm::vec2(2 / 11.f, 4 / 11.f));

		sprite->setAnimationSpeed(MOVED45_RIGHT, 8 * RageLevel);
		sprite->addKeyframe(MOVED45_RIGHT, glm::vec2(0 / 11.f, 5 / 11.f));
		sprite->addKeyframe(MOVED45_RIGHT, glm::vec2(1 / 11.f, 5 / 11.f));
		sprite->addKeyframe(MOVED45_RIGHT, glm::vec2(2 / 11.f, 5 / 11.f));

		sprite->setAnimationSpeed(MOVEU45_LEFT, 8 * RageLevel);
		sprite->addKeyframe(MOVEU45_LEFT, glm::vec2(3 / 11.f, 4 / 11.f));
		sprite->addKeyframe(MOVEU45_LEFT, glm::vec2(4 / 11.f, 4 / 11.f));
		sprite->addKeyframe(MOVEU45_LEFT, glm::vec2(5 / 11.f, 4 / 11.f));

		sprite->setAnimationSpeed(MOVED45_LEFT, 8 * RageLevel);
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

		sprite->setAnimationSpeed(DIE_RIGHT, 6);
		sprite->addKeyframe(DIE_RIGHT, glm::vec2(3 / 11.f, 2 / 11.f));
		sprite->addKeyframe(DIE_RIGHT, glm::vec2(2 / 11.f, 2 / 11.f));
		sprite->addKeyframe(DIE_RIGHT, glm::vec2(1 / 11.f, 2 / 11.f));
		sprite->addKeyframe(DIE_RIGHT, glm::vec2(0 / 11.f, 2 / 11.f));
		sprite->addKeyframe(DIE_RIGHT, glm::vec2(4 / 11.f, 2 / 11.f));
		sprite->addKeyframe(DIE_RIGHT, glm::vec2(4 / 11.f, 2 / 11.f));
		sprite->addKeyframe(DIE_RIGHT, glm::vec2(4 / 11.f, 2 / 11.f));

		sprite->setAnimationSpeed(DIE_LEFT, 6);
		sprite->addKeyframe(DIE_LEFT, glm::vec2(6 / 11.f, 2 / 11.f));
		sprite->addKeyframe(DIE_LEFT, glm::vec2(7 / 11.f, 2 / 11.f));
		sprite->addKeyframe(DIE_LEFT, glm::vec2(8 / 11.f, 2 / 11.f));
		sprite->addKeyframe(DIE_LEFT, glm::vec2(9 / 11.f, 2 / 11.f));
		sprite->addKeyframe(DIE_LEFT, glm::vec2(5 / 11.f, 2 / 11.f));
		sprite->addKeyframe(DIE_LEFT, glm::vec2(5 / 11.f, 2 / 11.f));
		sprite->addKeyframe(DIE_LEFT, glm::vec2(5 / 11.f, 2 / 11.f));

		sprite->setAnimationSpeed(WAT_STAND_LEFT, 8);
		sprite->addKeyframe(WAT_STAND_LEFT, glm::vec2(9 / 11.f, 6/11.f));

		sprite->setAnimationSpeed(WAT_STAND_RIGHT, 8);
		sprite->addKeyframe(WAT_STAND_RIGHT, glm::vec2(2 / 11.f, 6/11.f));
		
		sprite->setAnimationSpeed(WAT_RUN_LEFT, 8 * RageLevel);
		sprite->addKeyframe(WAT_RUN_LEFT, glm::vec2(10 / 11.f, 6 / 11.f));
		
		sprite->setAnimationSpeed(WAT_RUN_RIGHT, 8 * RageLevel);
		sprite->addKeyframe(WAT_RUN_RIGHT, glm::vec2(1 / 11.f, 6 / 11.f));

		sprite->setAnimationSpeed(WAT_RUNUP_LEFT, 8 * RageLevel);
		sprite->addKeyframe(WAT_RUNUP_LEFT, glm::vec2(7 / 11.f, 6 / 11.f));

		sprite->setAnimationSpeed(WAT_RUNUP_RIGHT, 8 * RageLevel);
		sprite->addKeyframe(WAT_RUNUP_RIGHT, glm::vec2(4 / 11.f, 6 / 11.f));
		
		sprite->setAnimationSpeed(WAT_UP_LEFT, 8);
		sprite->addKeyframe(WAT_UP_LEFT, glm::vec2(6 / 11.f, 6 / 11.f));

		sprite->setAnimationSpeed(WAT_UP_RIGHT, 8);
		sprite->addKeyframe(WAT_UP_RIGHT, glm::vec2(5 / 11.f, 6 / 11.f));

		sprite->setAnimationSpeed(WAT_SHOOT_LEFT, 8 * RageLevel);
		sprite->addKeyframe(WAT_SHOOT_LEFT, glm::vec2(8 / 11.f, 6 / 11.f));

		sprite->setAnimationSpeed(WAT_SHOOT_RIGHT, 8 * RageLevel);
		sprite->addKeyframe(WAT_SHOOT_RIGHT, glm::vec2(3 / 11.f, 6 / 11.f));

		sprite->setAnimationSpeed(SPLASH, 8);
		sprite->addKeyframe(SPLASH, glm::vec2(0 / 11.f, 6 / 11.f));
		

	sprite->changeAnimation(1);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	
}

void Player::update(int deltaTime)
{
	angle_aux += 45;
	if (angle_aux == 360) angle_aux = 0;
	sprite->update(deltaTime);
	if (RestLifes == 1 && !RageMode) {
		RageLevel = 1.5;
		RageMode = true;
		spritesheet.loadFromFile("images/soldadoRaged.png", TEXTURE_PIXEL_FORMAT_RGBA);
	}
	if(PlayerState == laying || swimming) {
		if (!F && !reviving && (posPlayer.y + 96> SCREEN_HEIGHT || BulletManager::instance().existsBulletColision(glm::vec2(posPlayer.x + 32, posPlayer.y + 56), 32, 40, "PLAYER") || EnemyManager::instance().existsPlayerColision(glm::vec2(posPlayer.x + 32, posPlayer.y + 6), 32, 90) || Boss::instance().existsBulletColision(glm::vec2(posPlayer.x + 32, posPlayer.y + 56), 32, 40))) {
			if (RageLevel > 1) {
				RageLevel = 1;
				if (RageMode) spritesheet.loadFromFile("images/soldado.png", TEXTURE_PIXEL_FORMAT_RGBA);
			}
			else {
				F = true;
				reviving = true;
				RestLifes -= 1;
				DieSec = Time::instance().NowToMili();
			}
		}
	}
	else {
		if (!F && !reviving && (posPlayer.y + 96 > SCREEN_HEIGHT || BulletManager::instance().existsBulletColision(glm::vec2(posPlayer.x + 32, posPlayer.y + 6), 32, 90, "PLAYER") || EnemyManager::instance().existsPlayerColision(glm::vec2(posPlayer.x + 32, posPlayer.y + 6), 32, 90) || Boss::instance().existsBulletColision(glm::vec2(posPlayer.x + 32, posPlayer.y + 6), 32, 90))) {
			if (RageLevel > 1) {
				RageLevel = 1;
				if (RageMode) spritesheet.loadFromFile("images/soldado.png", TEXTURE_PIXEL_FORMAT_RGBA);
			}
			else {
				F = true;
				reviving = true;
				RestLifes -= 1;
				DieSec = Time::instance().NowToMili();
			}
		}
	}
	if (F && reviving) {
		if((posPlayer.y + 96> SCREEN_HEIGHT)) posPlayer.y = SCREEN_HEIGHT-100;
		if (PlayerDir == "R") {
			if (sprite->animation() != DIE_RIGHT)
				sprite->changeAnimation(DIE_RIGHT);
		}
		else {
			if (sprite->animation() != DIE_LEFT)
				sprite->changeAnimation(DIE_LEFT);
		}
		if (Time::instance().NowToMili() - DieSec > 1000) {
			if(level1) posPlayer.x -= 50;
			if(level1) posPlayer.y = 30;
			PlayerState = standing;
			F = false;
		}
	}
	else {
		if (Time::instance().NowToMili() - DieSec > 3000) reviving = false;
		if (!powerup && posPlayer.x + 90 > 126 * 32 + 5 && posPlayer.x + 16 < 126 * 32 + 5 && posPlayer.y + 90 > 126 && posPlayer.y + 90< 166) powerup = true;	
		if (Game::instance().getKey('z')) {
			if (!shooting) {
				if (PlayerState != running && PlayerState != water_run) shooting = true;
				int speed = 4 * RageLevel;
				vector<glm::vec2> dir;
				vector<glm::vec2> pos;
				glm::vec2 d = glm::vec2(1, 0);
				glm::ivec2 p = glm::ivec2(posPlayer.x + 64, posPlayer.y + 28);
				if (PlayerDir == "L") d = glm::ivec2(-1, 0);
				switch (PlayerState)
				{
				case standing:
					dir.push_back(d);
					if (PlayerDir == "R") {
						p = glm::ivec2(posPlayer.x + 64, posPlayer.y + 28);
						pos.push_back(glm::ivec2(posPlayer.x + 64, posPlayer.y + 28));
					}
					else {
						p = glm::ivec2(posPlayer.x + 6, posPlayer.y + 28);
						pos.push_back(glm::ivec2(posPlayer.x + 6, posPlayer.y + 28));
					}
					if (powerup) {
						pos.push_back(p);
						pos.push_back(p);
						pos.push_back(p);
						pos.push_back(p);
						dir.push_back(glm::vec2(d.x, d.y + 0.1));
						dir.push_back(glm::vec2(d.x, d.y + 0.3));
						dir.push_back(glm::vec2(d.x, d.y - 0.1));
						dir.push_back(glm::vec2(d.x, d.y - 0.3));
					}
					break;
				case laying:
					dir.push_back(d);
					if (PlayerDir == "R") {
						p = glm::ivec2(posPlayer.x + 68, posPlayer.y + 58);
						pos.push_back(glm::ivec2(posPlayer.x + 68, posPlayer.y + 58));
					}
					else {
						p = glm::ivec2(posPlayer.x - 4, posPlayer.y + 58);
						pos.push_back(glm::ivec2(posPlayer.x - 4, posPlayer.y + 58));
					}
					if (powerup) {
						pos.push_back(p);
						pos.push_back(p);
						pos.push_back(p);
						pos.push_back(p);
						dir.push_back(glm::vec2(d.x, d.y + 0.1));
						dir.push_back(glm::vec2(d.x, d.y + 0.3));
						dir.push_back(glm::vec2(d.x, d.y - 0.1));
						dir.push_back(glm::vec2(d.x, d.y - 0.3));
					}
					break;
				case up:
					d = glm::ivec2(0, -1);
					dir.push_back(d);
					if (PlayerDir == "R") {
						p = glm::ivec2(posPlayer.x + 38, posPlayer.y - 6);
						pos.push_back(glm::ivec2(posPlayer.x + 38, posPlayer.y - 6));
					}
					else {
						p = glm::ivec2(posPlayer.x + 28, posPlayer.y - 6);
						pos.push_back(glm::ivec2(posPlayer.x + 28, posPlayer.y - 6));
					}
					if (powerup) {
						pos.push_back(p);
						pos.push_back(p);
						pos.push_back(p);
						pos.push_back(p);
						dir.push_back(glm::vec2(d.x + 0.1, d.y));
						dir.push_back(glm::vec2(d.x + 0.3, d.y));
						dir.push_back(glm::vec2(d.x - 0.1, d.y));
						dir.push_back(glm::vec2(d.x - 0.3, d.y));
					}
					break;
				case water_up:
					d = glm::ivec2(0, -1);
					dir.push_back(d);
					if (PlayerDir == "R") {
						p = glm::ivec2(posPlayer.x + 38, posPlayer.y - 6);
						pos.push_back(glm::ivec2(posPlayer.x + 38, posPlayer.y - 6));
					}
					else {
						p = glm::ivec2(posPlayer.x + 28, posPlayer.y - 6);
						pos.push_back(glm::ivec2(posPlayer.x + 28, posPlayer.y - 6));
					}
					if (powerup) {
						pos.push_back(p);
						pos.push_back(p);
						pos.push_back(p);
						pos.push_back(p);
						dir.push_back(glm::vec2(d.x + 0.1, d.y));
						dir.push_back(glm::vec2(d.x + 0.3, d.y));
						dir.push_back(glm::vec2(d.x - 0.1, d.y));
						dir.push_back(glm::vec2(d.x - 0.3, d.y));
					}
					break;
				case running_up:
					d = glm::vec2(0.5*d.x, -0.5);
					dir.push_back(d);
					if (PlayerDir == "R") {
						p = glm::ivec2(posPlayer.x + 55, posPlayer.y + 5);
						pos.push_back(glm::ivec2(posPlayer.x + 55, posPlayer.y + 5));
					}
					else {
						p = glm::ivec2(posPlayer.x + 15, posPlayer.y + 5);
						pos.push_back(glm::ivec2(posPlayer.x + 15, posPlayer.y + 5));
					}
					if (powerup) {
						pos.push_back(p);
						pos.push_back(p);
						pos.push_back(p);
						pos.push_back(p);
						dir.push_back(glm::vec2(d.x + 0.1, d.y));
						dir.push_back(glm::vec2(d.x + 0.3, d.y));
						dir.push_back(glm::vec2(d.x - 0.1, d.y));
						dir.push_back(glm::vec2(d.x - 0.3, d.y));
					}
					break;
				case water_runup:
					d = glm::vec2(0.5*d.x, -0.5);
					dir.push_back(d);
					if (PlayerDir == "R") {
						p = glm::ivec2(posPlayer.x + 55, posPlayer.y + 27);
						pos.push_back(glm::ivec2(posPlayer.x + 55, posPlayer.y + 27));
					}
					else {
						p = glm::ivec2(posPlayer.x + 15, posPlayer.y + 30);
						pos.push_back(glm::ivec2(posPlayer.x + 15, posPlayer.y + 30));
					}
					if (powerup) {
						pos.push_back(p);
						pos.push_back(p);
						pos.push_back(p);
						pos.push_back(p);
						dir.push_back(glm::vec2(d.x + 0.1, d.y));
						dir.push_back(glm::vec2(d.x + 0.3, d.y));
						dir.push_back(glm::vec2(d.x - 0.1, d.y));
						dir.push_back(glm::vec2(d.x - 0.3, d.y));
					}
					break;
				case running_down:
					d = glm::vec2(0.5*d.x, 0.5);
					dir.push_back(d);
					if (PlayerDir == "R") {
						p = glm::ivec2(posPlayer.x + 55, posPlayer.y + 40);
						pos.push_back(glm::ivec2(posPlayer.x + 55, posPlayer.y + 40));
					}
					else {
						p = glm::ivec2(posPlayer.x + 15, posPlayer.y + 40);
						pos.push_back(glm::ivec2(posPlayer.x + 15, posPlayer.y + 40));
					}
					if (powerup) {
						pos.push_back(p);
						pos.push_back(p);
						pos.push_back(p);
						pos.push_back(p);
						dir.push_back(glm::vec2(d.x + 0.1, d.y));
						dir.push_back(glm::vec2(d.x + 0.3, d.y));
						dir.push_back(glm::vec2(d.x - 0.1, d.y));
						dir.push_back(glm::vec2(d.x - 0.3, d.y));
					}
					break;
				case jumping:
					dir.push_back(d);
					p = glm::ivec2(posPlayer.x + 32, posPlayer.y + 32);
					pos.push_back(p);
					if (powerup) {
						pos.push_back(p);
						pos.push_back(p);
						pos.push_back(p);
						pos.push_back(p);
						dir.push_back(glm::vec2(d.x, d.y + 0.1));
						dir.push_back(glm::vec2(d.x, d.y + 0.3));
						dir.push_back(glm::vec2(d.x, d.y - 0.1));
						dir.push_back(glm::vec2(d.x, d.y - 0.3));
					}
					break;
				}
				BulletManager::instance().fire(dir, pos, speed, "CHARACTER");
				SoundSystem::instance().playSoundEffect("level01", "SHOOT", "CHARACTER");
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
					posPlayer.x += 2 * RageLevel;
					if (level1) {
						if (map->collisionMoveRight(posPlayer, glm::ivec2(64, 92)))
						{
							posPlayer.x -= 2;
						}
					}
					else if (posPlayer.x > 510) posPlayer.x -= 2;
				}
				else if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT) && Game::instance().getSpecialKey(GLUT_KEY_DOWN))
				{
					if (sprite->animation() != MOVED45_RIGHT)
						sprite->changeAnimation(MOVED45_RIGHT);
					PlayerState = running_down;
					PlayerDir = "R";
					posPlayer.x += 2 * RageLevel;
					if (level1) {
						if (map->collisionMoveRight(posPlayer, glm::ivec2(64, 92)))
						{
							posPlayer.x -= 2;
						}
					}
					else if (posPlayer.x > 496) posPlayer.x -= 2;
				}
				else if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT) && Game::instance().getKey('z'))
				{
					if (sprite->animation() != MOVESH_RIGHT)
						sprite->changeAnimation(MOVESH_RIGHT);
					PlayerState = running;
					PlayerDir = "R";
					posPlayer.x += 2 * RageLevel;
					if (level1) {
						if (map->collisionMoveRight(posPlayer, glm::ivec2(64, 92)))
						{
							posPlayer.x -= 2;
						}
					}
					else if (posPlayer.x > 496) posPlayer.x -= 2;
					if (!shooting) {
						shooting = true;
						vector<glm::vec2> dir;
						vector<glm::vec2> pos;
						glm::vec2 d = glm::vec2(1, 0);
						glm::ivec2 p = glm::ivec2(posPlayer.x + 60, posPlayer.y + 22);
						pos.push_back(glm::ivec2(posPlayer.x + 60, posPlayer.y + 22));
						dir.push_back(glm::ivec2(1, 0));
						if (powerup) {
							pos.push_back(p);
							pos.push_back(p);
							pos.push_back(p);
							pos.push_back(p);
							dir.push_back(glm::vec2(d.x, d.y + 0.1));
							dir.push_back(glm::vec2(d.x, d.y + 0.3));
							dir.push_back(glm::vec2(d.x, d.y - 0.1));
							dir.push_back(glm::vec2(d.x, d.y - 0.3));
						}
						BulletManager::instance().fire(dir, pos, 4 * RageLevel, "CHARACTER");
						SoundSystem::instance().playSoundEffect("level01", "SHOOT", "CHARACTER");
					}
				}
				else if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT))
				{
					if (sprite->animation() != MOVE_RIGHT)
						sprite->changeAnimation(MOVE_RIGHT);
					PlayerState = running;
					PlayerDir = "R";
					posPlayer.x += 2 * RageLevel;
					shooting = false;
					if (level1) {
						if (map->collisionMoveRight(posPlayer, glm::ivec2(64, 92)))
						{
							posPlayer.x -= 2;
						}
					}
					else if (posPlayer.x > 525) posPlayer.x -= 2;
				}
				else if (Game::instance().getSpecialKey(GLUT_KEY_LEFT) && Game::instance().getSpecialKey(GLUT_KEY_DOWN))
				{
					if (sprite->animation() != MOVED45_LEFT)
						sprite->changeAnimation(MOVED45_LEFT);
					PlayerState = running_down;
					PlayerDir = "L";
					posPlayer.x -= 2 * RageLevel;
					if (level1) {
						if (map->collisionMoveLeft(posPlayer, glm::ivec2(64, 92)))
						{
							posPlayer.x += 2;
						}
					}
					else if (posPlayer.x < -30) posPlayer.x += 2;
				}
				else if (Game::instance().getSpecialKey(GLUT_KEY_LEFT) && Game::instance().getSpecialKey(GLUT_KEY_UP))
				{
					if (sprite->animation() != MOVEU45_LEFT)
						sprite->changeAnimation(MOVEU45_LEFT);
					PlayerState = running_up;
					PlayerDir = "L";
					posPlayer.x -= 2 * RageLevel;
					if (level1) {
						if (map->collisionMoveLeft(posPlayer, glm::ivec2(64, 92)))
						{
							posPlayer.x += 2;
						}
					}
					else if (posPlayer.x < -30) posPlayer.x += 2;
				}
				else if (Game::instance().getSpecialKey(GLUT_KEY_LEFT) && Game::instance().getKey('z'))
				{
					if (sprite->animation() != MOVESH_LEFT)
						sprite->changeAnimation(MOVESH_LEFT);
					PlayerState = running;
					PlayerDir = "L";
					posPlayer.x -= 2 * RageLevel;
					if (level1) {
						if (map->collisionMoveLeft(posPlayer, glm::ivec2(64, 92)))
						{
							posPlayer.x += 2;
						}
					}
					else if (posPlayer.x < -30) posPlayer.x += 2;
					if (!shooting) {
						shooting = true;
						vector<glm::vec2> dir;
						vector<glm::vec2> pos;
						glm::vec2 d = glm::vec2(-1, 0);
						glm::ivec2 p = glm::ivec2(posPlayer.x + 4, posPlayer.y + 22);
						pos.push_back(glm::ivec2(posPlayer.x + 4, posPlayer.y + 22));
						dir.push_back(glm::ivec2(-1, 0));
						if (powerup) {
							pos.push_back(p);
							pos.push_back(p);
							pos.push_back(p);
							pos.push_back(p);
							dir.push_back(glm::vec2(d.x, d.y + 0.1));
							dir.push_back(glm::vec2(d.x, d.y + 0.3));
							dir.push_back(glm::vec2(d.x, d.y - 0.1));
							dir.push_back(glm::vec2(d.x, d.y - 0.3));
						}
						BulletManager::instance().fire(dir, pos, 4 * RageLevel, "CHARACTER");
						SoundSystem::instance().playSoundEffect("level01", "SHOOT", "CHARACTER");
					}
				}
				else if (Game::instance().getSpecialKey(GLUT_KEY_LEFT))
				{
					if (sprite->animation() != MOVE_LEFT)
						sprite->changeAnimation(MOVE_LEFT);
					PlayerState = running;
					PlayerDir = "L";
					posPlayer.x -= 2 * RageLevel;
					shooting = false;
					if (level1) {
						if (map->collisionMoveLeft(posPlayer, glm::ivec2(64, 92)))
						{
							posPlayer.x += 2;
						}
					}
					else if (posPlayer.x < -30) posPlayer.x += 2;
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
					if (!level1) {
						if (!map->collisionMoveDown(glm::vec2(posPlayer.x + 64, posPlayer.y), glm::ivec2(32, 80), &posPlayer.y)) posPlayer.y = int(startY - 96 * sin(3.14159f * jumpAngle / 180.f));
						else PlayerState = standing;
					}
					else {
						if (!map->collisionMoveDown(glm::vec2(posPlayer.x + 64, posPlayer.y), glm::ivec2(32, 90), &posPlayer.y)) posPlayer.y = int(startY - 96 * sin(3.14159f * jumpAngle / 180.f));
						else PlayerState = standing;
					}
				}
				if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT)) posPlayer.x += 2 * RageLevel;
				else if (Game::instance().getSpecialKey(GLUT_KEY_LEFT)) posPlayer.x -= 2 * RageLevel;

			}
			else
			{
				posPlayer.y += FALL_STEP;
				if (map->collisionWater(glm::vec2(posPlayer.x + 64, posPlayer.y), glm::ivec2(32, 96), &posPlayer.y)) {
					swimming = true;
					PlayerState = water_stand;
					if (sprite->animation() != SPLASH)sprite->changeAnimation(SPLASH);
				}
				else {
					if (!level1) {
						if (map->collisionMoveDown(glm::vec2(posPlayer.x + 64, posPlayer.y), glm::ivec2(32, 80), &posPlayer.y)) {
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
					else {
						if (map->collisionMoveDown(glm::vec2(posPlayer.x + 64, posPlayer.y), glm::ivec2(32, 90), &posPlayer.y)) {
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
					posPlayer.x += 2 * RageLevel;
					if (map->collisionOutWaterRight(glm::vec2(posPlayer.x + 64, posPlayer.y + 40), glm::ivec2(32, 52)))
					{
						posPlayer.x += 30;
						posPlayer.y -= 54;
						PlayerState = standing;
						swimming = false;
						sprite->changeAnimation(JUMP_RIGHT);
					}
				}
				else if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT) && Game::instance().getKey('z'))
				{
					if (sprite->animation() != WAT_SHOOT_RIGHT)
						sprite->changeAnimation(WAT_SHOOT_RIGHT);
					PlayerState = water_run;
					PlayerDir = "R";
					posPlayer.x += 2 * RageLevel;
					if (map->collisionOutWaterRight(glm::vec2(posPlayer.x + 64, posPlayer.y + 40), glm::ivec2(32, 52)))
					{
						posPlayer.x += 30;
						posPlayer.y -= 54;
						PlayerState = standing;
						swimming = false;
						sprite->changeAnimation(JUMP_RIGHT);
					}
					if (!shooting) {
						shooting = true;
						vector<glm::vec2> dir;
						vector<glm::vec2> pos;
						glm::vec2 d = glm::vec2(1, 0);
						glm::ivec2 p = glm::ivec2(posPlayer.x + 60, posPlayer.y + 55);
						pos.push_back(glm::ivec2(posPlayer.x + 60, posPlayer.y + 55));
						dir.push_back(glm::ivec2(1, 0));
						if (powerup) {
							pos.push_back(p);
							pos.push_back(p);
							pos.push_back(p);
							pos.push_back(p);
							dir.push_back(glm::vec2(d.x, d.y + 0.1));
							dir.push_back(glm::vec2(d.x, d.y + 0.3));
							dir.push_back(glm::vec2(d.x, d.y - 0.1));
							dir.push_back(glm::vec2(d.x, d.y - 0.3));
						}
						BulletManager::instance().fire(dir, pos, 4 * RageLevel, "CHARACTER");
						SoundSystem::instance().playSoundEffect("level01", "SHOOT", "CHARACTER");
					}
				}
				else if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT))
				{
					if (sprite->animation() != WAT_RUN_RIGHT)
						sprite->changeAnimation(WAT_RUN_RIGHT);
					PlayerState = water_run;
					PlayerDir = "R";
					posPlayer.x += 2 * RageLevel;
					shooting = false;
					if (map->collisionOutWaterRight(glm::vec2(posPlayer.x + 64, posPlayer.y + 40), glm::ivec2(32, 52)))
					{
						posPlayer.x += 30;
						posPlayer.y -= 54;
						PlayerState = standing;
						swimming = false;
						sprite->changeAnimation(JUMP_RIGHT);
					}
				}
				else if (Game::instance().getSpecialKey(GLUT_KEY_LEFT) && Game::instance().getSpecialKey(GLUT_KEY_UP))
				{
					if (sprite->animation() != WAT_RUNUP_LEFT)
						sprite->changeAnimation(WAT_RUNUP_LEFT);
					PlayerState = water_runup;
					PlayerDir = "L";
					posPlayer.x -= 2 * RageLevel;
					if (map->collisionOutWaterLeft(glm::vec2(posPlayer.x, posPlayer.y + 40), glm::ivec2(64, 52)))
					{
						posPlayer.x += 30;
						posPlayer.y -= 54;
						PlayerState = standing;
						swimming = false;
						sprite->changeAnimation(JUMP_RIGHT);
					}
				}
				else if (Game::instance().getSpecialKey(GLUT_KEY_LEFT) && Game::instance().getKey('z'))
				{
					if (sprite->animation() != WAT_SHOOT_LEFT)
						sprite->changeAnimation(WAT_SHOOT_LEFT);
					PlayerState = water_run;
					PlayerDir = "L";
					posPlayer.x -= 2 * RageLevel;
					if (map->collisionOutWaterLeft(glm::vec2(posPlayer.x, posPlayer.y + 40), glm::ivec2(64, 52)))
					{
						posPlayer.x += 30;
						posPlayer.y -= 54;
						PlayerState = standing;
						swimming = false;
						sprite->changeAnimation(JUMP_RIGHT);
					}
					if (!shooting) {
						shooting = true;
						vector<glm::vec2> dir;
						vector<glm::vec2> pos;
						glm::vec2 d = glm::vec2(-1, 0);
						glm::ivec2 p = glm::ivec2(posPlayer.x + 4, posPlayer.y + 55);
						pos.push_back(glm::ivec2(posPlayer.x + 4, posPlayer.y + 55));
						dir.push_back(glm::ivec2(-1, 0));
						if (powerup) {
							pos.push_back(p);
							pos.push_back(p);
							pos.push_back(p);
							pos.push_back(p);
							dir.push_back(glm::vec2(d.x, d.y + 0.1));
							dir.push_back(glm::vec2(d.x, d.y + 0.3));
							dir.push_back(glm::vec2(d.x, d.y - 0.1));
							dir.push_back(glm::vec2(d.x, d.y - 0.3));
						}
						BulletManager::instance().fire(dir, pos, 4 * RageLevel, "CHARACTER");
						SoundSystem::instance().playSoundEffect("level01", "SHOOT", "CHARACTER");
					}
				}
				else if (Game::instance().getSpecialKey(GLUT_KEY_LEFT))
				{
					if (sprite->animation() != WAT_RUN_LEFT)
						sprite->changeAnimation(WAT_RUN_LEFT);
					PlayerState = water_run;
					PlayerDir = "L";
					posPlayer.x -= 2 * RageLevel;
					shooting = false;
					if (map->collisionOutWaterLeft(glm::vec2(posPlayer.x, posPlayer.y + 40), glm::ivec2(64, 52)))
					{
						posPlayer.x -= 30;
						posPlayer.y -= 54;
						PlayerState = standing;
						swimming = false;
						sprite->changeAnimation(JUMP_RIGHT);
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
	}
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

enum PlayerAnimslv2
{
	STAND_LV2, LAY_LV2, MOVE_LEFT_LV2, MOVE_RIGHT_LV2, MOVE_UP_LV2, JUMP_RIGHT_LV2, JUMP_LEFT_LV2, DIE_RIGHT_LV2, DIE_LEFT_LV2
};
void Player::initlevel2(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	PlayerState = standing;
	PlayerDir = "R";
	RestLifes = 3;
	angle_aux = 0;
	spritesheet.loadFromFile("images/soldado.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(96, 96), glm::vec2(1 / 11.f, 1 / 11.f), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(9);

	sprite->setAnimationSpeed(STAND_LV2, 8);
	sprite->addKeyframe(STAND_LV2, glm::vec2(0 / 11.f, 7 / 11.f));

	sprite->setAnimationSpeed(LAY_LV2, 8);
	sprite->addKeyframe(LAY_LV2, glm::vec2(2 / 11.f, 7 / 11.f));
	sprite->addKeyframe(LAY_LV2, glm::vec2(3 / 11.f, 7 / 11.f));

	sprite->setAnimationSpeed(MOVE_LEFT_LV2, 8);
	sprite->addKeyframe(MOVE_LEFT_LV2, glm::vec2(3 / 11.f, 8 / 11.f));
	sprite->addKeyframe(MOVE_LEFT_LV2, glm::vec2(4 / 11.f, 8 / 11.f));
	sprite->addKeyframe(MOVE_LEFT_LV2, glm::vec2(5 / 11.f, 8 / 11.f));

	sprite->setAnimationSpeed(MOVE_RIGHT_LV2, 8);
	sprite->addKeyframe(MOVE_RIGHT_LV2, glm::vec2(0 / 11.f, 8 / 11.f));
	sprite->addKeyframe(MOVE_RIGHT_LV2, glm::vec2(1 / 11.f, 8 / 11.f));
	sprite->addKeyframe(MOVE_RIGHT_LV2, glm::vec2(2 / 11.f, 8 / 11.f));

	sprite->setAnimationSpeed(MOVE_UP_LV2, 8);
	sprite->addKeyframe(MOVE_UP_LV2, glm::vec2(4 / 11.f, 7 / 11.f));
	sprite->addKeyframe(MOVE_UP_LV2, glm::vec2(5 / 11.f, 7 / 11.f));

	sprite->setAnimationSpeed(JUMP_RIGHT_LV2, 8);
	sprite->addKeyframe(JUMP_RIGHT_LV2, glm::vec2(0 / 16.f, 1 / 11.f));
	sprite->addKeyframe(JUMP_RIGHT_LV2, glm::vec2(1 / 11.f, 1 / 11.f));
	sprite->addKeyframe(JUMP_RIGHT_LV2, glm::vec2(2 / 11.f, 1 / 11.f));
	sprite->addKeyframe(JUMP_RIGHT_LV2, glm::vec2(3 / 11.f, 1 / 11.f));

	sprite->setAnimationSpeed(JUMP_LEFT_LV2, 8);
	sprite->addKeyframe(JUMP_LEFT_LV2, glm::vec2(7 / 11.f, 1 / 11.f));
	sprite->addKeyframe(JUMP_LEFT_LV2, glm::vec2(6 / 11.f, 1 / 11.f));
	sprite->addKeyframe(JUMP_LEFT_LV2, glm::vec2(5 / 11.f, 1 / 11.f));
	sprite->addKeyframe(JUMP_LEFT_LV2, glm::vec2(4 / 11.f, 1 / 11.f));

	sprite->setAnimationSpeed(DIE_RIGHT_LV2, 6);
	sprite->addKeyframe(DIE_RIGHT_LV2, glm::vec2(3 / 11.f, 2 / 11.f));
	sprite->addKeyframe(DIE_RIGHT_LV2, glm::vec2(2 / 11.f, 2 / 11.f));
	sprite->addKeyframe(DIE_RIGHT_LV2, glm::vec2(1 / 11.f, 2 / 11.f));
	sprite->addKeyframe(DIE_RIGHT_LV2, glm::vec2(0 / 11.f, 2 / 11.f));
	sprite->addKeyframe(DIE_RIGHT_LV2, glm::vec2(4 / 11.f, 2 / 11.f));
	sprite->addKeyframe(DIE_RIGHT_LV2, glm::vec2(4 / 11.f, 2 / 11.f));
	sprite->addKeyframe(DIE_RIGHT_LV2, glm::vec2(4 / 11.f, 2 / 11.f));

	sprite->setAnimationSpeed(DIE_LEFT_LV2, 6);
	sprite->addKeyframe(DIE_LEFT_LV2, glm::vec2(6 / 11.f, 2 / 11.f));
	sprite->addKeyframe(DIE_LEFT_LV2, glm::vec2(7 / 11.f, 2 / 11.f));
	sprite->addKeyframe(DIE_LEFT_LV2, glm::vec2(8 / 11.f, 2 / 11.f));
	sprite->addKeyframe(DIE_LEFT_LV2, glm::vec2(9 / 11.f, 2 / 11.f));
	sprite->addKeyframe(DIE_LEFT_LV2, glm::vec2(5 / 11.f, 2 / 11.f));
	sprite->addKeyframe(DIE_LEFT_LV2, glm::vec2(5 / 11.f, 2 / 11.f));
	sprite->addKeyframe(DIE_LEFT_LV2, glm::vec2(5 / 11.f, 2 / 11.f));

	sprite->changeAnimation(0);
	//tileMapDispl = tileMapPos;
	//sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

void Player::updateLv2(int deltaTime, bool canMoveForward) 
{
	sprite->update(deltaTime);
	angle_aux += 45;
	if (angle_aux == 360) angle_aux = 0;
	if (!F && !reviving && (BulletManager::instance().existsBulletColision(glm::vec2(posPlayer.x, posPlayer.y), 32, 90, "PLAYER"))) {
		F = true;
		reviving = true;
		RestLifes -= 1;
		DieSec = Time::instance().NowToMili();
		posPlayer.y = 288;
		sprite->update(deltaTime);
	}
	if (F && reviving) {
		if (PlayerDir == "R") {
			if (sprite->animation() != DIE_RIGHT_LV2) {
				sprite->changeAnimation(DIE_RIGHT_LV2);
			}
		}
		else {
			if (sprite->animation() != DIE_LEFT_LV2) {
				sprite->changeAnimation(DIE_LEFT_LV2);
			}
		}
		if (Time::instance().NowToMili() - DieSec > 1000) {
			if (rand() % 2 == 0) posPlayer.x -= 70;
			else posPlayer.x += 70;
			PlayerState = standing;
			F = false;
		}
	}
	if (!F) {
		if (Time::instance().NowToMili() - DieSec > 3000) reviving = false;
		if (Game::instance().getKey('z') && !hasShoot) {
			hasShoot = true;
			int speed = 4;
			vector<glm::vec2> dir;
			//dir.push_back(glm::ivec2(1.5f,- 1.f));
			dir.push_back(glm::ivec2(0, -1.f));
			vector<glm::vec2> pos;
			pos.push_back(glm::ivec2(posPlayer.x, posPlayer.y - 30));
			BulletManager::instance().fire(dir, pos, speed, "CHARACTER");
			SoundSystem::instance().playSoundEffect("level01", "SHOOT", "CHARACTER");
		}
		if (hasShoot) ++count;
		if (count > 25) {
			count = 0;
			hasShoot = false;
		}
		// first we need to check if its moving an jumping, it shoud go before checking if its moving left or right
		if (PlayerState == standing || PlayerState == running || PlayerState == laying) {
			if (canMoveForward && Game::instance().getSpecialKey(GLUT_KEY_UP)) {
				if (sprite->animation() != MOVE_UP_LV2) sprite->changeAnimation(MOVE_UP_LV2);
			}
			else if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT)) {
				if (sprite->animation() != MOVE_RIGHT_LV2) {
					sprite->changeAnimation(MOVE_RIGHT_LV2);
				}
				PlayerState = running;
				PlayerDir = "R";
				if (posPlayer.x < 476) posPlayer.x += 2;
				else posPlayer.x = 476;
				setPositionLv2(glm::vec2(posPlayer.x, 9 * 32));
			}
			else if (Game::instance().getSpecialKey(GLUT_KEY_LEFT)) {
				if (sprite->animation() != MOVE_LEFT_LV2) {
					sprite->changeAnimation(MOVE_LEFT_LV2);
				}
				PlayerState = running;
				PlayerDir = "L";
				if (posPlayer.x > 64) posPlayer.x -= 2;
				else posPlayer.x = 64;
				setPositionLv2(glm::vec2(posPlayer.x, 9 * 32));
			}
			else {
				if (sprite->animation() != STAND_LV2) {
					sprite->changeAnimation(STAND_LV2);
					PlayerState = STAND_LV2;
					setPositionLv2(glm::vec2(posPlayer.x, 9 * 32));
				}
			}
		}
		if (PlayerState == jumping) {
			jumpAngle += JUMP_ANGLE_STEP;
			if (jumpAngle == 180) {
				PlayerState = standing;
				posPlayer.y = startY;
			}
			else {
				posPlayer.y = int(startY - 96 * sin(3.14159f * jumpAngle / 180.f));
			}
			if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT)) {
				if (posPlayer.x < 494) posPlayer.x += 2;
				else PlayerState = standing;
			}
			else if (Game::instance().getSpecialKey(GLUT_KEY_LEFT)) {
				if (posPlayer.x > 64) posPlayer.x -= 2;
				else PlayerState = standing;
			}
			sprite->setPosition(glm::vec2(float(posPlayer.x), float(posPlayer.y)));
		}
		else
		{
			posPlayer.y += FALL_STEP;
			if (map->collisionMoveDownLv2(posPlayer, canMoveForward, &posPlayer.y)) {
				if (Game::instance().getKey(VK_SPACE) && PlayerState != laying) {
					startY = posPlayer.y;
					jumpAngle = 0;
					PlayerState = jumping;
					if (PlayerDir == "L") {
						if (sprite->animation() != JUMP_LEFT_LV2) sprite->changeAnimation(JUMP_LEFT_LV2);
					}
					else {
						if (sprite->animation() != JUMP_RIGHT_LV2) sprite->changeAnimation(JUMP_RIGHT_LV2);
					}
				}
			}
		}
	}
}

void Player::render()
{
	if (reviving) {
		float x = sin(3.14159f * angle_aux / 180.f);
		if (x >= 0.0f) sprite->render();
	}
	else sprite->render();
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

void Player::setPositionLv2(const glm::vec2 &pos)
{
	posPlayer = pos;
	sprite->setPosition(glm::vec2(float(posPlayer.x), float(posPlayer.y)));
}

glm::ivec2 Player::getPosition()
{
	return posPlayer;
}

int Player::getLifes()
{
 	return RestLifes;
}

bool Player::getPower()
{
	return powerup;
}



