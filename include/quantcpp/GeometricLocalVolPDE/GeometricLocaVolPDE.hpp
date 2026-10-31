#pragma once
#include <Eigen/Dense>
#include <Eigen/Sparse>
#include <quantcpp/MarketDataWrapper/MarketDataWrapper.hpp>

namespace quantcpp {

    struct GeometricLocalVolatilityPDESolver {

        struct TransitionMatrix {

            static Eigen::SparseMatrix<double> implicitMatrix(
                double T, double dx, double dt, size_t M,
                const MarketDataWrapper::LocalVolatilitySurface& localVolatilitySurface,
                const MarketDataWrapper::DiscountFactorTermStructure& discountFactorTermStructure);
            
            static Eigen::SparseMatrix<double> explicitMatrix(
                double T, double dx, double dt, size_t M,
                const MarketDataWrapper::LocalVolatilitySurface& localVolatilitySurface,
                const MarketDataWrapper::DiscountFactorTermStructure& discountFactorTermStructure);

            std::pair<Eigen::SparseMatrix<double>, Eigen::SparseMatrix<double>> crankNicolsonMatrixes(
                double T, double dx, double dt, size_t M,
                const MarketDataWrapper::LocalVolatilitySurface& localVolatilitySurface,
                const MarketDataWrapper::DiscountFactorTermStructure& discountFactorTermStructure);

        };

        struct ImplicitBackwardPricer {

            MarketDataWrapper::ForwardTermStructure forwardTermStructure;
            MarketDataWrapper::DiscountFactorTermStructure discountFactorTermStructure; 
            MarketDataWrapper::LocalVolatilitySurface localVolatilitySurface;
            static constexpr double NUMBER_SIGMA_DEVIATION = 5.0;

            ImplicitBackwardPricer(
                const MarketDataWrapper::ForwardTermStructure& forwardTermStructure_, 
                const MarketDataWrapper::DiscountFactorTermStructure& discountFactorTermStructure_, 
                const MarketDataWrapper::LocalVolatilitySurface& localVolatilitySurface_
            );

            Eigen::MatrixXd europeanVanillaPriceMatrix(double S, double K, double T, bool isCall, size_t N, size_t M) const; 
            //double americanVanillaPrice(double S, double K, double T, bool isCall, size_t N, size_t M) const; 
            //double bermudanVanillaPrice(double S, double K, double T, bool isCall, const std::set<double>& callDates, size_t N, size_t M) const; 
        };

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

            std::pair<Eigen::MatrixXd,Eigen::MatrixXd> europeanVanillaPriceMatrixes(double S, double T, size_t N, size_t M) const; 
            //double americanVanillaPrice(double S, double K, double T, bool isCall, size_t N, size_t M) const; 
            //double bermudanVanillaPrice(double S, double K, double T, bool isCall, const std::set<double>& callDates, size_t N, size_t M) const; 
        };
    };
}