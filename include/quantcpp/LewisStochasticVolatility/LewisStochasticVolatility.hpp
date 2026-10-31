#pragma once 
#include <functional>
#include <numcpp/Quadratures/GaussLaguerre.hpp>
#include <quantcpp/LetsBeRational/LetsBeRational.hpp>

namespace quantcpp {

    struct LewisStochasticVolatility {
    
        using CharacteristicFunction = std::function<std::complex<double>(std::complex<double>)> ;

        static constexpr double LAGUERRE_WEIGHT_MIN = 1e-20;
        static constexpr double INTEGRAND_REAL_PART_MIN = 1e-20;

        struct GaussLaguerre {

            static double europeanPrice(double x, bool isCall, const CharacteristicFunction& characteristicFunction, const numcpp::GaussLaguerreQuadrature& gaussLaguerreQuadratures) {

                size_t n = gaussLaguerreQuadratures.size();
                double sum = 0.0, u, w;
                std::complex<double> integrand;
                std::complex<double> i(0.0, 1.0);
                for (size_t j = 0; j < n; ++j) {
                    
                    u = gaussLaguerreQuadratures.roots[j]; w = gaussLaguerreQuadratures.weights[j];
                    integrand = std::exp(i * u * x) * characteristicFunction(std::complex<double>(u, -0.5));
                    if (abs(integrand.real()) < INTEGRAND_REAL_PART_MIN or abs(w)< LAGUERRE_WEIGHT_MIN) {break;}
                    else {sum += w * std::exp(u) * integrand.real() / (u * u + 0.25);}
                    
                }
                double call = std::exp(x / 2.0) - sum / LetsBeRational::PI;
                return isCall ? call : call - LetsBeRational::_getNormalizedIntrisicValue(x, true) + LetsBeRational::_getNormalizedIntrisicValue(x, false);
            }

            static double impliedTotalVariance(double x, const CharacteristicFunction& characteristicFunction, const numcpp::GaussLaguerreQuadrature& gaussLaguerreQuadratures) {

                double price = europeanPrice(x,true, characteristicFunction,gaussLaguerreQuadratures);
                double normalizedSigma = LetsBeRational::_getNormalizedVolatility(true, x, true);
                return normalizedSigma*normalizedSigma;
            }

            static double impliedDensity(double x, const CharacteristicFunction& characteristicFunction, const numcpp::GaussLaguerreQuadrature& gaussLaguerreQuadratures) {
                
                size_t n = gaussLaguerreQuadratures.size();
                double sum = 0.0, u, w;
                std::complex<double> integrand;
                std::complex<double> i(0.0, 1.0);
                for (size_t j = 0; j < n; ++j) {
                    
                    u = gaussLaguerreQuadratures.roots[j]; w = gaussLaguerreQuadratures.weights[j];
                    integrand = std::exp(-i * u * x) * characteristicFunction(std::complex<double>(u, 0.0));
                    if (abs(integrand.real()) < INTEGRAND_REAL_PART_MIN or abs(w)< LAGUERRE_WEIGHT_MIN) {break;}
                    else {sum += w * std::exp(u) * integrand.real();}
                }
                return sum / LetsBeRational::PI;
            }
        };

    };

}