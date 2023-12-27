#include <iostream>
#include "DSP.hh"


std::vector<double> DSP::slowConvolution(std::vector<double> &sound,
                                        std::vector<double> &ir)
{
    unsigned int irLength = ir.size();
    unsigned int soundLength = sound.size();
    std::cout << soundLength + irLength << std::endl;
    std::vector<double> output(soundLength + irLength - 1, 0);

    for (unsigned int n = 0; n < soundLength; n++)
    {
        for (unsigned int k = 0; k < irLength; k++)
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

    for (unsigned int n(0); n < len; n += 2)
    {
        even.push_back(input[n]);
    }

    for (unsigned int n(1); n < len; n += 2) 
    {
        odd.push_back(input[n]);
    }

    evenFft = fft(even);
    oddFft = fft(odd);

    int halfLen = len / 2;

    cVector result(len);

    for (int n = 0; n < halfLen; ++n)
    {
        std::complex<double> t = std::polar(1.0, -2 * M_PI * n / len) * oddFft[n];
        result[n] = evenFft[n] + t;
        result[n + halfLen] = evenFft[n] - t;
    }

    return result;
}

cVector DSP::ifftUnnormalized(cVector &input)
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

    for (unsigned int n(0); n < len; n += 2)
    {
        even.push_back(input[n]);
    }

    for (unsigned int n(1); n < len; n += 2) 
    {
        odd.push_back(input[n]);
    }

    evenFft = ifftUnnormalized(even);
    oddFft = ifftUnnormalized(odd);

    int halfLen = len / 2;

    cVector result(len);

    for (int n = 0; n < halfLen; ++n)
    {
        std::complex<double> t = std::polar(1.0, 2 * M_PI * n / len) * oddFft[n];
        result[n] = (evenFft[n] + t);
        result[n + halfLen] = (evenFft[n] - t);
    }

    return result;
}

std::vector<double> DSP::ifft(cVector &input)
{
    cVector unnormalized = DSP::ifftUnnormalized(input);
    std::vector<double> output(unnormalized.size());

    for (unsigned int i = 0; i < unnormalized.size(); i++)
    {
        output[i] = unnormalized[i].real()/unnormalized.size();
    }

    return output;
}

// add zeros to the end until the length of input is a power of two
void DSP::zeroPad(cVector &input)
{
    unsigned long int nearestPow2 = 1;
    while (nearestPow2 < input.size()) nearestPow2 <<= 1;
    input.resize(nearestPow2, std::complex<double>(0, 0));
}

// add zeros until given length is reached
void DSP::zeroPad(cVector &input, unsigned int length)
{
    input.resize(length, std::complex<double>(0, 0));
}


cVector DSP::toComplexVector(std::vector<double> &input)
{
    cVector result(input.size());

    for (unsigned int i = 0; i < input.size(); i++)
    {
        result[i] = std::complex<double>(input[i], 0);
    }

    return result;
}


std::vector<double> DSP::convolution(std::vector<double> &a,
                                     std::vector<double> &b)
{

    // convert input signals to complex vectors
    cVector complexA = DSP::toComplexVector(a);
    cVector complexB = DSP::toComplexVector(b);
    
    // define output length to match linear convolution
    unsigned int outN = a.size() + b.size() - 1;
    
    // add zeros to minimum output length
    DSP::zeroPad(complexA, outN);
    DSP::zeroPad(complexB, outN);

    // add zeros to the end to make both's length a power of two
    DSP::zeroPad(complexA);
    DSP::zeroPad(complexB);

    // perform fft on both signals
    cVector fftA = DSP::fft(complexA);
    cVector fftB = DSP::fft(complexB);

    // multiply fft's elementwise
    cVector fftProduct = Math::multiplyElementWise(fftA, fftB);

    // finally perform inverse fft to get the convolution of a and b
    std::vector<double> conv = ifft(fftProduct);

    // reduce output length to outN
    if (conv.size() >= outN) 
    {
        conv.erase(conv.begin() + outN, conv.end());
    } 
    else 
    {
        conv.clear();
    }

    return conv;

}

std::vector<double> DSP::decimate(std::vector<double> &input,
                                  unsigned int factor)
{
    std::vector<double> output; 
    for (unsigned int i = 0; i < input.size(); i++)
    {
        if (i % factor == 0)
        {
            output.push_back(input[i]);
        }
    }
    return output;
}

std::vector<double> DSP::interpolateZeros(std::vector<double> &input,
                                          unsigned int factor)
{
    std::vector<double> output; 
    for (unsigned int i = 0; i < input.size(); i++)
    {
        output.push_back(input[i]);
        for (unsigned int j = 0; j < factor; j++)
        {
            output.push_back(0);
        }
    }
    return output;
}