#ifndef PLAYER_HH
#define PLAYER_HH

#include <iostream>
#include <string>
#include "SDL.h"
#include "AudioUtils.hh"


/// @brief Updates the audio buffer. Called by audio device each time it
///        needs a new buffer
/// @param userdata current audio file data from wavSpec
/// @param stream a pointer to the audio data buffer 
///               ie. where this funcion copies data
/// @param bufferLen length of buffer in bytes
void wavCallback(void* userdata, Uint8* stream, int bufferLen);

/// Holds the current position and length remaining in the audio file
/// https://wiki.libsdl.org/SDL2/SDL_AudioSpec
struct AudioData
{
    Uint8* pos;
    Uint32 length;
};


/// @brief Audio player object
class Player {

public:
    /// @brief Constructor, initializes SDL audio system
    Player();

    /// @brief Destructor
    ~Player();

    /// @brief Loads audio from a wav file into the player
    /// @param filename Name of the audio file to be loaded
    /// @return true if loading was successful, false otherwise
    bool loadWav(const char* filename);

    /// @brief Plays the audio
    void play();

private:
    SDL_AudioSpec wavSpec;
    Uint8* wavStart;
    Uint32 wavLength;
    AudioData audio; 
};

#endif
