#include "SuperTurret.h"
#include "Time.h"
#include "BulletManager.h"

#define FIRE_FRAME_INTERVAL 1000

#define FIRE_OFFSET_X_ANIM_DEGREE_120 30
#define FIRE_OFFSET_Y_ANIM_DEGREE_120 15

#define FIRE_OFFSET_X_ANIM_DEGREE_140 0
#define FIRE_OFFSET_Y_ANIM_DEGREE_140 15

#define FIRE_OFFSET_X_ANIM_DEGREE_180 0
#define FIRE_OFFSET_Y_ANIM_DEGREE_180 45

enum PlayerAnims
{
	DEGREE_120, DEGREE_140, DEGREE_180
};

void SuperTurret::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	bJumping = false;
	spritesheet.loadFromFile("images/superTurret.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(128, 128), glm::vec2(0.25f, 0.3333333333333333f), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(3);

	sprite->setAnimationSpeed(DEGREE_120, 8);
	sprite->addKeyframe(DEGREE_120, glm::vec2(0.5f, 0.3333333333333333f));
	sprite->addKeyframe(DEGREE_120, glm::vec2(0.75f, 0.3333333333333333f));
	sprite->addKeyframe(DEGREE_120, glm::vec2(0.f, 0.6666666666666666f));

	sprite->setAnimationSpeed(DEGREE_140, 8);
	sprite->addKeyframe(DEGREE_140, glm::vec2(0.75f, 0.f));
	sprite->addKeyframe(DEGREE_140, glm::vec2(0.f, 0.3333333333333333f));
	sprite->addKeyframe(DEGREE_140, glm::vec2(0.25f, 0.3333333333333333f));

	sprite->setAnimationSpeed(DEGREE_180, 8);
	sprite->addKeyframe(DEGREE_180, glm::vec2(0.0f, 0.f));
	sprite->addKeyframe(DEGREE_180, glm::vec2(0.25f, 0.f));
	sprite->addKeyframe(DEGREE_180, glm::vec2(0.5f, 0.f));

	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

void SuperTurret::decideFire(int playerAnim)
{
	long long diff = Time::instance().NowToMili() - lastSecondFired;
	if (diff > FIRE_FRAME_INTERVAL) {
		lastSecondFired = Time::instance().NowToMili();
		vector<glm::vec2> dir;
		vector<glm::vec2> pos;
		int speed = 2;
		switch (playerAnim) {
		case PlayerAnims::DEGREE_120:
			dir.push_back(glm::vec2(-0.75f, -0.75f));
			pos.push_back(glm::vec2(posPlayer.x + FIRE_OFFSET_X_ANIM_DEGREE_120, posPlayer.y + FIRE_OFFSET_Y_ANIM_DEGREE_120));
			break;
		case PlayerAnims::DEGREE_140:
			speed = 5;
			dir.push_back(glm::vec2(-0.3f, -0.3f));
			pos.push_back(glm::vec2(posPlayer.x + FIRE_OFFSET_X_ANIM_DEGREE_140, posPlayer.y + FIRE_OFFSET_Y_ANIM_DEGREE_140));
			break;
		case PlayerAnims::DEGREE_180:
			dir.push_back(glm::vec2(-1.f, 0.f));
			pos.push_back(glm::vec2(posPlayer.x + FIRE_OFFSET_X_ANIM_DEGREE_180, posPlayer.y + FIRE_OFFSET_Y_ANIM_DEGREE_180));
			break;
		}
		BulletManager::instance().fire(dir, pos, speed);
	}
}

void SuperTurret::update(glm::ivec2 &posPlayer1, glm::ivec2 &posPlayer2, int deltaTime)
{
	sprite->update(deltaTime);
	// turn left
	if ((posPlayer1.x - posPlayer.x >= -310 && posPlayer1.x - posPlayer.x < 0)) {
		if (posPlayer1.y - posPlayer.y < 0 && posPlayer1.x - posPlayer.x >= -64) {
			sprite->changeAnimation(DEGREE_120);
			decideFire(sprite->animation());
		}
		else if (posPlayer1.y - posPlayer.y < 0 && posPlayer1.x - posPlayer.x >= -128) {
			sprite->changeAnimation(DEGREE_140);
			decideFire(sprite->animation());
		}
		else if (posPlayer1.y - posPlayer.y > 0) {
			sprite->changeAnimation(DEGREE_180);
			if (posPlayer1.y - posPlayer.y < 100) decideFire(sprite->animation());
		}
	}
}

void SuperTurret::render()
{
	sprite->render();
}

void SuperTurret::setTileMap(TileMap *tileMap)
{
	map = tileMap;
}

void SuperTurret::setPosition(const glm::vec2 &pos)
{
	posPlayer = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

glm::ivec2 SuperTurret::getPosition()
{
	return posPlayer;
}


