#include "include/AudioUtils.hh"


WavInfo AudioUtils::createWavInfo(AudioFile<double>* audioFile)
{
    WavInfo wavInfo;
    wavInfo.sampleRate = audioFile->getSampleRate();
    wavInfo.bitDepth = audioFile->getBitDepth();
    wavInfo.numSamples = audioFile->getNumSamplesPerChannel();
    wavInfo.lengthInSeconds = audioFile->getLengthInSeconds();
    wavInfo.numChannels = audioFile->getNumChannels();
    wavInfo.isMono = audioFile->isMono();
    wavInfo.isStereo = audioFile->isStereo();
    return wavInfo;
}

AudioFile<double> AudioUtils::createAudioFile(const char* file) 
{
    AudioFile<double> audioFile;
    audioFile.load(file);
    return audioFile;    
}

void AudioUtils::writeWavFile(AudioFile<double> &audioFile, std::string outputFilename)
{
    audioFile.save(outputFilename, AudioFileFormat::Wave);
}

AudioFile<double> AudioUtils::samplesToAudioFile(std::vector<double> &left, 
                                    std::vector<double> &right, WavInfo info)
{
    AudioFile<double> output;
    output.samples.at(0) = left;
    output.samples.at(1) = right; // out of range error here

    output.setSampleRate(info.sampleRate);
    output.setBitDepth(info.bitDepth);
    output.setNumSamplesPerChannel(info.numSamples);
    output.setNumChannels(info.numChannels);

    return output;
}