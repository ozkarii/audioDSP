#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <csignal>
#include <thread>
#include "DSP.hh"
#include "Player.hh"


std::string toLowerCase(std::string &s)
{
    std::string output = "";
    for (auto c : s) {
        output.push_back(std::tolower(c));
    }
    return output;
}

template <typename T>
void printVector(const T& input, const std::string& header = "",
                 bool inLine = true) {
    if (inLine) {
        std::cout << header << " {";
        for (const auto& i : input) {
            std::cout << " " << i << ",";
        }
        std::cout << "}\n";
    } else {
        std::cout << header << "\n";
        for (const auto& i : input) {
            std::cout << i << "\n";
        }
        std::cout << "\n";
    }
}

void exitHandler(int signal)
{
    std::cout << " Exiting... caught signal: " << signal << std::endl;
    exit(1);
}

bool playSound(std::string &filename) 
{
    Player audioPlayer = Player();
    if ( not(audioPlayer.loadWav(filename.c_str())) ) 
    {
        std::cout << "Error loading file" << std::endl;
        return false;
    }
    audioPlayer.play();
    return true;
}

// thread for calculating the convolution of two signals
void convolutionThread(std::vector<double> &aSamples, 
                       std::vector<double> &bSamples,
                       std::vector<double> &result) 
{
    result = DSP::convolution(aSamples, bSamples);
}

void filter2ch(std::string &a, std::string &b, std::string &out)
{

    AudioFile<double> aFile = AudioUtils::createAudioFile(a.c_str());
    AudioFile<double> bFile = AudioUtils::createAudioFile(b.c_str());

    WavInfo spec = AudioUtils::createWavInfo(&aFile);
    
    // hard code 16bit because 32bit doesn't work
    spec.bitDepth = 16;

    std::vector<double> aSamplesL = aFile.samples[0];
    std::vector<double> bSamplesL = bFile.samples[0];
    std::vector<double> aSamplesR = aFile.samples[1];
    std::vector<double> bSamplesR = bFile.samples[1];

    std::vector<double> leftConv, rightConv;
    std::thread leftThread(convolutionThread, std::ref(aSamplesL), 
                           std::ref(bSamplesL), std::ref(leftConv));
    std::thread rightThread(convolutionThread, std::ref(aSamplesR), 
                           std::ref(bSamplesR), std::ref(rightConv));

    leftThread.join();
    rightThread.join();

    AudioFile<double> convFile = AudioUtils::samplesToAudioFile(leftConv,
                                                        rightConv, spec);
    
    AudioUtils::writeWavFile(convFile, out);
}


int main(int argc, char* argv[]) 
{
    signal(SIGINT, exitHandler);

    if (argc == 1)
    {
        std::cout << "No params!" << std::endl;
        std::cout << "Available commands:\n"
                  << "   play <audio_file_path>\n"
                  << "   filter <audio_path> <ir_path> optional flags: \n\
          'specify output file (default out.wav)' -o <output_file>, 'play sound' -p\n"
                  << "   info (about wav file)\n" 
                  << "   help" << std::endl;
        return 1;
    }

    std::vector<std::string> args = {};
    for (int i = 0; i < argc; i++) { args.push_back(argv[i]); }

    if (args[1] == "-h" or args[1] == "--help" or args[1] == "help") 
    {
        std::cout << "Available commands:\n"
                  << "   play <audio_file_path>\n"
                  << "   filter <audio_path> <ir_path> optional flags: \n\
        'specify output file (default out.wav)' -o <output_file>, 'play sound' -p\n"
                  << "   info (about wav file)\n" 
                  << "   help" << std::endl;
        
        return 0;
    }

    if (toLowerCase(args[1]) == "play")
    {
        if (argc <= 2) 
        {
            std::cout << "No file provided" << std::endl;
            return 1;
        }
        if (argc != 3)
        {
            std::cout << "Wrong number of params" << std::endl;
            return 1;
        }
        if ( not(playSound(args[2])) )
        {   
            return 1;
        }
        return 0;
    }

    if (toLowerCase(args[1]) == "filter")
    {
        std::string outputFilename = "out.wav";

        if (argc < 4)
        {
            std::cout << "Wrong number of params" << std::endl;
            return 1;
        }

        if (argc == 4) 
        {
            filter2ch(args[2], args[3], outputFilename);
            return 0;
        }

        if (argc == 5)
        {
            if (args[4] == "-o") {
                std::cout << "No filename provided" << std::endl;
                return 1;
            }
            else if (args[4] == "-p") {
                if(playSound(outputFilename)) {return 0;}
                return 1;
            }
            else {
                std::cout << "Invalid parameters" << std::endl;
                return 1;
            }
        }

        if (argc == 6)
        {
            if (args[4] == "-o") {
                outputFilename = args[5];
                filter2ch(args[2], args[3], outputFilename);
                return 0;
            }
            else {
                std::cout << "Invalid parameters" << std::endl;
                return 1;
            }
        }

        if (argc == 7)
        {
            if (args[4] == "-o") {
                outputFilename = args[5];
                filter2ch(args[2], args[3], outputFilename);
                if (args[6] == "-p") {
                    if(playSound(outputFilename)){return 0;}
                    return 1;
                }
                std::cout << "Invalid parameters" << std::endl;
                return 1;
            }
            std::cout << "Invalid parameters" << std::endl;         
            return 1;
        }

        if (argc > 7) {
            std::cout << "Too many parameters" << std::endl;
            return 1;
        }
        
        return 0;
    }

    if (args[1] == "info")
    {
        if (argc != 3)
        {
            return 1;
        }
        AudioUtils::printWavInfo(args[2]);
        return 0;
    }

    std::cout << "Invalid parameters, try help" << std::endl;
    return 1;

}
