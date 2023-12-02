#include "AudioPlayer.hh"
#include <iostream>


void ERRCHECK(FMOD_RESULT result) {
    if (result != FMOD_OK) {
        std::cout << "Error!" << std::endl;
    }
}

AudioPlayer::AudioPlayer()
{
}

AudioPlayer::~AudioPlayer()
{
}

void AudioPlayer::initPlayer(unsigned int maxChannels)
{
    FMOD_RESULT result;     // variable used for error checking
    ERRCHECK(FMOD::System_Create(&fmodSystem));
    ERRCHECK(fmodSystem->init(2, FMOD_INIT_NORMAL, nullptr));
}


int main() {
    AudioPlayer ap = AudioPlayer();
    ap.initPlayer(2);
    std::cout << "lol" << "\n";
    return 0;
}