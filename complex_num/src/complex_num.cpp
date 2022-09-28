#include "complex_num.h"

complex_num::complex::complex (double re, double im): 
	re_ {re}, im_ {im} {}

complex_num::complex::complex (const complex_num::complex& other): 
	re_ {other.re_}, im_ {other.im_} {}


complex_num::complex complex_num::complex::operator+ (const complex_num::complex& add)  const 
{
    return complex_num::complex (re_ + add.re_, im_ + add.im_);
}

complex_num::complex complex_num::complex::operator+ (const double add)  const 
{
    return *this + complex_num::complex (add);
}

complex_num::complex complex_num::complex::operator+ () const 
{
    return *this;
}


complex_num::complex complex_num::complex::operator- (const complex_num::complex& sub)  const 
{
    return complex_num::complex (re_ - sub.re_, im_ - sub.im_);
}

complex_num::complex complex_num::complex::operator- (const double sub)  const 
{
    return *this - complex_num::complex (sub);
}

complex_num::complex complex_num::complex::operator- () const 
{
    return complex_num::complex (- re_, - im_);
}


complex_num::complex complex_num::complex::operator* (const complex_num::complex& mul) const 
{
    return complex_num::complex (re_ * mul.re_ - im_ * mul.im_, re_ * mul.im_ + im_ * mul.re_);
}

complex_num::complex complex_num::complex::operator* (const double mul) const 
{
    return *this * complex_num::complex(mul);
}


complex_num::complex complex_num::complex::operator/ (const complex_num::complex& div) const 
{
    double denominator = div.im_ * div.im_ + div.re_ * div.re_;
    double real = (re_ * div.re_ + im_ * div.im_) / denominator;
    double img  = (im_ * div.re_ - re_ * div.im_) / denominator;

    return complex_num::complex (real, img);
}

complex_num::complex complex_num::complex::operator/ (const double div) const
{
    return *this / complex_num::complex (div);
}


complex_num::complex& complex_num::complex::operator= (const complex_num::complex& b) 
{
    re_ = b.re_;
    im_ = b.im_;

    return *this;
}


bool complex_num::complex::operator== (const complex_num::complex& b) const 
{
    return (re_ == b.re_) && (im_ == b.im_);
}

bool complex_num::complex::operator!= (const complex_num::complex& b) const
{
    return !(*this == b);
}


double complex_num::complex::square_abs () const
{
    return re_ * re_ + im_ * im_;
}

double complex_num::complex::abs () const
{
    return sqrt (this->square_abs ());
}


bool complex_num::complex::operator< (const complex_num::complex& b) const 
{ 
    return (this->square_abs ()) < (b.square_abs ());
}

bool complex_num::complex::operator> (const complex_num::complex& b) const 
{
    return (this->square_abs ()) > (b.square_abs ());
}

complex_num::complex complex_num::operator- (const double dbl, const complex_num::complex& cmplx)
{
    return complex_num::complex (dbl) - cmplx;
}

complex_num::complex complex_num::operator+ (const double dbl, const complex_num::complex& cmplx)
{
    return complex (dbl) + cmplx;
}

complex_num::complex operator* (const double dbl, const complex_num::complex& cmplx)
{
    return complex_num::complex (dbl) * cmplx;
}

complex_num::complex operator/ (const double dbl, const complex_num::complex& cmplx)
{
    return complex_num::complex (dbl) / cmplx;
}   

std::ostream& operator<< (std::ostream& os, const complex_num::complex& cmplx)
{
    return os << '(' << cmplx.re_ << ',' << cmplx.im_ << ')' << std::endl;
}
