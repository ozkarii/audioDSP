#ifndef AudioUtils_HH
#define AudioUtils_HH

#include "AudioFile/AudioFile.h"

struct WavInfo
{
    int sampleRate;
    int bitDepth;
    int numSamples;
    double lengthInSeconds;
    int numChannels;
    bool isMono;
    bool isStereo;
};


namespace AudioUtils {

    WavInfo createWavInfo(AudioFile<float>* audioFile);
    AudioFile<double> createAudioFile(const char *file);
    void writeWavFile(AudioFile<float> &audioFile, std::string outputFilename);
    AudioFile<float> samplesToAudioFile(std::vector<float> &left,
                                        std::vector<float> &right, WavInfo info);
};



#endif