#pragma once 
#include <quantcpp/GeometricLocalVolBackwardPDE/GeometricLocalVolBackwardPDE.hpp>

namespace quantcpp {

    struct GeometricLocalVolatilityForwardPDE {

        struct ExplicitForwardPricer {

            MarketDataWrapper::ForwardTermStructure forwardTermStructure;
            MarketDataWrapper::DiscountFactorTermStructure discountFactorTermStructure; 
            MarketDataWrapper::LocalVolatilitySurface localVolatilitySurface;
            static constexpr double NUMBER_SIGMA_DEVIATION = 5.0;

            ExplicitForwardPricer(
                const MarketDataWrapper::ForwardTermStructure& forwardTermStructure_, 
                const MarketDataWrapper::DiscountFactorTermStructure& discountFactorTermStructure_, 
                const MarketDataWrapper::LocalVolatilitySurface& localVolatilitySurface_
            );

            std::pair<Eigen::MatrixXd,Eigen::MatrixXd> europeanVanillaMatrixes(double S, double T, size_t N, size_t M) const; 
            //double americanVanillaPrice(double S, double K, double T, bool isCall, size_t N, size_t M) const; 
            //double bermudanVanillaPrice(double S, double K, double T, bool isCall, const std::set<double>& callDates, size_t N, size_t M) const; 
        };
    };
}