#include <iostream>
#include <vector>
#include <string>
#include <cctype>
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

// void filter(std::string &a, std::string &b);

int main(int argc, char* argv[]) 
{
    Player audioPlayer = Player();
    if (argc == 1)
    {
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
            std::cout << "no file provided" << std::endl;
            return 1;
        }
        if (argc != 3)
        {
            std::cout << "Wrong number of params" << std::endl;
            return 1;
        }
        if ( not(audioPlayer.loadWav(args.at(2).c_str())) ) 
        {
            std::cout << "error loading file" << std::endl;
            return 1;
        }
        audioPlayer.play();
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
        if (argc < 4)
        {
            std::cout << "Wrong number of params" << std::endl;
            return 1;
        }

        AudioFile<double> aFile = AudioUtils::createAudioFile(args.at(2).c_str());
        AudioFile<double> bFile = AudioUtils::createAudioFile(args.at(3).c_str());

        AudioFile<double>* spec = &aFile;

        std::vector<double> aSamplesL = aFile.samples.at(0);
        std::vector<double> bSamplesL = bFile.samples.at(0);

        std::vector<double> leftConv = DSP::convolution(aSamplesL, bSamplesL);

        AudioFile<double> convFile = AudioUtils::samplesToAudioFile(
                          leftConv, leftConv, AudioUtils::createWavInfo(spec));
        
        AudioUtils::writeWavFile(convFile, "out.wav");

        if (args.at(4) == "-p")
        {
            if ( not(audioPlayer.loadWav("out.wav")) ) 
            {
                std::cout << "error loading file" << std::endl;
                return 1;
            }
            audioPlayer.play();
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
