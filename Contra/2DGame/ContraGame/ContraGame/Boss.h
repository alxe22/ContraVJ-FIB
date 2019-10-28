#pragma once
#include "Sprite.h"
#include "TileMap.h"
#include "BossArm.h"

using namespace std;

class Boss
{
public:
	Boss();
	~Boss();

	static Boss &instance()
	{
		static Boss BM;

		return BM;
	}

	void init(const glm::ivec2 & tileMapPos, ShaderProgram & shaderProgram);
	void update(int deltaTime, const glm::ivec2 & tileMapPos, ShaderProgram & shaderProgram);
	void createBullet(glm::vec2 pos, glm::vec2 dir, const glm::ivec2 & tileMapPos, ShaderProgram & shaderProgram);
	void render();
	bool existsBulletColision(glm::vec2 topLeft, int width, int height);

private:
	int Life;
	bool F;
	BossArm *arm1;
	BossArm *arm2;
	BossArm *arm3;
	BossArm *arm4;
	BossArm *head;
	glm::ivec2 tileMapDispl;
	ShaderProgram shaderProgram;
	vector<BossBullet *> bullets;
	int armshoot;
	long long lastBullet;
	bool fase2;
};