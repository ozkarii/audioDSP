#include "FIR.hh"

/// @brief Design FIR filter using hamming window, at the cutoff frequency
///        the magnitude response will be -6dB
/// @param cutoff normalized cutoff frequency with respect to sample rate
/// @param transitionWidth normalized width of the transition band 
///                        (with respect to sample rate)
/// @param type desired filter type
/// @return impulse response of the filter
/// 
std::vector<double> FIR::designHamming(double cutoff, double transitionWidth,
                                       FIR::FilterType type)
{
    if (type == LowPass)
    {
        // Calculate the order of the filter
        int N = static_cast<int>(3.3 / transitionWidth);
        if (N % 2 == 0) {N++;}

        std::vector<double> h(N), w(N);
        double x;
        // Calculate the ideal impulse response (sinc function)
        for (int n = (-1)*(N-1)/2; n < (N-1)/2; ++n)
        {
            x = n*2.0*M_PI*cutoff;
            h[n + (N-1)/2] = 2.0*cutoff*Math::sinc(x, 1.0);
        }
        
        // Calculate the Hamming window
        for (int n = 0; n < N; ++n)
        {
            w[n] = 0.54 - 0.46 * std::cos((2.0 * M_PI * n) / N);
        }

        // Apply the window to the impulse response
        for (int n = 0; n < N; ++n)
        {
            h[n] *= w[n];
        }

        return h;
    }

    if (type == FIR::LowPass)
    {
        return std::vector<double>();
    }

    if (type == FIR::BandPass)
    {
        return std::vector<double>();
    }

    if (type == FIR::BandStop)
    {
        return std::vector<double>();
    }

    return std::vector<double>();
}

