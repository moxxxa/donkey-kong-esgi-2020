#pragma once
#include <SFML/Audio.hpp>

class Music
{
public:
	Music();
	virtual ~Music() { };

public:
	void playMusic();
	void nextMusic();
	void resumePauseMusic();
	void pauseMusic();
	void resumeMusic();
	void DieSound(); 
	void WinSound();
	void triggerJumdSound();
	void triggerWalkSound(bool isPressed);


public:
    short musicIndex = 1;
	bool musicIsResumed = true;

	sf::SoundBuffer musicBuffer;
	sf::Sound music;
	std::string music1Path = "Media/Sounds/piste_1.wav";
	std::string music2Path = "Media/Sounds/piste_2.wav";
	std::string music3Path = "Media/Sounds/piste_3.wav";
	std::string musicDeath = "Media/Sounds/death.wav";
	std::string musicWin =   "Media/Sounds/thank_you.wav";
	

	sf::SoundBuffer jumdBuffer;
	sf::Sound jumdSound;
	sf::SoundBuffer walkBuffer;
	sf::Sound walkSound;
	std::string sound_mario_jump = "Media/Sounds/mario_jump.wav";
	std::string sound_mario_walk = "Media/Sounds/mario_walk.wav";
	
};
