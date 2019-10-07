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

	void initEnemies(GLuint nSoldier, GLuint nSniper, GLuint nTurrets);
	void updateEnemies(glm::ivec2 &posPlayer1, glm::ivec2 &posPlayer2, int deltaTime);

private:
	vector<Enemy *> enemies;
};

