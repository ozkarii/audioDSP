#include <iostream>
#include "include/SDL.h"

// https://wiki.libsdl.org/SDL2/SDL_AudioSpec


// holds the current position and lenght remaining in the audio file
struct AudioData
{
    Uint8* pos;
    Uint32 length;
};

// userdata comes from the audio data through wavSpec
// stream = pointer to where this fucnction copies audio
// bufferLen = length of the current buffer
void wavCallback(void* userdata, Uint8* stream, int bufferLen) 
{
    AudioData* audio = (AudioData*)userdata;

    if (audio->length == 0) 
    {
        return;
    }

    Uint32 length;

    if (bufferLen > audio->length)
    {
        length = audio->length;
    }
    else 
    {
        length = bufferLen;
    }

    // copy to the stream from the current position in the audio
    SDL_memcpy(stream, audio->pos, length);

    //update audio position and the remaining length
    audio->pos += length;
    audio->length -= length;
}



int main() 
{
    SDL_Init(SDL_INIT_AUDIO);
    
    SDL_AudioSpec wavSpec;  // contains information about the wav file
    Uint8* wavStart;        // pointer to the start of the wav file (or maybe the start of the block)
    Uint32 wavLength;       // length of the wav file

    const char* file = "back.wav";

    // load wav from "file" into memory, populate "wavSpec", "wavStart",
    // and "wavLength" accordingly
    if (SDL_LoadWAV(file, &wavSpec, &wavStart, &wavLength) == NULL)
    {
        std::cout << "Error loading wav" << std::endl;
        return 1;
    }
    
    AudioData audio;
    audio.pos = wavStart;
    audio.length = wavLength;

    wavSpec.callback = wavCallback;
    wavSpec.userdata = &audio;

    // init audio device, allow changing wavSpec to match audio device's spec
    SDL_AudioDeviceID audioDevice = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL,
                                    SDL_AUDIO_ALLOW_ANY_CHANGE);
    
    if (audioDevice == 0)
    {
        std::cout << "Error: " << SDL_GetError() << std::endl;
    }

    SDL_PauseAudioDevice(audioDevice, 0);

    while (audio.length > 0)
    {
        SDL_Delay(200);
    }

    SDL_CloseAudioDevice(audioDevice);
    SDL_Quit();
    return 0;
}