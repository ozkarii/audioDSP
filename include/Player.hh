#ifndef PLAYER_HH
#define PLAYER_HH

#include <iostream>
#include <string>
#include "SDL/SDL.h"
#include "DSP.hh"
#include "AudioUtils.hh"


void wavCallback(void* userdata, Uint8* stream, int bufferLen);

// https://wiki.libsdl.org/SDL2/SDL_AudioSpec
// holds the current position and lenght remaining in the audio file
struct AudioData
{
    Uint8* pos;
    Uint32 length;
};

class Player {

public:
    Player();
    ~Player();
    void init();
    bool loadWav(const char* filename);
    void play();

private:
    SDL_AudioSpec wavSpec;  // contains information about the wav file
    Uint8* wavStart;        // pointer to the start of the wav file (or maybe the start of the block)
    Uint32 wavLength;       // length of the wav file
    const char* filename;   // 
    AudioData audio;        // 
    
};

#endif
