#pragma once

#include <iostream>

namespace complex_num
{

struct complex
{
    double re_ = 0;
    double im_ = 0;

    complex (double re = 0.0, double im = 0.0);
    complex (const complex& other);

    complex operator+ (const complex& add) const;
    complex operator+ (const double   add) const;
    complex operator+ () const;

    complex operator- (const complex& sub)  const;
    complex operator- (const double   sub)  const;
    complex operator- () const;
    
    complex operator* (const complex& mul) const;
    complex operator* (const double mul) const; 
    
    complex operator/ (const complex& div) const; 
    complex operator/ (const double div) const;

    complex& operator= (const complex& b); 
        
    bool operator== (const complex& b) const;
    bool operator!= (const complex& b) const;
    
    bool operator< (const complex& b) const;
    bool operator> (const complex& b) const;
};

complex operator- (const double dbl, const complex& cmplx);
complex operator+ (const double dbl, const complex& cmplx);

complex operator* (const double dbl, const complex& cmplx);
complex operator/ (const double dbl, const complex& cmplx);

std::ostream& operator<< (std::ostream& os, const complex& cmplx);

}
