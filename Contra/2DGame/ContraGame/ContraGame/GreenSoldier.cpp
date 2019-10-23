#include "GreenSoldier.h"

#define JUMP_ANGLE_STEP 4
#define JUMP_Y_MAX_HEIGHT 190
#define JUMP_Y_MIN_HEIGHT 210
#define FALL_STEP 4
#define IN_RANGE 20
#define MIDDLE_POINT 300

enum PlayerAnims
{
	MOVE_LEFT, MOVE_RIGHT, LAY_DOWN, JUMP
};

void GreenSoldier::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	jumping = false;
	spritesheet.loadFromFile("images/green_soldier.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(1 / 4.f, 1 / 4.f), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(4);

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
	sprite->addKeyframe(JUMP, glm::vec2(1 / 4.f, 0 / 4.f));

	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	//sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

void GreenSoldier::update(glm::ivec2 &posPlayer1, glm::ivec2 &posPlayer2, int deltaTime)
{
	sprite->update(deltaTime);
	if (sprite->animation() == 0 && direction != "L") direction = "L";
	else if (sprite->animation() == 1 && direction != "R") direction = "R";
	if ((posPlayer.x >= float(MIDDLE_POINT - 1.5) && posPlayer.x <= float(MIDDLE_POINT + 1.5)) && !jumpingDecisionMade) {
		jumpingDecisionMade = true;
		int randAux = rand() % 2;
		if (randAux % 2 == 0) {
			jumping = true;
			state = "JUMPING_UP";
			if (sprite->animation() != JUMP) sprite->changeAnimation(JUMP);
		}
	}
	if (jumpingDecisionMade && (state == "JUMPING_UP" || state == "JUMPING_DOWN")) {
		if (state == "JUMPING_UP") {
			if (posPlayer.y > JUMP_Y_MAX_HEIGHT) posPlayer.y -= 2;
			else {
				state = "JUMPING_DOWN";
				posPlayer.y = JUMP_Y_MAX_HEIGHT;
			}
		}
		else if (state == "JUMPING_DOWN") {
			if (posPlayer.y < JUMP_Y_MIN_HEIGHT) posPlayer.y += 2;
			else {
				state = "RUNNING";
				posPlayer.y = JUMP_Y_MIN_HEIGHT;
			}
		}
	}
	if (state == "RUNNING") {
		if (direction == "L") {
			if (sprite->animation() != 0) sprite->changeAnimation(MOVE_LEFT);
			posPlayer.x -= 1.5f;
		}
		else if (direction == "R") {
			if (sprite->animation() != 1) sprite->changeAnimation(MOVE_RIGHT);
			posPlayer.x += 1.5f;
		}
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