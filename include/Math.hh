#include <cmath>
#include <vector>
#include <complex>

using cVector = std::vector<std::complex<double>>;

namespace Math {

    std::vector<double> multiplyElementWise(std::vector<double> &a,
                                            std::vector<double> &b);
    
    cVector multiplyElementWise(cVector &a, cVector &b);

    double sinc(double input);

    double sinc(double input, double x0);

    double sinc(double input, double x0, bool normalize);

    double sinc(double x, bool normalize);

};