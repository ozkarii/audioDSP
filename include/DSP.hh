#ifndef DSP_HH
#define DSP_HH

#include <vector>
#include <complex>
#include <cmath>
#include "Math.hh"
#include "FIR.hh"

namespace DSP
{
    /// @brief Slow naive linear convolution implementation
    /// @param a First signal to be convloved
    /// @param b Second signal to be convloved
    /// @return Convolved signal
    std::vector<double> slowConvolution(std::vector<double> &a,
                                        std::vector<double> &ir);
    
    /// @brief Fast fourier transform for a complex vector.
    ///        Implemented using the divide and conquer method O(n log(n)).
    /// @param input Input signal
    /// @return fft of input signal
    cVector fft(cVector &input);

    /// @brief Unnormalized inverse fast fourier transform for a 
    ///         complex vector. Implemented using the divide and conquer
    ///         method O(n log(n)).
    /// @param input Input signal
    /// @return ifft unnormalized as a complex vector
    cVector ifftUnnormalized(cVector &input);

    /// @brief Normalized inverse fast fourier transform for a 
    ///        complex vector. Implemented using the divide and conquer 
    ///        method O(n log(n)).
    /// @param input Input signal
    /// @return ifft of input singal
    std::vector<double> ifft(cVector &input);

    /// @brief Adds zeros to the end until the length of input
    ///        is a power of two.
    /// @param input Vector to be padded
    void zeroPad(cVector &input);
    
    /// @brief Add zeros until given length is reached
    /// @param input Vector to be padded
    /// @param length Length to be reached
    void zeroPad(cVector &input, unsigned int length);

    /// @brief Returns the input vector as a complex vector
    /// @param input 
    /// @return 
    cVector toComplexVector(std::vector<double> &input);

    /// @brief Fast linear convolution.
    /// @param a First signal to be convloved
    /// @param b Second signal to be convloved
    /// @return Convolved signal 
    std::vector<double> convolution(std::vector<double> &a,
                                    std::vector<double> &b);

    /// @brief Decimates the signal by a given factor
    /// @param input Signal to be decimated
    /// @param factor Decimation factor. For example factor=2 would
    ///               halve the sample rate.
    /// @return Decimated signal
    std::vector<double> decimate(std::vector<double> &input,
                                 unsigned int factor);
    
    /// @brief Interpolates the signal by a given factor.
    /// @param input Signal to be interpolated
    /// @param factor Interpolation factor
    /// @return Interpolated signal
    std::vector<double> interpolateZeros(std::vector<double> &input,
                                         unsigned int factor);
    
};

#endif