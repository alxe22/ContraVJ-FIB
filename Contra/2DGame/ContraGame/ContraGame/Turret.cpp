#include "Turret.h"

#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 96
#define FALL_STEP 4
#define IN_RANGE 20


enum PlayerAnims
{
	LEFT, RIGHT, UP, UP_LEFT, UP_RIGHT, DOWN, DOWN_LEFT, DOWN_RIGHT 
};

void Turret::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	bJumping = false;
	spritesheet.loadFromFile("images/turret.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(32, 64), glm::vec2(0.25f, 0.25f), &spritesheet, &shaderProgram);
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
	if (Game::instance().getKey('s')) sprite->changeAnimation(12);
	if (Game::instance().getKey('d')) sprite->changeAnimation(13);

	/*sprite->update(deltaTime);
	if (Game::instance().getSpecialKey(GLUT_KEY_LEFT))
	{
	if (sprite->animation() != MOVE_LEFT)
	sprite->changeAnimation(MOVE_LEFT);
	posPlayer.x -= 2;
	if (map->collisionMoveLeft(posPlayer, glm::ivec2(32, 32)))
	{
	posPlayer.x += 2;
	sprite->changeAnimation(STAND_LEFT);
	}
	}
	else if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT))
	{
	if (sprite->animation() != MOVE_RIGHT)
	sprite->changeAnimation(MOVE_RIGHT);
	posPlayer.x += 2;
	if (map->collisionMoveRight(posPlayer, glm::ivec2(32, 32)))
	{
	posPlayer.x -= 2;
	sprite->changeAnimation(STAND_RIGHT);
	}
	}
	else
	{
	if (sprite->animation() == MOVE_LEFT)
	sprite->changeAnimation(STAND_LEFT);
	else if (sprite->animation() == MOVE_RIGHT)
	sprite->changeAnimation(STAND_RIGHT);
	}

	if (bJumping)
	{
	jumpAngle += JUMP_ANGLE_STEP;
	if (jumpAngle == 180)
	{
	bJumping = false;
	posPlayer.y = startY;
	}
	else
	{
	posPlayer.y = int(startY - 96 * sin(3.14159f * jumpAngle / 180.f));
	if (jumpAngle > 90)
	bJumping = !map->collisionMoveDown(posPlayer, glm::ivec2(32, 32), &posPlayer.y);
	}
	}
	else
	{
	posPlayer.y += FALL_STEP;
	if (map->collisionMoveDown(posPlayer, glm::ivec2(32, 32), &posPlayer.y))
	{
	if (Game::instance().getSpecialKey(GLUT_KEY_UP))
	{
	bJumping = true;
	jumpAngle = 0;
	startY = posPlayer.y;
	}
	}
	}

	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));*/
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


