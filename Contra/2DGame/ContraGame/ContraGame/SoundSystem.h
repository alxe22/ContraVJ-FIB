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
	static SoundSystem *createSoundSystem(const string &levelFile);
	SoundSystem(const string &level);
	~SoundSystem();

	void playMusic(const string &level);

private:
	string STATE = "NOT_PLAYING";
};

