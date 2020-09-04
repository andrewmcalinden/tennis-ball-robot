// from http://www.pcs.cnu.edu/~bbradie/cpp/interpdriver.txt

double neville ( int, double*, double*, double , double *wrk);
double* divdiff ( int, double*, double* );
double nf_eval ( int, double*, double*, double );
void cubic_nak ( int, double*, double*, double*, double*, double* );
void cubic_clamped ( int, double*, double*, double*, double*,
                     double*, double, double );
double spline_eval ( int, double*, double*, double*, double*,
                     double*, double );
