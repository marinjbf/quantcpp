#include <quantcpp/Heston/Heston.hpp>
#include <cassert>

bool isClose(double a, double b, double tol = 1e-3) {return std::abs(a - b) <= tol;}

int main() {

    double S = 100.0;    
    double K = 100.0;    
    double r = 0.05;   
    double q = 0.01;    
    double T = 1.5;     
    double F = S * std::exp((r - q) * T);

    numcpp::GaussLaguerreQuadrature gl(64);
    quantcpp::Heston::GaussLaguerre heston{0.05,0.05,0.45,.3,2.0,gl};
    double expectedHestonPrice = 13.2561; 
    double x = std::log(F/K);
    double modelHestonPrice = heston.europeanPrice(x,T,true)*std::exp(-r*T)*sqrt(F*K);
    assert(isClose(modelHestonPrice, expectedHestonPrice, 1e-4));
    return 0;
}