#include "sound.h"

#include "raylib.h"
namespace arkanoid_IDG {
	Music originalMusic;
	Music originalMusic1;
	Sound originalSound;
	static Wave wave;

	void initSounds()
	{
		originalMusic = LoadMusicStream("sounds/epic_song.ogg");
		originalMusic1 = LoadMusicStream("sounds/NotSoEpicSongySong.ogg");
		wave = LoadWave("sounds/epic_sound.wav");
		originalSound = LoadSoundFromWave(wave);
		UnloadWave(wave);
		SetSoundPitch(originalSound,2.0f);
		PlayMusicStream(originalMusic);
		PlayMusicStream(originalMusic1);
		SetSoundVolume(originalSound,0.1f);
		SetMusicVolume(originalMusic1,0.1f);
		SetMasterVolume(0.1f);
	}

	void resetSounds()
	{
		StopMusicStream(originalMusic);
		PlayMusicStream(originalMusic);
		StopMusicStream(originalMusic1);
		PlayMusicStream(originalMusic1);
	}

	void unloadSounds()
	{
		UnloadSound(originalSound);
		UnloadMusicStream(originalMusic);
		UnloadMusicStream(originalMusic1);
	}
}