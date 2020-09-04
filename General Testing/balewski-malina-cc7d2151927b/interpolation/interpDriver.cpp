#include <iostream>
#include "interp.h"
using namespace std;

/* to compile on MAC:

c++ interp.cpp interpDriver.cpp -o interp

 */

//taken from : http://www.pcs.cnu.edu/~bbradie/cpp/interpdriver.txt

int main ()
{
     double *x,
            *f,
            *b,
            *c,
            *d,
            *coeff;
     int n, i;       
     
     n = 9;
     x = new double [n];
     f = new double [n];
     b = new double [n];
     c = new double [n];
     d = new double [n];

     // jan's addition, to save time for multiple invocations
     double *wrk = new double [n];
     

     x[0] = 300.0;   x[1] = 320.0;   x[2] = 340.0;   x[3] = 360.0;
     x[4] = 380.0;   x[5] = 400.0;   x[6] = 450.0;   x[7] = 500.0;
     x[8] = 550.0;
     f[0] = 0.851;   f[1] = 0.872;   f[2] = 0.891;   f[3] = 0.908;
     f[4] = 0.926;   f[5] = 0.942;   f[6] = 0.981;   f[7] = 1.02;
     f[8] = 1.05;

     cout << "USING NEVILLE's ALGORITHM" << endl;
     cout << "x = 510" << '\t' << neville ( n, x, f, 510.0, wrk ) << endl;
     cout << endl;
     
     
     coeff = divdiff ( n, x, f );
     cout << "COEFFICIENTS OF NEWTON FORM OF THE INTERPOLATING POLYNOMIAL" << endl;
     for ( i = 0; i < n; i++ )
         cout << coeff[i] << endl;
     cout << endl;

     cout << "VALUES FROM NEWTON FORM OF THE INTERPOLATING POLYNOMIAL" << endl;
     cout << "x = 340" << '\t' << nf_eval ( n, x, coeff, 340.0 ) << endl;
     cout << "x = 510" << '\t' << nf_eval ( n, x, coeff, 510.0 ) << endl;
     cout << "x = 385" << '\t' << nf_eval ( n, x, coeff, 385.0 ) << endl;
     cout << "x = 475" << '\t' << nf_eval ( n, x, coeff, 475.0 ) << endl;
     cout << endl;
   
   
     cubic_nak ( n, x, f, b, c, d );
     cout << "NOT-A-KNOT CUBIC SPLINE COEFFICIENSTS" << endl;
     for ( i = 0; i < n-1; i++ )
         cout << f[i] << '\t' << b[i] << '\t' << c[i] << '\t' << d[i] << endl; 
     cout << endl;
     
     cout << "VALUES FROM NOT-A-KNOT CUBIC SPLINE" << endl;
     cout << "x = 340" << '\t' << spline_eval ( n, x, f, b, c, d, 340.0 ) << endl;
     cout << "x = 510" << '\t' << spline_eval ( n, x, f, b, c, d, 510.0 ) << endl;
     cout << "x = 385" << '\t' << spline_eval ( n, x, f, b, c, d, 385.0 ) << endl;
     cout << "x = 475" << '\t' << spline_eval ( n, x, f, b, c, d, 475.0 ) << endl;
}


/*   test OUTPUT 

USING NEVILLE's ALGORITHM
x = 510 1.00092

COEFFICIENTS OF NEWTON FORM OF THE INTERPOLATING POLYNOMIAL
0.851
0.00105
-2.5e-06
0
7.8125e-10
-2.34375e-11
2.76986e-13
-2.05303e-15
1.10602e-17

VALUES FROM NEWTON FORM OF THE INTERPOLATING POLYNOMIAL
x = 340 0.891
x = 510 1.00092
x = 385 0.930335
x = 475 1.01463

NOT-A-KNOT CUBIC SPLINE COEFFICIENSTS
0.851   0.00107795      -8.46308e-07    -2.75615e-08
0.872   0.00101102      -2.5e-06        -2.75615e-08
0.891   0.000877951     -4.15369e-06    1.37808e-07
0.908   0.000877172     4.11477e-06     -1.48669e-07
0.926   0.00086336      -4.80537e-06    8.18683e-08
0.942   0.000769387     1.06725e-07     2.11062e-09
0.981   0.000795889     4.23319e-07     -1.48221e-08
1.02    0.000727055     -1.8e-06        -1.48221e-08

VALUES FROM NOT-A-KNOT CUBIC SPLINE
x = 340 0.891
x = 510 1.02708
x = 385 0.930207
x = 475 1.00093
*/
