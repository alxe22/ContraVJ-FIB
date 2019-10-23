#include "GreenSoldier.h"

#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 96
#define FALL_STEP 4
#define IN_RANGE 20

enum PlayerAnims
{
	MOVE_LEFT, MOVE_RIGHT, LAY_DOWN, JUMP
};

void GreenSoldier::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	bJumping = false;
	spritesheet.loadFromFile("images/green_soldier.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(1 / 4.f, 1 / 4.f), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(3);

	sprite->setAnimationSpeed(MOVE_LEFT, 8);
	//sprite->addKeyframe(MOVE_LEFT, glm::vec2(0 / 4.f, 1 / 4.f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(1 / 4.f, 1 / 4.f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(2 / 4.f, 1 / 4.f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(3 / 4.f, 1 / 4.f));

	sprite->setAnimationSpeed(MOVE_RIGHT, 8);
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0 / 4.f, 2 / 4.f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(1 / 4.f, 2 / 4.f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(2 / 4.f, 2 / 4.f));
	//sprite->addKeyframe(MOVE_RIGHT, glm::vec2(3 / 4.f, 2 / 4.f));

	sprite->setAnimationSpeed(LAY_DOWN, 1);
	sprite->addKeyframe(LAY_DOWN, glm::vec2(0 / 4.f, 0 / 4.f));

	sprite->setAnimationSpeed(JUMP, 1);
	sprite->addKeyframe(LAY_DOWN, glm::vec2(0 / 4.f, 0 / 4.f));

	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	//sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

void GreenSoldier::update(glm::ivec2 &posPlayer1, glm::ivec2 &posPlayer2, int deltaTime)
{
	sprite->update(deltaTime);
	if (sprite->animation() == MOVE_LEFT) posPlayer.x -= 1.5f;
	else {
		if (sprite->animation() != MOVE_RIGHT) {
			sprite->changeAnimation(MOVE_RIGHT);
		}
		posPlayer.x += 1.5f;
	}
	sprite->setPosition(glm::vec2(float(posPlayer.x), float(posPlayer.y)));
}

void GreenSoldier::render()
{
	sprite->render();
}

void GreenSoldier::setTileMap(TileMap *tileMap)
{
	map = tileMap;
}

void GreenSoldier::setPosition(const glm::vec2 &pos)
{
	posPlayer = pos;
	sprite->setPosition(glm::vec2(float(posPlayer.x), float(posPlayer.y)));
}

glm::ivec2 GreenSoldier::getPosition()
{
	return posPlayer;
}

glm::ivec2 GreenSoldier::getSize()
{
	return glm::ivec2(32, 32);
}

string GreenSoldier::type()
{
	return "GREEN_SOLDIER";
}

void GreenSoldier::setAnimation(int animation) 
{
	sprite->changeAnimation(animation);
}

int GreenSoldier::getAnimation() 
{
	return sprite->animation();
}