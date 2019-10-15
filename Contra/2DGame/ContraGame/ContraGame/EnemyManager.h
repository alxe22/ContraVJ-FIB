#include <glm/gtc/matrix_transform.hpp>
#include "Enemy.h"
#include <String.h>

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

	void loadSnipers(string level, ShaderProgram &shaderProgram, TileMap *tileMap);
	void loadTurrets(string level, ShaderProgram &shaderProgram, TileMap *tileMap);
	void loadSuperTurrets(string level, ShaderProgram &shaderProgram, TileMap *tileMap);
	void loadSoldiers(string level, ShaderProgram &shaderProgram, TileMap *tileMap);

private:
	vector<Enemy *> enemies;
};

