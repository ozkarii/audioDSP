#ifndef FIR_HH
#define FIR_HH

#include "Math.hh"
#include "DSP.hh"

namespace FIR
{
    enum FilterType {LowPass, HighPass, BandPass, BandStop};
    
    /// @brief Design FIR filter using hamming window, at the cutoff frequency
    ///        the magnitude response will be -6dB
    /// @param cutoff normalized cutoff frequency with respect to sample rate
    /// @param transitionWidth normalized width of the transition band 
    ///                        (with respect to sample rate)
    /// @param type desired filter type
    /// @return impulse response of the filter
    std::vector<double> designHamming(double cutoff, double transitionWidth,
                                      FilterType type);
    
};

#endif
