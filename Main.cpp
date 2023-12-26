#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <csignal>
#include <thread>
#include "include/DSP.hh"
#include "include/Player.hh"

/* 
TODO: 
- fir filter
- butterworth filter
- tests (unit, speed/size)
- polished cli
- sample rate altering
- speedup
- optimization
- switch -o for filter
- multithreading
- make params and variables const
- windows version
*/

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

// todo: overload for filtering samples

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

    if (args[1] == "-h") 
    {
        std::cout << "help: " << std::endl;
        std::cout << " " << std::endl;
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

    if (toLowerCase(args[1]) == "test")
    {
        if (args[2] == "--fft") 
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

        if (args[2] == "--conv") 
        {
            cVector a = {2, 3, 4, 1, 3, 5, 29, 1};
            cVector b = {6, -2, 3, 9};

            std::vector<double> a_real = {2, 3, 4, 1, 3, 5, 29, 1};
            std::vector<double> b_real = {6, -2, 3, 9};
                        
            std::vector<double> convAB = DSP::convolution(a_real, b_real);
            
            printVector(convAB, "conv:");

            return 0;
        }

        if (args[2] == "--fir")
        {
            // cutoff = -6dB
            std::vector<double> ir = FIR::designHamming(5500.0/48000.0, 1000.0/48000.0, FIR::LowPass);
            std::cout << ir.size() << std::endl;
            printVector(ir, "ir:", false);
            AudioFile<double> haha = AudioUtils::createAudioFile("examples/midnight6.wav");
            std::vector<double> hahaSamples = haha.samples[0];
            std::string out = "low.wav";
            WavInfo info = AudioUtils::createWavInfo(&haha);
            info.bitDepth = 16;
            std::vector<double> conv = DSP::convolution(hahaSamples, ir);
            AudioFile<double> outFile = AudioUtils::samplesToAudioFile(conv, conv, info);
            AudioUtils::writeWavFile(outFile, out);
        }
    }

    if (toLowerCase(args[1]) == "filter")
    {

        std::string outputFilename = "out.wav";

        if (argc < 4)
        {
            std::cout << "Wrong number of params" << std::endl;
            return 1;
        }

        filter2ch(args[2], args[3], outputFilename);

        if (argc == 5)
        {
            if (args[4] == "-p")
                playSound(outputFilename);
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

}
