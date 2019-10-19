

#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include "Bullet.h"

using namespace std;

// Game is a singleton

class BulletManager
{
public:

	BulletManager() {}

	static BulletManager &instance()
	{
		static BulletManager BM;

		return BM;
	}
	// TODO: call this every time map changes
	void initBulletManager(ShaderProgram &shaderProgram, TileMap *tileMap);
	void fire(vector<glm::vec2> dir, vector<glm::vec2> pos, int speed, string firedBy);
	bool existsBulletColision(glm::vec2 topLeft, int width, int height, string type);
	void update(glm::ivec2 &posPlayer1, glm::ivec2 &posPlayer2, int deltaTime);
	void render();

private:
	vector<Bullet *> bullets;
	ShaderProgram shaderProgram;
	TileMap *tileMap;
};