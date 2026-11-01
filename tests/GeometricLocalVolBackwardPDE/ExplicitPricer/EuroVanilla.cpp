#include <quantcpp/GeometricLocalVolBackwardPDE/GeometricLocalVolBackwardPDE.hpp>
#include <quantcpp/BlackScholes/BlackSholes.hpp>
#include <iostream>

void europeanFlatSigma() {

    using namespace quantcpp;

    double S = 100.0; 
    double r = 0.001;
    double mu = r - .11;
    double T = 1.0;
    double F = S*std::exp(mu*T); 
    double K = 100.0;
    double sigma = 0.16; 
    bool isCall = true;
    size_t N = 252; 
    size_t M = 79; 

    double bsPrice = BlackScholes::europeanPrice(F, K, T, sigma,isCall)*std::exp(-r*T);

    MarketDataWrapper::DiscountFactorTermStructure discountTermStructure = [r](double t) {return std::exp(-r*t);};
    MarketDataWrapper::LocalVolatilitySurface localVolatilitySurface = [sigma](double k, double t) {return sigma;};
    MarketDataWrapper::ForwardTermStructure forwardTermStructure = [mu,S](double t) {return S*std::exp(mu*t);};
    GeometricLocalVolatilityBackwardPDE::ImplicitPricer implicitPricer(forwardTermStructure,discountTermStructure,localVolatilitySurface);
    
    auto t1 = std::chrono::high_resolution_clock::now();

    Eigen::MatrixXd pdePrice = implicitPricer.europeanVanillaPriceMatrix(S, K, T, isCall,N, M);

    auto t2 = std::chrono::high_resolution_clock::now();
    auto ms_int = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);

    std::cout << "Closed Form Price: " << bsPrice << std::endl;
    std::cout << "BS PDE Price: " << pdePrice.col(0)(M) << std::endl;
    std::cout << "Time taken for solving BS PDE: " << ms_int.count() << "ms\n";

}

int main() {

    europeanFlatSigma(); 
    return 0;
}