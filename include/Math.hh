#include <cmath>
#include <vector>
#include <complex>

using cVector = std::vector<std::complex<double>>;

namespace Math {

    /// @brief Takes two equal length vectors and multiplies them element wise.
    /// @param a vector 1
    /// @param b vector 2
    /// @return element wise product vector
    std::vector<double> multiplyElementWise(std::vector<double> &a,
                                            std::vector<double> &b);
    
    /// @brief Takes two equal length vectors and multiplies them element wise.
    /// @param a vector 1
    /// @param b vector 2
    /// @return element wise product vector
    cVector multiplyElementWise(cVector &a, cVector &b);


    /// @brief sin(x)/x
    /// @param input
    /// @return sinc of input
    double sinc(double input);

    /// @brief sin(x)/x
    /// @param input
    /// @param x0 output when input equals zero
    /// @return sinc of input
    double sinc(double input, double x0);

    /// @brief sin(x)/x
    /// @param input
    /// @param x0 output when input equals zero
    /// @param normalize wheter or not to normalize by multiplying input by pi
    /// @return sinc of input
    double sinc(double input, double x0, bool normalize);
    
};
