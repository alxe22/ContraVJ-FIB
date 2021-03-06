#include "Sprite.h"
#include "TileMap.h"

class Bullet
{
public:
	void init(const glm::ivec2 &tileMapPos, const glm::vec2 &pos, const glm::vec2 &dir, int speed, ShaderProgram &shaderProgram);
	void update(int deltaTime);
	void render();

	void setTileMap(TileMap *tileMap);
	glm::ivec2 getPosition() const;
	void setFiredBy(const string firedBy);
	string getFiredBy() const;
	void changeBulletAnimation(const int animNum) const;
	int getAnimation() const;

private:
	Texture spritesheet;
	Sprite *sprite;
	TileMap *map;
	glm::ivec2 tileMapDispl;
	glm::vec2 pos, dir;
	string firedBy;
	int speed;
};