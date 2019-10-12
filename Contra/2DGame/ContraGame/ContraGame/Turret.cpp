#include "Turret.h"
#include "Math.h"
#include <math.h>

#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 96
#define FALL_STEP 4
#define IN_RANGE 20

# define M_PI 3.14159265358979323846

enum PlayerAnims
{
	DEGREE_0, DEGREE_30, DEGREE_50, DEGREE_90, DEGREE_120, DEGREE_140, DEGREE_180, DEGREE_210,
	DEGREE_230, DEGREE_270, DEGREE_300, DEGREE_320
};

void Turret::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	bJumping = false;
	spritesheet.loadFromFile("images/turret2.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(64, 60), glm::vec2(0.111111111111111f, 0.25f), &spritesheet, &shaderProgram);
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

void Turret::update(glm::ivec2 &posPlayer1, glm::ivec2 &posPlayer2, int deltaTime)
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
	if (Game::instance().getKey('s')) sprite->changeAnimation(0);
	sprite->update(deltaTime);

	if ((posPlayer1.x - posPlayer.x >= -310 && posPlayer1.x - posPlayer.x < 0) ||
		(posPlayer1.x - posPlayer.x >= 0 && posPlayer1.x - posPlayer.x < 310)) {
		// turn left
		if ((posPlayer1.x - posPlayer.x >= -310 && posPlayer1.x - posPlayer.x < 0)) {
			if (posPlayer1.y - posPlayer.y < 0 && posPlayer1.y - posPlayer.y >= -64) sprite->changeAnimation(DEGREE_120);
			else if (posPlayer1.y - posPlayer.y < 0 && posPlayer1.y - posPlayer.y > -128) sprite->changeAnimation(DEGREE_140);
			else if (posPlayer1.y - posPlayer.y > 0 && posPlayer1.y - posPlayer.y < 64) sprite->changeAnimation(DEGREE_180);
			else if (posPlayer1.y - posPlayer.y > 64 && posPlayer1.y - posPlayer.y < 128) sprite->changeAnimation(DEGREE_210);
			else if (posPlayer1.y - posPlayer.y > 128 && posPlayer1.y - posPlayer.y < 192) sprite->changeAnimation(DEGREE_230);
			else if (posPlayer1.y > posPlayer.y && ((posPlayer1.x - posPlayer.x > -64) && (posPlayer1.x - posPlayer.x < 64))) sprite->changeAnimation(DEGREE_270);
			else if (posPlayer1.y < posPlayer.y && ((posPlayer1.x - posPlayer.x > -64) && (posPlayer1.x - posPlayer.x < 64))) sprite->changeAnimation(DEGREE_90);
		}
		//turn right
		else {
			if (posPlayer1.y - posPlayer.y < 0 && posPlayer1.y - posPlayer.y >= -64)  sprite->changeAnimation(DEGREE_30);
			else if (posPlayer1.y - posPlayer.y < 0 && posPlayer1.y - posPlayer.y > -128) sprite->changeAnimation(DEGREE_50);
			else if (posPlayer1.y - posPlayer.y > 0 && posPlayer1.y - posPlayer.y < 64) sprite->changeAnimation(DEGREE_0);
			else if (posPlayer1.y - posPlayer.y > 64 && posPlayer1.y - posPlayer.y < 128) sprite->changeAnimation(DEGREE_320);
			else if (posPlayer1.y - posPlayer.y > 128 && posPlayer1.y - posPlayer.y < 192) sprite->changeAnimation(DEGREE_300);
			else if (posPlayer1.y > posPlayer.y && ((posPlayer1.x - posPlayer.x > -64) && (posPlayer1.x - posPlayer.x < 64))) sprite->changeAnimation(DEGREE_270);
			else if (posPlayer1.y < posPlayer.y && ((posPlayer1.x - posPlayer.x > -64) && (posPlayer1.x - posPlayer.x < 64))) sprite->changeAnimation(DEGREE_90);
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


