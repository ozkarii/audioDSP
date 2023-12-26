#ifndef DSP_HH
#define DSP_HH

#include <vector>
#include <complex>
#include <cmath>
#include "Math.hh"
#include "FIR.hh"

namespace DSP
{

    std::vector<double> slowConvolution(std::vector<double> &sound,
                                       std::vector<double> &ir);
    
    cVector fft(cVector &input);

    cVector ifftUnnormalized(cVector &input);

    std::vector<double> ifft(cVector &input);

    void zeroPad(cVector &input);
    void zeroPad(cVector &input, unsigned int length);

    cVector toComplexVector(std::vector<double> &input);

    std::vector<double> convolution(std::vector<double> &a,
                                    std::vector<double> &b);

    std::vector<double> decimate(std::vector<double> &input,
                                 unsigned int factor);
            
    std::vector<double> interpolateZeros(std::vector<double> &input,
                                         unsigned int factor);
    
    
};

#endif