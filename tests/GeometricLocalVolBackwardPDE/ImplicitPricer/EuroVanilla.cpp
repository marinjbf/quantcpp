#include <quantcpp/GeometricLocalVolBackwardPDE/GeometricLocalVolBackwardPDE.hpp>
#include <quantcpp/SSVI/SSVI.hpp>
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
    bool isCall = false;
    size_t N = 200; 
    size_t M = 75; 

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

void europeanLocalVolatility() {

    using namespace quantcpp;
    quantcpp::SSVIPowerLaw ssvi(-0.5,0.46,0.77,1.0); 

    double mu = .05;
    double r = 0.01; 
    double T = 2.0;
    double S = 100.0;
    double F = S*std::exp(mu*T);
    double K = 100.0; 
    double x = std::log(F/K); 
    int N = 200; 
    int M = 75; 
    bool isCall = false;

    MarketDataWrapper::DiscountFactorTermStructure discountTermStructure = [r](double t) {return std::exp(-r*t);};
    MarketDataWrapper::LocalVolatilitySurface localVolatilitySurface = [ssvi](double k, double t) {return std::sqrt(ssvi.localVariance(k, t));};
    MarketDataWrapper::ForwardTermStructure forwardTermStructure = [S,mu](double t) {return S*std::exp(mu*t);};
    GeometricLocalVolatilityBackwardPDE::ImplicitPricer implicitPricer(forwardTermStructure,discountTermStructure,localVolatilitySurface);

    auto t1 = std::chrono::high_resolution_clock::now();

    Eigen::MatrixXd pdePrices = implicitPricer.europeanVanillaPriceMatrix(S, K, T, isCall,N, M);

    auto t2 = std::chrono::high_resolution_clock::now();
    auto ms_int = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);

    std::cout << "Closed Form Price: " << ssvi.normalizedPrice(x, T, isCall)*std::sqrt(F*K)*std::exp(-r*T) << std::endl;
    std::cout << "Local Vol PDE Price: " << pdePrices.col(0)(M) << std::endl;
    std::cout << "Time taken for solving Local-Vol PDE: " << ms_int.count() << "ms\n";
  
}

int main() {

    europeanFlatSigma();
    europeanLocalVolatility();
    return 0;
}