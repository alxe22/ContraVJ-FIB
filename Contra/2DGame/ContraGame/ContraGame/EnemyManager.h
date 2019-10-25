#include <glm/gtc/matrix_transform.hpp>
#include "Enemy.h"
#include <string>

using namespace std;

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

	void initEnemies(GLuint nSoldier, GLuint nSniper, GLuint nTurrets, ShaderProgram &shaderProgram, TileMap *tileMap, string level);
	void updateEnemies(glm::ivec2 &posPlayer1, glm::ivec2 &posPlayer2, int deltaTime, string level);
	void detectBulletCollisions(string level);
	void render();

	void loadSnipers(string level, ShaderProgram &shaderProgram, TileMap *tileMap);
	void loadTurrets(string level, ShaderProgram &shaderProgram, TileMap *tileMap);
	void loadSuperTurrets(string level, ShaderProgram &shaderProgram, TileMap *tileMap);
	void loadSoldiers(string level, ShaderProgram &shaderProgram, TileMap *tileMap);

	// there is no tilemap in lv2 so we omit this parameter
	void loadGreenSoldiers(string level, ShaderProgram &shaderProgram);
	bool canAdvance();
	void setCanAdvance(int i);
	void deleteAll();

private:
	vector<Enemy *> enemies;
	ShaderProgram shaderProgram;
	long long miliLastGreenSoldierCreated = 0;
	int greenSoldiersKilled = 0;
};

