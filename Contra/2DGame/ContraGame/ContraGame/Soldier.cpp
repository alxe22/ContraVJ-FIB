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
	sprite = Sprite::createSprite(glm::ivec2(42, 64), glm::vec2(0.25f, 0.25f), &spritesheet, &shaderProgram);
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
	if ((posPlayer1.x - posPlayer.x >= -360 && posPlayer1.x - posPlayer.x < 0) ||
		(posPlayer1.x - posPlayer.x >= 0 && posPlayer1.x - posPlayer.x < 360)) {
		if (map->isTerrainAhead(posPlayer, glm::ivec2(42, 64), "LEFT"))
		{
			posPlayer.x -= 2;
			if (sprite->animation() != MOVE_LEFT) sprite->changeAnimation(MOVE_LEFT);
		}
		else {
			if (sprite->animation() != STAND_LEFT) sprite->changeAnimation(STAND_LEFT);
		}
	}
	posPlayer.y += FALL_STEP;
	if (map->collisionMoveDown(posPlayer, glm::ivec2(42, 64), &posPlayer.y))
	{
		// so here we can try to jump if the player shoots at the soldier
		/*if (Game::instance().getSpecialKey(GLUT_KEY_UP))
		{
			bJumping = true;
			jumpAngle = 0;
			startY = posPlayer.y;
		}*/
	}
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
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

/*glm::ivec2 Soldier::getSize()
{
	return glm::ivec2(42, 64);
}*/

string Soldier::type()
{
	return "SOLDIER";
}

glm::ivec2 Soldier::getSize()
{
	if (sprite->animation() == STAND_LEFT) return glm::ivec2(42, 64);
	else if (sprite->animation() == MOVE_LEFT) return glm::ivec2(20, 64);
}

glm::ivec2 Soldier::getTopLeftPos()
{
	if (sprite->animation() == STAND_LEFT) return glm::ivec2(posPlayer.x, posPlayer.y);
	else if (sprite->animation() == MOVE_LEFT) return glm::ivec2(posPlayer.x+9, posPlayer.y);
}