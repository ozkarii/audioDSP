#include "include/DSP.hh"
#include <iostream>


std::vector<float> DSP::convolution(const std::vector<float> &sound,
                                    const std::vector<float> &ir)
{
    unsigned int irLength = ir.size();
    unsigned int soundLength = sound.size();
    std::cout << soundLength + irLength << std::endl;
    std::vector<float> output(soundLength + irLength - 1, 0);

    for (int n = 0; n < soundLength; n++)
    {
        for (int k = 0; k < irLength; k++)
        {
            output[n + k] += ir[k] * sound[n];
        }
    }

    return output;
}

cVector DSP::fft(cVector &input) 
{
    unsigned int len = input.size();
    cVector odd;
    cVector even;
    cVector oddFft;
    cVector evenFft;
    std::complex<double> im(0, 1);

    if (len == 1) 
    {
        return input;
    }

    for (int n(0); n < len; n += 2)
    {
        even.push_back(input.at(n));
    }

    for (int n(1); n < len; n += 2) 
    {
        odd.push_back(input.at(n));
    }

    evenFft = fft(even);
    oddFft = fft(odd);

    int halfLen = len / 2;

    cVector result(len);

    for (int n = 0; n < halfLen; ++n)
    {
        std::complex<double> t = std::polar(1.0, -2 * M_PI * n / len) * oddFft.at(n);
        result.at(n) = evenFft.at(n) + t;
        result.at(n + halfLen) = evenFft.at(n) - t;
    }

    return result;
}

// add zeros until the length of input is a power of two
void DSP::zeroPad(cVector &input)
{
    int nearestPow2 = 1;
    while (nearestPow2 < input.size()) nearestPow2 <<= 1;
    input.resize(nearestPow2, std::complex<double>(0, 0));
}

cVector DSP::toComplexVector(std::vector<double> &input)
{
    cVector result(input.size());

    for (int i = 0; i < input.size(); i++)
    {
        result[i] = std::complex<double>(input[i], 0);
    }

    return result;
}