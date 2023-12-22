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
        output.at(i) = a.at(i) * b.at(i);
    }

    return output;
}


cVector Math::multiplyElementWise(cVector &a, cVector &b)
{
    if (a.size() != b.size())
    {
        std::cout << a.size() << " " << b.size() << std::endl;
        throw std::invalid_argument("Vectors must be the same length");
    }
    
    cVector output(a.size());
    
    for (unsigned int i = 0; i < a.size(); i++)
    {
        output.at(i) = a.at(i) * b.at(i);
    }
    
    return output;
}