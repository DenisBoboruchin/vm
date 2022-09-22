#include "include/complex_num.h"

int main ()
{
    complex_num::complex d (1, 2);

    complex_num::complex c = d;

    printf ("re: %lf\nim: %lf", c.re_, c.im_);

    return 0;
}
