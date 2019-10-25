#include "Sniper.h"
#include "BulletManager.h"
#include "Time.h"
#include "SoundSystem.h"

#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 96
#define FALL_STEP 4
#define IN_RANGE 20
#define FIRE_FRAME_INTERVAL 1000

#define FIRE_OFFSET_X_ANIM_UP_LEFT 14
#define FIRE_OFFSET_Y_ANIM_UP_LEFT 24

#define FIRE_OFFSET_X_ANIM_UP_RIGHT 45
#define FIRE_OFFSET_Y_ANIM_UP_RIGHT 24

#define FIRE_OFFSET_X_ANIM_FRONT_LEFT 14
#define FIRE_OFFSET_Y_ANIM_FRONT_LEFT 55

#define FIRE_OFFSET_X_ANIM_FRONT_RIGHT 50
#define FIRE_OFFSET_Y_ANIM_FRONT_RIGHT 55

#define FIRE_OFFSET_X_ANIM_FIRE_WATER_LEFT 30
#define FIRE_OFFSET_Y_ANIM_FIRE_WATER_LEFT 93

#define FIRE_OFFSET_X_ANIM_FIRE_WATER_RIGHT 60
#define FIRE_OFFSET_Y_ANIM_FIRE_WATER_RIGHT 93

using namespace std;

enum PlayerAnims
{
	FRONT_LEFT, FIRE_FRONT_LEFT, FRONT_RIGHT, FIRE_FRONT_RIGHT,
	UP_LEFT, FIRE_UP_LEFT, UP_RIGHT, FIRE_UP_RIGHT,
	DOWN_LEFT, DOWN_RIGHT,
	WATER_LEFT, FIRE_WATER_LEFT, WATER_RIGHT, FIRE_WATER_RIGHT
};

