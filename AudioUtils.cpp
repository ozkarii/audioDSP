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
                                    std::vector<double> &right, WavInfo &info)
{
    AudioFile<double> output;
    
    output.setSampleRate(info.sampleRate);
    output.setBitDepth(info.bitDepth);
    output.setNumSamplesPerChannel(left.size());
    output.setNumChannels(2);
    
    output.samples.at(0) = left;
    output.samples.at(1) = right;

    return output;
}

void AudioUtils::printWavInfo(std::string filename)
{
    AudioFile<double> file(filename);
    std::cout << "Sample rate: " << file.getSampleRate() << std::endl;
    std::cout << "Bit depth: : " << file.getBitDepth() << std::endl;
    std::cout << "Number of samples per channel: " << file.getNumSamplesPerChannel() << std::endl;
    std::cout << "Number of channels: " << file.getNumChannels() << std::endl;
    //std::cout << "Is stereo: " << file.isStereo() << std::endl;
    //std::cout << "Is mono: " << file.isMono() << std::endl;
}
