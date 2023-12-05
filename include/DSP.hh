#include <vector>
#include <complex>
#include <cmath>

using cVector = std::vector<std::complex<double>>;

namespace DSP
{
    std::vector<float> convolution(const std::vector<float> &sound,
                                   const std::vector<float> &ir);
    
    cVector fft(cVector &input);

    void zeroPad(cVector &input);

    cVector toComplexVector(std::vector<double> &input)
    {
        cVector result(input.size());

        for (int i = 0; i < input.size(); i++)
        {
            result[i] = std::complex<double>(input[i], 0);
        }

        return result;
    }

};