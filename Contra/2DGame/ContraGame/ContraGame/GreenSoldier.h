#include "Enemy.h"

class GreenSoldier: public Enemy
{
public:
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram) override;
	void update(glm::ivec2 &posPlayer1, glm::ivec2 &posPlayer2, int deltaTime) override;
	void render() override;

	void setTileMap(TileMap *tileMap) override;
	void setPosition(const glm::vec2 &pos) override;
	glm::ivec2 getPosition() override;
	glm::ivec2 getSize() override;
	string type() override;
	void setAnimation(int animation) override;
	int getAnimation() override;

private:
	bool jumping;
	string state = "RUNNING"; // could be RUNNING, JUMPING_UP, JUMPING_DOWN
	string direction = "L"; // could be Left or Right
	bool jumpingDecisionMade = false;
	glm::ivec2 tileMapDispl, posPlayer;
	int jumpAngle, startY;
	Texture spritesheet;
	Sprite *sprite;
	TileMap *map;
};

