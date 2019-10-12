#include "SuperTurret.h"

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

void SuperTurret::update(glm::ivec2 &posPlayer1, glm::ivec2 &posPlayer2, int deltaTime)
{
	sprite->update(deltaTime);
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));

	if (Game::instance().getKey('q')) sprite->changeAnimation(1);
	if (Game::instance().getKey('w')) sprite->changeAnimation(2);
	if (Game::instance().getKey('e')) sprite->changeAnimation(0);
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


