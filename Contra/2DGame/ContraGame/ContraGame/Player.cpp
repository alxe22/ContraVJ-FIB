#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Player.h"
#include "Game.h"
#include "BulletManager.h"
#include "Time.h"
#include "SoundSystem.h"


#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 96
#define FALL_STEP 4


enum PlayerAnims
{
	STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT, MOVESH_LEFT, MOVESH_RIGHT, JUMP_LEFT, JUMP_RIGHT, LAY_LEFT, LAY_RIGHT, UP_LEFT, UP_RIGHT, DIE_LEFT, DIE_RIGHT, MOVEU45_LEFT, MOVEU45_RIGHT, MOVED45_LEFT, MOVED45_RIGHT
};

enum PlayerStates
{
	standing, running, laying, up, running_up, running_down, jumping
};


void Player::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	PlayerState = standing;
	PlayerDir = "R";
	RestLifes = 3;
	spritesheet.loadFromFile("images/soldado.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(96, 96), glm::vec2(1/11.f, 1/11.f), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(18);
	
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
		

	sprite->changeAnimation(1);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	
}

void Player::update(int deltaTime)
{
	sprite->update(deltaTime);
	if (Game::instance().getKey('z')) {
		int speed = 4;
		vector<glm::vec2> dir;
		//dir.push_back(glm::ivec2(1.5f,- 1.f));
		dir.push_back(glm::ivec2(-1, 0));
		vector<glm::vec2> pos;
		pos.push_back(glm::ivec2(posPlayer.x + 32, posPlayer.y + 30));
		BulletManager::instance().fire(dir, pos, speed, "CHARACTER");
		char *msgbuf = (char *)malloc(sizeof(char) * (300 + 1));
		sprintf(msgbuf, "Called soundSystemEffect \n");
		OutputDebugStringA(msgbuf);
		SoundSystem::instance().playSoundEffect("level01", "SHOOT", "CHARACTER");
	}
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
		else if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT))
		{
			if (sprite->animation() != MOVE_RIGHT)
				sprite->changeAnimation(MOVE_RIGHT);
			PlayerState = running;
			PlayerDir = "R";
			posPlayer.x += 2;
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
		else if (Game::instance().getSpecialKey(GLUT_KEY_LEFT))
		{
			if (sprite->animation() != MOVE_LEFT)
				sprite->changeAnimation(MOVE_LEFT);
			PlayerState = running;
			PlayerDir = "L";
			posPlayer.x -= 2;
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
			posPlayer.y = int(startY - 96 * sin(3.14159f * jumpAngle / 180.f));
		}
		if(Game::instance().getSpecialKey(GLUT_KEY_RIGHT)) posPlayer.x += 2;
		else if (Game::instance().getSpecialKey(GLUT_KEY_LEFT)) posPlayer.x -= 2;
		
	}
	else
	{
		posPlayer.y += FALL_STEP;
		if (map->collisionMoveDown(posPlayer, glm::ivec2(64, 96), &posPlayer.y)) {
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
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

enum PlayerAnimslv2
{
	STAND_LV2, LAY_LV2, MOVE_LEFT_LV2, MOVE_RIGHT_LV2, MOVE_UP_LV2, JUMP_RIGHT_LV2, JUMP_LEFT_LV2
};
void Player::initlevel2(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	PlayerState = standing;
	PlayerDir = "R";
	spritesheet.loadFromFile("images/soldado.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(96, 96), glm::vec2(1 / 11.f, 1 / 11.f), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(7);

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

	sprite->changeAnimation(0);
	//tileMapDispl = tileMapPos;
	//sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

void Player::updateLv2(int deltaTime, bool canMoveForward) 
{
	sprite->update(deltaTime);
	// first we need to check if its moving an jumping, it shoud go before checking if its moving left or right
	if (PlayerState == standing || PlayerState == running || PlayerState == laying) {
		if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT)) {
			if (sprite->animation() != MOVE_RIGHT_LV2) {
				sprite->changeAnimation(MOVE_RIGHT_LV2);
			}
			PlayerState = running;
			PlayerDir = "R";
			if (posPlayer.x < 494) posPlayer.x += 2;
			setPositionLv2(glm::vec2(posPlayer.x, 9 * 32));
		}
		else if (Game::instance().getSpecialKey(GLUT_KEY_LEFT)) {
			if (sprite->animation() != MOVE_LEFT_LV2) {
				sprite->changeAnimation(MOVE_LEFT_LV2);
			}
			PlayerState = running;
			PlayerDir = "L";
			if (posPlayer.x > 64) posPlayer.x -= 2;
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



