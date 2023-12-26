#include "include/Math.hh"
#include <stdexcept>
#include <iostream>

std::vector<double> Math::multiplyElementWise(std::vector<double> &a,
                                              std::vector<double> &b)
{
    if (a.size() != b.size())
    {        
        throw std::invalid_argument("vectors must be the same length");
    }
    
    std::vector<double> output(a.size());
    
    for (unsigned int i = 0; i < a.size(); i++)
    {
        output[i] = a[i] * b[i];
    }

    return output;
}


cVector Math::multiplyElementWise(cVector &a, cVector &b)
{
    if (a.size() != b.size())
    {
        throw std::invalid_argument("Vectors must be the same length");
    }
    
    cVector output(a.size());
    
    for (unsigned int i = 0; i < a.size(); i++)
    {
        output[i] = a[i] * b[i];
    }
    
    return output;
}

double Math::sinc(double x)
{
    return sin(x)/x;
}

double Math::sinc(double x, double x0)
{
    if (x == 0) { return x0; }
    return sin(x)/x;
}

double Math::sinc(double x, double x0, bool normalize)
{
    if (x == 0) { return x0; }
    if (normalize) {return sin(x*M_PI)/x*M_PI;}
    return sin(x)/x;
}

double Math::sinc(double x, bool normalize)
{
    if (normalize) {return sin(x*M_PI)/x*M_PI;}
    return sin(x)/x;
}