#include "include/AudioUtils.hh"


WavInfo AudioUtils::createWavInfo(AudioFile<float>* audioFile)
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

void AudioUtils::writeWavFile(AudioFile<float> &audioFile, std::string outputFilename)
{
    audioFile.save(outputFilename, AudioFileFormat::Wave);
}

AudioFile<float> AudioUtils::samplesToAudioFile(std::vector<float> &left, 
                                    std::vector<float> &right, WavInfo info)
{
    AudioFile<float> output;
    output.samples.at(0) = left;
    output.samples.at(1) = right;

    output.setSampleRate(info.sampleRate);
    output.setBitDepth(info.bitDepth);
    output.setNumSamplesPerChannel(info.numSamples);
    output.setNumChannels(info.numChannels);

    return output;
}