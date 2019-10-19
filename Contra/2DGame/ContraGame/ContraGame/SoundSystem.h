#pragma once
#include <string>
#include <irrKlang.h>
#include <GL/glew.h>
#include <GL/glut.h>
#pragma comment(lib, "irrKlang.lib") // link with irrKlang.dll

using namespace std;
using namespace irrklang;

class SoundSystem
{
public:
	static SoundSystem &instance()
	{
		static SoundSystem SS;

		return SS;
	}

	void playMusic(const string &level, const string &gameState);
	void playSoundEffect(const string &level, const string &effect, const string &triggerer);


private:
};

