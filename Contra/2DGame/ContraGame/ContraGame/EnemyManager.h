#include <glm/gtc/matrix_transform.hpp>
#include "Enemy.h"

class EnemyManager
{
public:
	EnemyManager() {}

	// singleton
	static EnemyManager &instance()
	{
		static EnemyManager EM;

		return EM;
	}

	void initEnemies(GLuint nSoldier, GLuint nSniper, GLuint nTurrets, ShaderProgram &shaderProgram, TileMap *tileMap);
	void updateEnemies(glm::ivec2 &posPlayer1, glm::ivec2 &posPlayer2, int deltaTime);
	void render();

private:
	vector<Enemy *> enemies;
};

