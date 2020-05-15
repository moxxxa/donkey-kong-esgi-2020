#include "pch.h"
#include "Music.h"


const int JUMPING_FRAMES = 10;
const int FLYING_FRAMES = 15;

Music::Music()
{
}

void Music::playMusic()
{
     if (musicBuffer.loadFromFile(music1Path))
	  {
		music.setBuffer(musicBuffer);
		music.play();
		music.setLoop(true);
	  }
}

void Music::nextMusic()
{
	if (musicIndex < 3) {
		musicIndex ++;
	} else {
		musicIndex = 1;
	}
	switch (musicIndex)
	{
	case 1:
		musicBuffer.loadFromFile(music1Path);
		music.play();
		break;
	case 2:
		musicBuffer.loadFromFile(music2Path);
		music.play();
		break;
	case 3:
		musicBuffer.loadFromFile(music3Path);
		music.play();
		break;
	default:
		break;
	}
	musicIsResumed = true;
	music.setLoop(true);
}

void Music::resumePauseMusic()
{
	musicIsResumed = !musicIsResumed;
	if (musicIsResumed) {
		resumeMusic();
	} else {
		pauseMusic();
	}
	// std::cout <<"music is resumed ="<<musicIsResumed<<"\n";
}

void Music::resumeMusic()
{
	music.play();
}

void Music::pauseMusic()
{
	music.pause();
}


void Music::DieSound()
{
	music.stop();
	if (musicBuffer.loadFromFile(musicDeath))
	{
		music.setBuffer(musicBuffer);
		music.play();
	}
} 

void Music::WinSound()
{
	music.stop();
	if (musicBuffer.loadFromFile(musicWin))
	{
		music.setBuffer(musicBuffer);
		music.play();
	}
}



void Music::triggerJumdSound()
{
	if (jumdBuffer.loadFromFile(sound_mario_jump))
	{   walkSound.stop();
		jumdSound.setBuffer(jumdBuffer);
		jumdSound.play();
	}
}

void Music::triggerWalkSound(bool isPressed)
{	

	if (!isPressed)
	{
		//std::cout << "stopping music, key not pressed \n";
		walkSound.stop();
	}
	if (walkBuffer.loadFromFile(sound_mario_walk) && walkSound.getStatus() == sf::SoundSource::Status::Stopped)
	{
		//std::cout << "playing music\n";
		walkSound.setBuffer(walkBuffer);
        walkSound.setPlayingOffset(sf::seconds(0.29));
		walkSound.play();	

	}
}


