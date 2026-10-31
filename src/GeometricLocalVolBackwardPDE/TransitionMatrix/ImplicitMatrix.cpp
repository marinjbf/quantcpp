#include <quantcpp/GeometricLocalVolBackwardPDE/GeometricLocalVolBackwardPDE.hpp>

namespace quantcpp {

    Eigen::SparseMatrix<double> GeometricLocalVolatilityBackwardPDE::TransitionMatrix::implicitMatrix(
            double T, double dx, double dt, size_t M,
            const MarketDataWrapper::LocalVolatilitySurface& localVolatilitySurface,
            const MarketDataWrapper::DiscountFactorTermStructure& discountFactorTermStructure) {

        Eigen::SparseMatrix<double> A(2*M+1, 2*M+1);
        std::vector<Eigen::Triplet<double>> coefs;
        double sigma = MarketDataWrapper::localVolatility(0.0,T, localVolatilitySurface);
        double rfr = MarketDataWrapper::forwardDiscountFactor(T, T+dt,discountFactorTermStructure);
        double mid = rfr + sigma*sigma*dt/(dx*dx); 
        double up = -.5*sigma*sigma*dt/(dx*dx) - .5*(0.0 - .5*sigma*sigma)*dt/dx; 
        double down = -.5*sigma*sigma*dt/(dx*dx) + .5*(0.0 - .5*sigma*sigma)*dt/dx; 

        coefs.push_back({Eigen::Triplet<double>(M,M-1,up)});
        coefs.push_back({Eigen::Triplet<double>(M,M,mid)});
        coefs.push_back({Eigen::Triplet<double>(M,M+1,down)});


        for (size_t i = 1; i<=M; i++) {

            sigma = MarketDataWrapper::localVolatility(-double(i)*dx,T, localVolatilitySurface);
            mid = rfr + sigma*sigma*dt/(dx*dx); 
            up = -.5*sigma*sigma*dt/(dx*dx) - .5*(0.0 - .5*sigma*sigma)*dt/dx; 
            down = -.5*sigma*sigma*dt/(dx*dx) + .5*(0.0 - .5*sigma*sigma)*dt/dx; 
            
            if (M-i == 0) {

                coefs.push_back({Eigen::Triplet<double>(0,0,2*up)});
                coefs.push_back({Eigen::Triplet<double>(0,1,2*mid-up)});
                coefs.push_back({Eigen::Triplet<double>(0,2,2*down-mid)});
                coefs.push_back({Eigen::Triplet<double>(0,3,-down)});
                coefs.push_back({Eigen::Triplet<double>(2*M,2*M,rfr)});

            } else {

                coefs.push_back({Eigen::Triplet<double>(M-i,M-i-1,up)});
                coefs.push_back({Eigen::Triplet<double>(M-i,M-i,mid)});
                coefs.push_back({Eigen::Triplet<double>(M-i,M-i+1,down)});
                sigma = MarketDataWrapper::localVolatility(double(i)*dx,T, localVolatilitySurface);
                mid = rfr + sigma*sigma*dt/(dx*dx); 
                up = -.5*sigma*sigma*dt/(dx*dx) - .5*(0.0 - .5*sigma*sigma)*dt/dx; 
                down = -.5*sigma*sigma*dt/(dx*dx) + .5*(0.0 - .5*sigma*sigma)*dt/dx;
                coefs.push_back({Eigen::Triplet<double>(M+i,M+i-1,up)});
                coefs.push_back({Eigen::Triplet<double>(M+i,M+i,mid)});
                coefs.push_back({Eigen::Triplet<double>(M+i,M+i+1,down)}); 

            }
        }

        A.setFromTriplets(coefs.begin(), coefs.end());
        return A;
    }

}