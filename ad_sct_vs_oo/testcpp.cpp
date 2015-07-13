//#define ADACTIVE
#undef ADACTIVE

#include <iostream>
#include <vector>

#ifdef ADACTIVE
#include <cppad/cppad.hpp>
using CppAD::AD;
typedef AD<double> dbl;
#else
typedef double dbl;
#endif

// problem data
const dbl S0 = 100.0;
const double T = 10.0;
const dbl K = 100.0;

// PDE parameters
const dbl Smin = 0.0;
const dbl Smax = 200.0;
const unsigned int sizeS = 2 * 50 + 1;
const unsigned int sizeT = static_cast<int>(T * 500.0 + 1.0);

// local volatility function
dbl volatility(const double t, const dbl S, const dbl implVol) {
    return implVol * S;
}

// solution grid
dbl loc[sizeS + 1], c[2][sizeS + 1], exerciseValue[sizeS + 1];

int main() {

    std::vector<dbl> implVol(1, 0.20);

#ifdef ADACTIVE
    CppAD::Independent(implVol);
#endif

    unsigned int swap = 0;

    // initial values
    const dbl h = (Smax - Smin) / static_cast<dbl>(sizeS - 1);
    const dbl hq = h * h;
    for (unsigned int j = 0; j < sizeS; ++j) {
        loc[j] = Smin + h * static_cast<double>(j);
        c[swap][j] = exerciseValue[j] = std::max<dbl>(loc[j] - K, 0.0);
    }

    // PDE solver
    const double dt = T / static_cast<double>(sizeT);
    const dbl r = dt / hq;
    for (unsigned int i = 0; i <= sizeT; ++i) {
        const double t = T - static_cast<double>(i) * dt;
        // rollback
        for (unsigned int j = 0; j < sizeS; ++j) {
            const dbl v = volatility(t, loc[j], implVol[0]);
            dbl d;
            if (j == 0 || j == sizeS - 1) {
                d = 0.0;
            } else {
                d = (c[swap][j + 1] - 2.0 * c[swap][j] + c[swap][j - 1]);
            }
            // Euler
            c[1 - swap][j] = c[swap][j] + r * d * 0.5 * v * v;
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

#ifdef ADACTIVE
    std::vector<dbl> y(1);
    y[0] = c[swap][(sizeS-1)/2];
    CppAD::ADFun<double> f(implVol,y);
    std::vector<double> w(1,1.0);
    std::vector<double> vega(1);
    vega = f.Reverse(1,w);
    std::clog << "vega = " << vega[0] << std::endl;
#endif

} // main
