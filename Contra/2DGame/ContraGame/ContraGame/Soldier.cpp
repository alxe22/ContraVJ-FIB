#include "Soldier.h"

#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 96
#define FALL_STEP 4
#define IN_RANGE 20

enum PlayerAnims
{
	STAND_LEFT, MOVE_LEFT, LAY_DOWN
};

void Soldier::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	bJumping = false;
	spritesheet.loadFromFile("images/soldier.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(0.25f, 0.25f), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(3);
	
	sprite->setAnimationSpeed(STAND_LEFT, 8);
	sprite->addKeyframe(STAND_LEFT, glm::vec2(0.75f, 0.25f));

	sprite->setAnimationSpeed(MOVE_LEFT, 8);
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.25f, 0.f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.5f, 0.f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.75f, 0.f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.25f));

	sprite->setAnimationSpeed(LAY_DOWN, 1);
	sprite->addKeyframe(LAY_DOWN, glm::vec2(0.25f, 0.5f));

	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

void Soldier::update(glm::ivec2 &posPlayer1, glm::ivec2 &posPlayer2, int deltaTime)
{
	sprite->update(deltaTime);
	if (posPlayer.x - posPlayer1.x <= 15*32) {
		if (posPlayer.x - posPlayer1.x <= 4*32 && posPlayer.x - posPlayer1.x > 0) {
			if (sprite->animation() != STAND_LEFT) {
				sprite->changeAnimation(STAND_LEFT);
				// and here will go the code to fire the gun of the soldier (we are not considering the cases
				// where the player is under or over the soldier
			}
		}
		else {
			if (sprite->animation() != MOVE_LEFT)
				sprite->changeAnimation(MOVE_LEFT);
			posPlayer.x -= 2;
			if (map->collisionMoveLeft(posPlayer, glm::ivec2(32, 32)))
			{
				posPlayer.x += 2;
				sprite->changeAnimation(STAND_LEFT);
			}
		}
	}
	/*posPlayer.y += FALL_STEP;
	if (map->collisionMoveDown(posPlayer, glm::ivec2(32, 32), &posPlayer.y))
	{
		if (Game::instance().getSpecialKey(GLUT_KEY_UP))
		{
			bJumping = true;
			jumpAngle = 0;
			startY = posPlayer.y;
		}
	}*/

	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));


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

void Soldier::render()
{
	sprite->render();
}

void Soldier::setTileMap(TileMap *tileMap)
{
	map = tileMap;
}

void Soldier::setPosition(const glm::vec2 &pos)
{
	posPlayer = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

glm::ivec2 Soldier::getPosition()
{
	return posPlayer;
}


