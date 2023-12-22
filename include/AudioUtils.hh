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

    //
    WavInfo createWavInfo(AudioFile<double>* audioFile);
    
    // creates an AudioFile type object from a .wav file for example
    // AudioFile object allows access to sample data etc.
    // TODO: maybe change char* to std::string
    AudioFile<double> createAudioFile(const char *file);
    
    void writeWavFile(AudioFile<double> &audioFile, std::string outputFilename);
    
    AudioFile<double> samplesToAudioFile(std::vector<double> &left,
                                        std::vector<double> &right, WavInfo info);
    
    void printWavInfo(std::string filename);
};



#endif