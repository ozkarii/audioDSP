#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <csignal>
#include "include/DSP.hh"
#include "include/Player.hh"

#define GET_VARIABLE_NAME(Variable) (#Variable)

std::string toLowerCase(std::string &s)
{
    std::string output = "";
    for (auto c : s) {
        output.push_back(std::tolower(c));
    }
    return output;
}

void printVector(cVector &input, std::string header = "",
                 bool inLine = true) 
{
    if (inLine) {
        std::cout << header;
        for (auto i : input)
        {
            std::cout << " " << i;
        }
        std::cout << "\n";
    }
    else 
    {
        std::cout << header << "\n";
        for (auto i : input)
        {
            std::cout << i << "\n";
        }
        std::cout << "\n";
    }
}

void printVector(std::vector<double> &input, std::string header = "",
                 bool inLine = true) 
{
    if (inLine) {
        std::cout << header << " {";
        for (auto i : input)
        {
            std::cout << i << ",";
        }
        std::cout << "}\n";
    }
    else 
    {
        std::cout << header << "\n";
        for (auto i : input)
        {
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

void filter2ch(std::string &a, std::string &b, std::string &out)
{

    AudioFile<double> aFile = AudioUtils::createAudioFile(a.c_str());
    AudioFile<double> bFile = AudioUtils::createAudioFile(b.c_str());

    WavInfo spec = AudioUtils::createWavInfo(&aFile);
    
    // hard code 16bit because 32bit doesn't work
    spec.bitDepth = 16;

    std::vector<double> aSamplesL = aFile.samples.at(0);
    std::vector<double> bSamplesL = bFile.samples.at(0);
    std::vector<double> aSamplesR = aFile.samples.at(1);
    std::vector<double> bSamplesR = bFile.samples.at(1);

    std::vector<double> leftConv = DSP::convolution(aSamplesL, bSamplesL);
    std::vector<double> rightConv = DSP::convolution(aSamplesR, bSamplesR);

    AudioFile<double> convFile = AudioUtils::samplesToAudioFile(leftConv,
                                                        rightConv, spec);
    
    AudioUtils::writeWavFile(convFile, out);
}

int main(int argc, char* argv[]) 
{
    signal(SIGINT, exitHandler);

    if (argc == 1)
    {
        // add list of all commands
        std::cout << "no params" << std::endl;
        return 1;
    }

    std::vector<std::string> args = {};
    for (int i = 0; i < argc; i++) { args.push_back(argv[i]); }

    if (args.at(1) == "-h") 
    {
        std::cout << "help: " << std::endl;
        std::cout << " " << std::endl;
        return 0;
    }

    if (toLowerCase(args.at(1)) == "play")
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
        if ( not(playSound(args.at(2))) )
        {   
            return 1;
        }
        return 0;
    }

    if (toLowerCase(args.at(1)) == "test")
    {
        if (args.at(2) == "--fft") 
        {
            cVector a = {2, 3, 4, 1, 3, 5, 29, 1};
            cVector b = {6, -2, 3, 9};

            std::vector<double> a_real = {2, 3, 4, 1, 3, 5, 29, 1};
            std::vector<double> b_real = {6, -2, 3, 9};

            printVector(a, "a:");
            printVector(b, "b:");

            DSP::zeroPad(a);
            DSP::zeroPad(b);

            printVector(a, "a_0:");
            printVector(b, "b_0:");

            cVector a_fft = DSP::fft(a);
            cVector b_fft = DSP::fft(b);

            printVector(a_fft, "fft_a:");
            printVector(b_fft, "fft_b:");

            std::vector<double> a_ifft = DSP::ifft(a_fft);
            std::vector<double> b_ifft = DSP::ifft(b_fft);

            printVector(a_ifft, "ifft_a:");
            printVector(b_ifft, "ifft_b:");
            
            std::vector<double> convAB = DSP::convolution(a_real, b_real);
            printVector(convAB, "conv:");

            return 0;
        }

        if (args.at(2) == "--conv") 
        {
            cVector a = {2, 3, 4, 1, 3, 5, 29, 1};
            cVector b = {6, -2, 3, 9};

            std::vector<double> a_real = {2, 3, 4, 1, 3, 5, 29, 1};
            std::vector<double> b_real = {6, -2, 3, 9};
                        
            std::vector<double> convAB = DSP::convolution(a_real, b_real);
            
            printVector(convAB, "conv:");

            return 0;
        }
    }

    if (toLowerCase(args.at(1)) == "filter")
    {

        std::string outputFilename = "out.wav";

        if (argc < 4)
        {
            std::cout << "Wrong number of params" << std::endl;
            return 1;
        }

        filter2ch(args.at(2), args.at(3), outputFilename);

        if (args.at(4) == "-p")
        {
            playSound(outputFilename);
        }
        
        return 0;
    }

    if (args.at(1) == "info")
    {
        if (argc != 3)
        {
            return 1;
        }
        AudioUtils::printWavInfo(args.at(2));
        return 0;
    }

}
