#pragma once 
#include <quantcpp/LetsBeRational/LetsBeRational.hpp>

namespace quantcpp {

    struct BlackScholes {

        static inline double europeanPrice(double F, double K, double t, double sigma, bool isCall) {

            return LetsBeRational::_getNormalizedPrice(std::log(F/K), sigma * std::sqrt(t), isCall);
        }

        static inline double impliedVolatility(double normalizedPrice, double F, double K, double t, bool isCall) {

            return LetsBeRational::_getNormalizedVolatility(normalizedPrice, std::log(F/K), isCall)/std::sqrt(t);
        }
    };
}