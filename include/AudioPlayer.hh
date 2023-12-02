#ifndef AUDIOPLAYER_HH
#define AUDIOPLAYER_HH

#include "fmod_studio.hpp"
#include "fmod.hpp"
#include "fmod_errors.h"


void ERRCHECK(FMOD_RESULT result);


class AudioPlayer {

    public:

    AudioPlayer();

    ~AudioPlayer();

    void initPlayer(unsigned int maxChannels);

    void loadAudio();

    void playAudio();
    
    void setVolume();

    
    private:

    FMOD::System* fmodSystem = nullptr;

};


#endif
