// define to enable AD
//#define CPPAD

// define to enable ADOL-C
#define ADOLC

// define for plain computation
//#define PLAIN

#include <iostream>
#include <vector>
#include <cmath>

#ifdef CPPAD
#include <cppad/cppad.hpp>
using CppAD::AD;
typedef AD<double> dbl;
#endif

#ifdef ADOLC
#include <adolc/adolc.h>
typedef adouble dbl;
#endif

#ifdef PLAIN
typedef double dbl;
#endif

// problem data
const dbl S0 = std::log(100.0);
const double T = 10.0;
const dbl K = std::log(120.0);
const unsigned int n = 500; // sigma grid

// PDE parameters
const dbl Smin = 1.07555172964;
const dbl Smax = 8.13478864234;
const unsigned int sizeS = 2 * 50 + 1;
const unsigned int sizeT = 500 * 10;

// solution grid
dbl loc[sizeS + 1], c[2][sizeS], exerciseValue[sizeS];

int main() {

#ifdef PLAIN
    std::vector<dbl> implVol(n, 0.20);
#endif

#ifdef CPPAD
    std::vector<dbl> implVol(n, 0.20);
    CppAD::Independent(implVol);
#endif

#ifdef ADOLC
    int tag = 1, keep = 1;
    adouble *implVol;
    implVol = new adouble[n];
    trace_on(tag, keep);
    for (unsigned int i = 0; i < n; ++i)
        implVol[i] <<= 0.20;
#endif

    unsigned int swap = 0;

    // initial values
    const dbl h = (Smax - Smin) / static_cast<dbl>(sizeS - 1);
    const dbl hq = h * h;
    for (unsigned int j = 0; j < sizeS; ++j) {
        loc[j] = Smin + h * static_cast<double>(j);
        c[swap][j] = exerciseValue[j] =
            std::max<dbl>(exp(loc[j]) - exp(K), 0.0);
    }

    // PDE solver
    const double dt = T / static_cast<double>(sizeT);
    for (unsigned int i = 0; i < sizeT; ++i) {
        // rollback
        for (unsigned int j = 0; j < sizeS; ++j) {
            const dbl v = implVol[static_cast<int>(static_cast<double>(i) *
                                                   static_cast<double>(n) /
                                                   static_cast<double>(sizeT))];
            dbl d1, d2;
            if (j == 0 || j == sizeS - 1) {
                d2 = 0.0;
            } else {
                d2 = (c[swap][j + 1] - 2.0 * c[swap][j] + c[swap][j - 1]) / hq;
            }
            if (j == 0) {
                d1 = (c[swap][j + 1] - c[swap][j]) / h;
            } else {
                if (j == sizeS - 1) {
                    d1 = (c[swap][j] - c[swap][j - 1]) / h;
                } else {
                    d1 = (c[swap][j + 1] - c[swap][j - 1]) / (2.0 * h);
                }
            }
            // Euler
            c[1 - swap][j] = c[swap][j] + 0.5 * dt * v * v * (d2 - d1);
        }
        // update prices
        for (unsigned int j = 0; j < sizeS; ++j) {
            c[1 - swap][j] = std::max(c[1 - swap][j], exerciseValue[j]);
        }
        swap = 1 - swap;
    }

    // solution output
    std::clog.precision(12);
    std::clog << "c(0,0) = " << c[swap][(sizeS - 1) / 2] << std::endl;

#ifdef CPPAD
    std::vector<dbl> y(1);
    y[0] = c[swap][(sizeS - 1) / 2];
    CppAD::ADFun<double> f(implVol, y);
    std::vector<double> w(1, 1.0);
    std::vector<double> vega(n - 1);
    vega = f.Reverse(1, w);
    double sum = 0.0;
    for (unsigned int i = 0; i < n - 1; ++i) {
        sum += vega[i];
    }
    // std::vector<double> x0(n - 1, 1.0);
    // sum = f.Forward(1,x0);
    std::clog << "vega =" << sum << std::endl;
#endif

#ifdef ADOLC
    double yout;
    c[swap][(sizeS - 1) / 2] >>= yout;
    trace_off();
    double u[1];
    u[0] = 1.0;
    double *vega = new double[n];
    reverse(tag, 1, n, 0, u, vega);
    double sum = 0.0;
    for (unsigned int i = 0; i < n; ++i) {
        sum += vega[i];
    }
    std::clog << "vega =" << sum << std::endl;
    delete[] implVol;
    delete[] vega;
#endif

} // main
