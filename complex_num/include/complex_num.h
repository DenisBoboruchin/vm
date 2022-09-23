#pragma once

#include <iostream>

namespace complex_num
{

struct complex
{
    double re_ = 0;
    double im_ = 0;

    //complex () {}
    //complex (double re = 0.0): re_ {re} {}
    complex (double re = 0.0, double im = 0.0): re_ {re}, im_ {im} {}
    complex (const complex& other): re_ {other.re_}, im_ {other.im_} {}

    complex operator+ (const complex& add)  const {return complex (re_ + add.re_, im_ + add.im_);}
    complex operator+ (const double   add)  const {return *this + complex (add);}
    complex operator+ ()                    const {return *this;}
    friend complex operator+ (const double dbl, const complex& cmplx) {
        return complex (dbl) + cmplx;}

    complex operator- (const complex& sub)  const {return complex (re_ - sub.re_, im_ - sub.im_);}
    complex operator- (const double   sub)  const {return *this - complex (sub);}
    complex operator- ()                    const {return complex (- re_, - im_);}
    friend complex operator- (const double dbl, const complex& cmplx) {
        return complex (dbl) - cmplx;}
    
    complex operator* (const complex& mul) const {
        return complex (re_ * mul.re_ - im_ * mul.im_, re_ * mul.im_ + im_ * mul.re_);}

    complex operator* (const double mul) const {return (*this * complex(mul));}

    complex operator/ (const complex& div) const 
    {
        double denominator = div.im_ * div.im_ + div.re_ * div.re_;
        double real = (re_ * div.re_ + im_ * div.im_) / denominator;
        double img  = (im_ * div.re_ - re_ * div.im_) / denominator;

        return complex (real, img);
    }

    complex& operator=   (const complex& b) 
    {
        re_ = b.re_;
        im_ = b.im_;

        return *this;
    }
    
    bool    operator==  (const complex& b) const {return ((re_ == b.re_) && (im_ == b.im_));}
    bool    operator!=  (const complex& b) const {return !(*this == b);}
    
    bool    operator<   (const complex& b) const { 
        return (re_ * re_ + im_ * im_) < (b.re_ * b.re_ + b.im_ * b.im_);}

    bool    operator>   (const complex& b) const {
        return (re_ * re_ + im_ * im_) > (b.re_ * b.re_ + b.im_ * b.im_);}

    friend std::ostream& operator<< (std::ostream& os, const complex& cmplx){
        return os << '(' << cmplx.re_ << ',' << cmplx.im_ << ')' << std::endl;}
};

}
