#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include "include/DSP.hh"
#include "include/Player.hh"

// adt play haha.wav
// adt filter haha.wav st_andrew.wav -o out.wav -p
// 

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
        cVector a = {2, 3, 4, 1, 3, 5, 29, 1};
        cVector b = {6, -2, 3, 9};

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

        return 0;
    }

}
