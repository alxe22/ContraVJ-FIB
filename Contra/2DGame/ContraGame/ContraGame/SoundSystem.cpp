#include "SoundSystem.h"

ISoundEngine *SoundEngine = createIrrKlangDevice();

void SoundSystem::playMusic(const string &level, const string &gameState) {
	if (gameState == "MENU") {
		SoundEngine->play2D("audio/menu-music.mp3", GL_FALSE);
	 }
	if (gameState == "PLAYING") {
		if (level == "level01") {
			SoundEngine->stopAllSounds();
			SoundEngine->play2D("audio/level01-music.mp3", GL_TRUE);
		}
		else if (level == "level02") {
			SoundEngine->stopAllSounds();
			SoundEngine->play2D("audio/level01-music.mp3", GL_TRUE);
		}
	}
}

void SoundSystem::playSoundEffect(const string &level, const string &effect, const string &triggerer) 
{
	if (level == "level01") {
		if (effect == "SHOOT") {
			if (triggerer == "CHARACTER") SoundEngine->play2D("audio/level01-shoot.mp3", GL_FALSE);
			else if (triggerer == "SNIPER") SoundEngine->play2D("audio/level01-sniper-shoot.mp3", GL_FALSE);
			else if (triggerer == "TURRET") SoundEngine->play2D("audio/level01-turret-shoot.mp3", GL_FALSE);
			else if (triggerer == "SUPER_TURRET") SoundEngine->play2D("audio/level01-turret-shoot.mp3", GL_FALSE);

		}
	}
}