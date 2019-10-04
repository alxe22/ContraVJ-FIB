#include "SoundSystem.h"

ISoundEngine *SoundEngine = createIrrKlangDevice();

SoundSystem *SoundSystem::createSoundSystem(const string &levelFile)
{
	SoundSystem *sy = new SoundSystem(levelFile);

	return sy;
}

SoundSystem::SoundSystem(const string& level)
{
	playMusic(level);
}


SoundSystem::~SoundSystem()
{
}

void SoundSystem::playMusic(const string &level) {
	if (STATE == "PLAYING") {
	}
	STATE = "PLAYING";
	if(level == "level01")
		SoundEngine->play2D("audio/level01-music.mp3", GL_TRUE);
	else if(level == "level02")
		SoundEngine->play2D("audio/level01-music.mp3", GL_TRUE);

}
