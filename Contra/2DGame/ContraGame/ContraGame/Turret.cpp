#include "Turret.h"
#include "BulletManager.h"
#include "Time.h"
#include <math.h>

#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 96
#define FALL_STEP 4
#define IN_RANGE 20

#define FIRE_FRAME_INTERVAL 1000

enum PlayerAnims
{
	DEGREE_0, DEGREE_30, DEGREE_50, DEGREE_90, DEGREE_120, DEGREE_140, DEGREE_180, DEGREE_210,
	DEGREE_230, DEGREE_270, DEGREE_300, DEGREE_320
};

void Turret::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	bJumping = false;
	spritesheet.loadFromFile("images/turret2.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(64, 64), glm::vec2(0.111111111111111f, 0.25f), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(12);

	sprite->setAnimationSpeed(DEGREE_0, 8);
	sprite->addKeyframe(DEGREE_0, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(DEGREE_0, glm::vec2(0.11f, 0.f));
	sprite->addKeyframe(DEGREE_0, glm::vec2(0.22f, 0.f));

	sprite->setAnimationSpeed(DEGREE_30, 8);
	sprite->addKeyframe(DEGREE_30, glm::vec2(0.66f, 0.75f));
	sprite->addKeyframe(DEGREE_30, glm::vec2(0.77f, 0.75f));
	sprite->addKeyframe(DEGREE_30, glm::vec2(0.88f, 0.75f));

	sprite->setAnimationSpeed(DEGREE_50, 8);
	sprite->addKeyframe(DEGREE_50, glm::vec2(0.33f, 0.75f));
	sprite->addKeyframe(DEGREE_50, glm::vec2(0.44f, 0.75f));
	sprite->addKeyframe(DEGREE_50, glm::vec2(0.55f, 0.75f));

	sprite->setAnimationSpeed(DEGREE_90, 8);
	sprite->addKeyframe(DEGREE_90, glm::vec2(0.f, 0.75f));
	sprite->addKeyframe(DEGREE_90, glm::vec2(0.11f, 0.75f));
	sprite->addKeyframe(DEGREE_90, glm::vec2(0.22f, 0.75f));

	sprite->setAnimationSpeed(DEGREE_120, 8);
	sprite->addKeyframe(DEGREE_120, glm::vec2(0.66f, 0.5f));
	sprite->addKeyframe(DEGREE_120, glm::vec2(0.77f, 0.5f));
	sprite->addKeyframe(DEGREE_120, glm::vec2(0.88f, 0.5f));

	sprite->setAnimationSpeed(DEGREE_140, 8);
	sprite->addKeyframe(DEGREE_140, glm::vec2(0.33f, 0.5f));
	sprite->addKeyframe(DEGREE_140, glm::vec2(0.44f, 0.5f));
	sprite->addKeyframe(DEGREE_140, glm::vec2(0.55f, 0.5f));

	sprite->setAnimationSpeed(DEGREE_180, 8);
	sprite->addKeyframe(DEGREE_180, glm::vec2(0.f, 0.5f));
	sprite->addKeyframe(DEGREE_180, glm::vec2(0.11f, 0.5f));
	sprite->addKeyframe(DEGREE_180, glm::vec2(0.22f, 0.5f));

	sprite->setAnimationSpeed(DEGREE_210, 8);
	sprite->addKeyframe(DEGREE_210, glm::vec2(0.66f, 0.25f));
	sprite->addKeyframe(DEGREE_210, glm::vec2(0.77f, 0.25f));
	sprite->addKeyframe(DEGREE_210, glm::vec2(0.88f, 0.25f));

	sprite->setAnimationSpeed(DEGREE_230, 8);
	sprite->addKeyframe(DEGREE_230, glm::vec2(0.33f, 0.25f));
	sprite->addKeyframe(DEGREE_230, glm::vec2(0.44f, 0.25f));
	sprite->addKeyframe(DEGREE_230, glm::vec2(0.55f, 0.25f));

	sprite->setAnimationSpeed(DEGREE_270, 8);
	sprite->addKeyframe(DEGREE_270, glm::vec2(0.f, 0.25f));
	sprite->addKeyframe(DEGREE_270, glm::vec2(0.11f, 0.25f));
	sprite->addKeyframe(DEGREE_270, glm::vec2(0.22f, 0.25f));

	sprite->setAnimationSpeed(DEGREE_300, 8);
	sprite->addKeyframe(DEGREE_300, glm::vec2(0.66f, 0.f));
	sprite->addKeyframe(DEGREE_300, glm::vec2(0.77f, 0.f));
	sprite->addKeyframe(DEGREE_300, glm::vec2(0.88f, 0.f));

	sprite->setAnimationSpeed(DEGREE_320, 8);
	sprite->addKeyframe(DEGREE_320, glm::vec2(0.33f, 0.f));
	sprite->addKeyframe(DEGREE_320, glm::vec2(0.44f, 0.f));
	sprite->addKeyframe(DEGREE_320, glm::vec2(0.55f, 0.f));


	sprite->changeAnimation(6);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

void Turret::decideFire(int playerAnim)
{
	long long diff = Time::instance().NowToMili() - lastSecondFired;
	if (diff > FIRE_FRAME_INTERVAL) {
		lastSecondFired = Time::instance().NowToMili();
		vector<glm::vec2> dir;
		vector<glm::vec2> pos;
		int speed = 2;
		switch (playerAnim) {
		case PlayerAnims::DEGREE_0:
			dir.push_back(glm::vec2(1.f, 0.f));
			pos.push_back(glm::vec2(posPlayer.x + 48, posPlayer.y + 16));
			break;
		case PlayerAnims::DEGREE_30:
			dir.push_back(glm::vec2(1.f, -0.7f));
			pos.push_back(glm::vec2(posPlayer.x + 50, posPlayer.y + 5));
			break;
		case PlayerAnims::DEGREE_50:
			speed = 4;
			dir.push_back(glm::vec2(0.3f, -0.5f));
			pos.push_back(glm::vec2(posPlayer.x + 27, posPlayer.y - 7));
			break;
		case PlayerAnims::DEGREE_90:
			dir.push_back(glm::vec2(0.f, -1.f));
			pos.push_back(glm::vec2(posPlayer.x + 16, posPlayer.y - 5));
			break;
		case PlayerAnims::DEGREE_120:
			speed = 4;
			dir.push_back(glm::vec2(-0.3f, -0.5f));
			pos.push_back(glm::vec2(posPlayer.x + 8, posPlayer.y - 10));
			break;
		case PlayerAnims::DEGREE_140:
			dir.push_back(glm::vec2(-1.f, -0.7f));
			pos.push_back(glm::vec2(posPlayer.x - 16, posPlayer.y + 3));
			break;
		case PlayerAnims::DEGREE_180:
			dir.push_back(glm::vec2(-1.f, 0.f));
			pos.push_back(glm::vec2(posPlayer.x - 5, posPlayer.y + 16));
			break;
		case PlayerAnims::DEGREE_210:
			dir.push_back(glm::vec2(-1.f, 0.6f));
			pos.push_back(glm::vec2(posPlayer.x - 16, posPlayer.y + 29));
			break;
		case PlayerAnims::DEGREE_230:
			speed = 4;
			dir.push_back(glm::vec2(-0.3f, 0.5f));
			pos.push_back(glm::vec2(posPlayer.x + 10, posPlayer.y + 40));
			break;
		case PlayerAnims::DEGREE_270:
			dir.push_back(glm::vec2(0.f, 1.f));
			pos.push_back(glm::vec2(posPlayer.x + 16, posPlayer.y + 37));
			break;
		case PlayerAnims::DEGREE_300:
			speed = 4;
			dir.push_back(glm::vec2(0.3f, 0.5f));
			pos.push_back(glm::vec2(posPlayer.x + 27, posPlayer.y + 40));
			break;
		case PlayerAnims::DEGREE_320:
			dir.push_back(glm::vec2(1.f, 0.6f));
			pos.push_back(glm::vec2(posPlayer.x + 37, posPlayer.y + 33));
			break;
		}
		BulletManager::instance().fire(dir, pos, speed, "ENEMY");
		SoundSystem::instance().playSoundEffect("level01", "SHOOT", "TURRET");
	}
}

void Turret::update(glm::ivec2 &posPlayer1, glm::ivec2 &posPlayer2, int deltaTime)
{
	sprite->update(deltaTime);
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	if ((posPlayer1.x - posPlayer.x >= -310 && posPlayer1.x - posPlayer.x < 0) ||
		(posPlayer1.x - posPlayer.x >= 0 && posPlayer1.x - posPlayer.x < 310)) {
		// turn left
		if ((posPlayer1.x - posPlayer.x >= -310 && posPlayer1.x - posPlayer.x < 0)) {
			if (posPlayer1.y - posPlayer.y < 0 && ((posPlayer1.x - posPlayer.x > -30) && (posPlayer1.x - posPlayer.x < 0))) {
				sprite->changeAnimation(DEGREE_90);
				decideFire(sprite->animation());
			}
			else if (posPlayer1.y - posPlayer.y < 0 && posPlayer1.x - posPlayer.x >= -55) {
				sprite->changeAnimation(DEGREE_120);
				decideFire(sprite->animation());
			}
			else if (posPlayer1.y - posPlayer.y < 0 && posPlayer1.x - posPlayer.x >= -120) {
				sprite->changeAnimation(DEGREE_140);
				decideFire(sprite->animation());
			}
			else if (posPlayer1.y - posPlayer.y > 0 && posPlayer1.y - posPlayer.y <= 85) {
				sprite->changeAnimation(DEGREE_180);
				decideFire(sprite->animation());
			}
			else if (posPlayer1.y - posPlayer.y > 0 && posPlayer1.x - posPlayer.x <= -55) {
				sprite->changeAnimation(DEGREE_210);
				decideFire(sprite->animation());
			}
			else if (posPlayer1.y - posPlayer.y > 0 && posPlayer1.x - posPlayer.x <= -30) {
				sprite->changeAnimation(DEGREE_230);
				decideFire(sprite->animation());
			}
			else if (posPlayer1.y - posPlayer.y > 20 && ((posPlayer1.x - posPlayer.x > -30) && (posPlayer1.x - posPlayer.x < 0))) {
				sprite->changeAnimation(DEGREE_270);
				decideFire(sprite->animation());
			}
		}
		//turn right
		else {
			if (posPlayer1.y - posPlayer.y < 0 && ((posPlayer1.x - posPlayer.x >= 0) && (posPlayer1.x - posPlayer.x < 64))) {
				sprite->changeAnimation(DEGREE_90);
				decideFire(sprite->animation());
			}
			else if (posPlayer1.y - posPlayer.y > 20 && ((posPlayer1.x - posPlayer.x >= 0) && (posPlayer1.x - posPlayer.x <= 20))) {
				sprite->changeAnimation(DEGREE_270);
				decideFire(sprite->animation());
			}
			else if (posPlayer1.y - posPlayer.y > 20 && posPlayer1.x - posPlayer.x <= 100) {
				sprite->changeAnimation(DEGREE_300);
				decideFire(sprite->animation());
			}
			else if (posPlayer1.y - posPlayer.y > 85 && posPlayer1.y - posPlayer.y <= 140) {
				sprite->changeAnimation(DEGREE_320);
				decideFire(sprite->animation());
			}
			else if ((posPlayer1.y - posPlayer.y > 20 && ((posPlayer1.x - posPlayer.x >= 0) && (posPlayer1.x - posPlayer.x < 64)))) {
				sprite->changeAnimation(DEGREE_270);
				decideFire(sprite->animation());
			}
			else if (posPlayer1.y - posPlayer.y < 0 && posPlayer1.x - posPlayer.x >= 128) {
				sprite->changeAnimation(DEGREE_30);
				decideFire(sprite->animation());
			}
			else if (posPlayer1.y - posPlayer.y < 0 && posPlayer1.x - posPlayer.x >= 64)  {
				sprite->changeAnimation(DEGREE_50);
				decideFire(sprite->animation());
			}
			else {
				sprite->changeAnimation(DEGREE_0);
				decideFire(sprite->animation());
			}
		}
	}
}

void Turret::render()
{
	sprite->render();
}

void Turret::setTileMap(TileMap *tileMap)
{
	map = tileMap;
}

void Turret::setPosition(const glm::vec2 &pos)
{
	posPlayer = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

glm::ivec2 Turret::getPosition()
{
	return posPlayer;
}

glm::ivec2 Turret::getSize()
{
	return glm::ivec2(64, 64);
}

glm::ivec2 Turret::getTopLeftPos()
{
	return posPlayer;
}

string Turret::type()
{
	return "TURRET";
}


