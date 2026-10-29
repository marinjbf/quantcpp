#include <cassert>
#include <quantcpp/BlackScholes/BlackSholes.hpp>

bool isClose(double a, double b, double tol = 1e-3) {return std::abs(a - b) <= tol;}

void initialTestBlackScholes() {
    
    using namespace quantcpp;

    double S = 100.0;   
    double K = 100.0;    
    double r = 0.05;     
    double q = 0.02;     
    double sigma = 0.20;
    double T = 2.0;     

    double callPrice = 13.5218;
    double putPrice = 7.9266;

    double F = S*std::exp((r-q)*T);
    double x = std::log(F/K); 
    double normalizedSigma = sigma*sqrt(T);
    double modelCallPrice = BlackScholes::europeanPrice(F,K,T,sigma, true)*std::exp(-r*T)*std::sqrt(F*K);
    double modelPutPrice = BlackScholes::europeanPrice(F,K,T,sigma, false)*std::exp(-r*T)*std::sqrt(F*K);
    double impliedVolPut = BlackScholes::impliedVolatility(modelPutPrice*std::exp(r*T)/std::sqrt(F*K),F,K,T,false);
    double impliedVolCall = BlackScholes::impliedVolatility(modelCallPrice*std::exp(r*T)/std::sqrt(F*K),F, K, T, true);
    assert(isClose(modelCallPrice, callPrice, 1e-4));
    assert(isClose(modelPutPrice, putPrice, 1e-4));
    assert(isClose(impliedVolPut, .2, 1e-3));
    assert(isClose(impliedVolCall, .2, 1e-3));

}

int main() {

    initialTestBlackScholes();
    return 0;
}