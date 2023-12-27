#include "Player.hh"

// userdata comes from the audio data through wavSpec
// stream = pointer to where this fucnction copies audio
// bufferLen = length of the current buffer
// has to be declared outside of Player class becuase a member function
// is not allowed by SDL
void wavCallback(void* userdata, Uint8* stream, int bufferLen) 
{
    AudioData* audio = (AudioData*)userdata;

    if (audio->length == 0) 
    {
        return;
    }

    Uint32 length;

    if ((Uint32)bufferLen > audio->length)
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

Player::Player()
{
    SDL_Init(SDL_INIT_AUDIO);
}

Player::~Player()
{
    SDL_Quit();
}

bool Player::loadWav(const char *name)
{
    filename = name;
    // load wav from "file" into memory, populate "wavSpec", "wavStart",
    // and "wavLength" accordingly
    if (SDL_LoadWAV(filename, &wavSpec, &wavStart, &wavLength) == NULL)
    {
        std::cout << "Error loading wav" << std::endl;
        return false;
    }

    audio.pos = wavStart;
    audio.length = wavLength;

    wavSpec.callback = wavCallback;
    wavSpec.userdata = &audio;

    return true;

}

void Player::play()
{
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
}


