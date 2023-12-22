#include <cmath>
#include <vector>
#include <complex>

using cVector = std::vector<std::complex<double>>;

namespace Math {

    std::vector<double> multiplyElementWise(std::vector<double> &a,
                                            std::vector<double> &b);
    
    cVector multiplyElementWise(cVector &a, cVector &b);

};