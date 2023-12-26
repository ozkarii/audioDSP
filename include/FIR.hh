#ifndef FIR_HH
#define FIR_HH

#include "Math.hh"
#include "DSP.hh"

namespace FIR
{
    enum FilterType {LowPass, HighPass, BandPass, BandStop};
    
    // normalized freqs
    std::vector<double> designHamming(double cutoff, double transitionWidth,
                                      FilterType type);
    
};

#endif