void Sniper::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	spritesheet.loadFromFile("images/sniper.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(64, 128), glm::vec2(0.25f, 0.25f), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(14);

	sprite->setAnimationSpeed(FRONT_LEFT, 8);
	sprite->addKeyframe(FRONT_LEFT, glm::vec2(0.f, 0.f));

	sprite->setAnimationSpeed(FIRE_FRONT_LEFT, 8);
	sprite->addKeyframe(FIRE_FRONT_LEFT, glm::vec2(0.25f, 0.f));

	sprite->setAnimationSpeed(UP_LEFT, 8);
	sprite->addKeyframe(UP_LEFT, glm::vec2(0.5f, 0.f));

	sprite->setAnimationSpeed(FIRE_UP_LEFT, 8);
	sprite->addKeyframe(FIRE_UP_LEFT, glm::vec2(0.75f, 0.f));



	sprite->setAnimationSpeed(FRONT_RIGHT, 8);
	sprite->addKeyframe(FRONT_RIGHT, glm::vec2(0.75f, 0.25f));

	sprite->setAnimationSpeed(FIRE_FRONT_RIGHT, 8);
	sprite->addKeyframe(FIRE_FRONT_RIGHT, glm::vec2(0.5f, 0.25f));

	sprite->setAnimationSpeed(UP_RIGHT, 8);
	sprite->addKeyframe(UP_RIGHT, glm::vec2(0.25f, 0.25f));

	sprite->setAnimationSpeed(FIRE_UP_RIGHT, 8);
	sprite->addKeyframe(FIRE_UP_RIGHT, glm::vec2(0.f, 0.25f));



	sprite->setAnimationSpeed(DOWN_LEFT, 8);
	sprite->addKeyframe(DOWN_LEFT, glm::vec2(0.f, 0.5f));

	sprite->setAnimationSpeed(DOWN_RIGHT, 8);
	sprite->addKeyframe(DOWN_RIGHT, glm::vec2(0.75f, 0.25f));



	sprite->setAnimationSpeed(WATER_LEFT, 8);
	sprite->addKeyframe(WATER_LEFT, glm::vec2(0.25f, 0.5f));

	sprite->setAnimationSpeed(FIRE_WATER_LEFT, 8);
	sprite->addKeyframe(FIRE_WATER_LEFT, glm::vec2(0.5f, 0.5f));

	sprite->setAnimationSpeed(WATER_RIGHT, 8);
	sprite->addKeyframe(WATER_RIGHT, glm::vec2(0.f, 0.75f));

	sprite->setAnimationSpeed(FIRE_WATER_RIGHT, 8);
	sprite->addKeyframe(FIRE_WATER_RIGHT, glm::vec2(0.75f, 0.5f));


	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

void Sniper::decideFire(int playerAnim)
{
	long long diff = Time::instance().NowToMili() - lastSecondFired;
	if (diff > FIRE_FRAME_INTERVAL) {
		lastSecondFired = Time::instance().NowToMili();
		vector<glm::vec2> dir;
		vector<glm::vec2> pos;
		int speed = 4;
		switch (playerAnim) {
		case PlayerAnims::UP_LEFT:
			dir.push_back(glm::vec2(-1.f, -0.75f));
			pos.push_back(glm::vec2(posPlayer.x - FIRE_OFFSET_X_ANIM_UP_LEFT, posPlayer.y + FIRE_OFFSET_Y_ANIM_UP_LEFT));
			break;
		case PlayerAnims::UP_RIGHT:
			dir.push_back(glm::vec2(1.f, -0.75f));
			pos.push_back(glm::vec2(posPlayer.x + FIRE_OFFSET_X_ANIM_UP_RIGHT, posPlayer.y + FIRE_OFFSET_Y_ANIM_UP_RIGHT));
			break;
		case PlayerAnims::FRONT_LEFT:
			dir.push_back(glm::vec2(-1.f, 0.f));
			pos.push_back(glm::vec2(posPlayer.x - FIRE_OFFSET_X_ANIM_FRONT_LEFT, posPlayer.y + FIRE_OFFSET_Y_ANIM_FRONT_LEFT));
			break;
		case PlayerAnims::FRONT_RIGHT:
			dir.push_back(glm::vec2(1.f, 0.f));
			pos.push_back(glm::vec2(posPlayer.x + FIRE_OFFSET_X_ANIM_FRONT_RIGHT, posPlayer.y + FIRE_OFFSET_Y_ANIM_FRONT_RIGHT));
			break;
		case PlayerAnims::FIRE_WATER_LEFT:
			dir.push_back(glm::vec2(-1.f, 0.f));
			pos.push_back(glm::vec2(posPlayer.x - FIRE_OFFSET_X_ANIM_FIRE_WATER_LEFT, posPlayer.y + FIRE_OFFSET_Y_ANIM_FIRE_WATER_LEFT));
			break;
		case PlayerAnims::FIRE_WATER_RIGHT:
			dir.push_back(glm::vec2(1.f, 0.f));
			pos.push_back(glm::vec2(posPlayer.x + FIRE_OFFSET_X_ANIM_FIRE_WATER_RIGHT, posPlayer.y + FIRE_OFFSET_Y_ANIM_FIRE_WATER_RIGHT));
			break;
		}
		BulletManager::instance().fire(dir, pos, speed, "ENEMY");
		SoundSystem::instance().playSoundEffect("level01", "SHOOT", "SNIPER");
	}
}

void Sniper::update(glm::ivec2 &posPlayer1, glm::ivec2 &posPlayer2, int deltaTime)
{
	sprite->update(deltaTime);
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));

	if (Game::instance().getKey('q')) sprite->changeAnimation(1);
	if (Game::instance().getKey('w')) sprite->changeAnimation(2);
	if (Game::instance().getKey('e')) sprite->changeAnimation(3);
	if (Game::instance().getKey('r')) sprite->changeAnimation(4);
	if (Game::instance().getKey('t')) sprite->changeAnimation(5);
	if (Game::instance().getKey('y')) sprite->changeAnimation(6);
	if (Game::instance().getKey('u')) sprite->changeAnimation(7);
	if (Game::instance().getKey('i')) sprite->changeAnimation(8);
	if (Game::instance().getKey('o')) sprite->changeAnimation(9);
	if (Game::instance().getKey('p')) sprite->changeAnimation(10);
	if (Game::instance().getKey('a')) sprite->changeAnimation(11);
	if (Game::instance().getKey('s')) sprite->changeAnimation(12);
	if (Game::instance().getKey('d')) sprite->changeAnimation(13);

	if ((posPlayer1.x - posPlayer.x >= -310 && posPlayer1.x - posPlayer.x < 0) || 
		(posPlayer1.x - posPlayer.x > 0 && posPlayer1.x - posPlayer.x < 310)) {
		// turn left
		if ((posPlayer1.x - posPlayer.x >= -310 && posPlayer1.x - posPlayer.x < 0)) {
			if (sprite->animation() == WATER_RIGHT || sprite->animation() == FIRE_WATER_RIGHT) 
				sprite->changeAnimation(WATER_LEFT);
			else if (sprite->animation() == WATER_LEFT || sprite->animation() == FIRE_WATER_LEFT) {
				if (sprite->animation() != FIRE_WATER_LEFT) sprite->changeAnimation(FIRE_WATER_LEFT);
				decideFire(FIRE_WATER_LEFT);
			}
			else if (posPlayer1.y < posPlayer.y) {
				if (sprite->animation() != UP_LEFT)
					sprite->changeAnimation(UP_LEFT);
				else if (posPlayer1.x - posPlayer.x > -220 && posPlayer1.x - posPlayer.x < -120) decideFire(UP_LEFT);
			}
			else if (sprite->animation() != FRONT_LEFT) sprite->changeAnimation(FRONT_LEFT);
			else decideFire(FRONT_LEFT);
		}
		//turn right
		else {
			if (sprite->animation() == WATER_LEFT || sprite->animation() == FIRE_WATER_LEFT &&
				(sprite->animation() != WATER_RIGHT || sprite->animation() != FIRE_WATER_RIGHT)) sprite->changeAnimation(WATER_RIGHT);
			else if (sprite->animation() == WATER_RIGHT || sprite->animation() == FIRE_WATER_RIGHT) {
				if (sprite->animation() != FIRE_WATER_RIGHT) sprite->changeAnimation(FIRE_WATER_RIGHT);
				decideFire(FIRE_WATER_RIGHT);
			}
			else if (posPlayer1.y < posPlayer.y) {
				if (sprite->animation() != UP_RIGHT) sprite->changeAnimation(UP_RIGHT);
				else if (posPlayer1.x - posPlayer.x > 120 && posPlayer1.x - posPlayer.x < 220) decideFire(UP_RIGHT);
			}
			else if (sprite->animation() != FRONT_RIGHT) sprite->changeAnimation(FRONT_RIGHT);
			else decideFire(FRONT_RIGHT);
		}
		
	}
}

void Sniper::render()
{
	sprite->render();
}

void Sniper::setTileMap(TileMap *tileMap)
{
	map = tileMap;
}

void Sniper::setPosition(const glm::vec2 &pos)
{
	posPlayer = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

void Sniper::setAnimation(int animNum) 
{
	sprite->changeAnimation(animNum);
}

glm::ivec2 Sniper::getPosition()
{
	return posPlayer;
}

glm::ivec2 Sniper::getSize()
{
	return glm::ivec2(64, 92);
}

glm::ivec2 Sniper::getTopLeftPos()
{
	return glm::ivec2(posPlayer.x, posPlayer.y + 64);
}

string Sniper::type()
{
	return "SNIPER";
}


