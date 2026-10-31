#pragma once 
#include <quantcpp/LetsBeRational/LetsBeRational.hpp>
#include <numcpp/UnivariateDistributions/Normal.hpp>

namespace quantcpp {

    struct BlackScholes {

        static inline double europeanPrice(double F, double K, double t, double sigma, bool isCall) {

            return LetsBeRational::_getNormalizedPrice(std::log(F/K), sigma * std::sqrt(t), isCall)*std::sqrt(F*K);
        }

        static inline double impliedVolatility(double normalizedPrice, double F, double K, double t, bool isCall) {

            return LetsBeRational::_getNormalizedVolatility(normalizedPrice, std::log(F/K), isCall)/std::sqrt(t);
        }

        static double europeanDelta(double F, double mu, double K, double t, double sigma, double r, bool isCall) {

            int putCallFlag = isCall ? 1 : -1; 
            double d1 = (std::log(F / K) + 0.5 * sigma * sigma * t) / (sigma * std::sqrt(t)); 
            return std::exp(-t*r)*putCallFlag*exp(mu*t)*numcpp::NormalDistribution{}.cdf(putCallFlag*d1);
        }

        static double europeanGamma(double F, double mu, double K, double t, double sigma, double r, bool isCall) {

            double d1 = (std::log(F / K) + 0.5 * sigma * sigma * t) / (sigma * std::sqrt(t)); 
            double driftSq = exp(mu*t)*std::exp(mu*t);
            return std::exp(-t*r)*driftSq*numcpp::NormalDistribution{}.pdf(d1)/(F*sigma*std::sqrt(t));
        }

        static double europeanVega(double F, double K, double t, double sigma, double r, bool isCall) {

            double d1 = (std::log(F / K) + 0.5 * sigma * sigma * t) / (sigma * std::sqrt(t)); 
            return F*std::exp(-t*r)*numcpp::NormalDistribution{}.pdf(d1)*std::sqrt(t);
        }
    };
}