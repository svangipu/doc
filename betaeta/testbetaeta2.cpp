#include <ql/quantlib.hpp>

#include <iostream>

using namespace QuantLib;

int main() {

    Array times(0);
    Array alpha(1, 0.05);
    Array kappa(1, 0.00);

    Real eta = atof(getenv("ETA"));

    BetaEtaCore core(times, alpha, kappa, 1.0, eta);

    Real u0 = 0.000001;
    while (u0 < 10.0) {
        Real v = 0.0;
        while (v < 10.0) {
            std::cout << u0 << " " << v << " " << core.M_tabulated(u0,v) << " " << core.M(u0,v) << std::endl;
            v += 0.01;
        }
        std::cout << std::endl;
        u0 += 0.1;
    }

    return 0;
}
