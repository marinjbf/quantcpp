#include <quantcpp/GeometricLocalVolForwardPDE/GeometricLocalVolForwardPDE.hpp>
#include <quantcpp/GeometricLocalVolBackwardPDE/GeometricLocalVolBackwardPDE.hpp>
#include <numcpp/ThomasAlgorithm.hpp>


namespace quantcpp { 


    GeometricLocalVolatilityForwardPDE::EuropeanPricerResult GeometricLocalVolatilityForwardPDE::ExplicitForwardPricer::europeanVanillaMatrixes(double S, double T, bool isCall, size_t N, size_t M) const {

        EuropeanPricerResult result;
        result.isCall = isCall;
        double dt = T/double(N);
        double atmLocalVol = localVolatilitySurface(0.0,T);
        double xmax = std::abs(NUMBER_SIGMA_DEVIATION)*std::sqrt(T)*atmLocalVol;  
        double dx = xmax/double(M);
        double putCallFlag = isCall ? 1.0 : -1.0;
        double t = 0.0;
        double F = S;

        result.priceMatrix.col(0)(0) = 0.0;
        result.forwardPriceVector(0) = S;
        result.logMoneynessVector(0) = 0.0;
        result.timeVector(0) = 0.0;
        
        for (size_t i = 1; i<=M; i++) {

            double F1 = F*std::exp(-double(i)*dx); 
            double F2 = F*std::exp(double(i)*dx); 
            result.priceMatrix.col(0)(M-i) = std::max(putCallFlag*(F2-S),0.0);
            result.logMoneynessVector(M-i) = double(i)*dx;
            result.priceMatrix.col(0)(M+i) = std::max(putCallFlag*(F1-S),0.0);
            result.logMoneynessVector(M+i) = -double(i)*dx;

        }; 

        for (size_t i = 0; i<N; i++) {

            t += dt; 
            F = MarketDataWrapper::forwardPrice(t, S, forwardTermStructure);
            result.timeVector(i+1) = t;
            result.forwardPriceVector(i+1) = F;
            Eigen::SparseMatrix<double> explicitMatrix = GeometricLocalVolatilityBackwardPDE::TransitionMatrix::explicitMatrix(t, dx, dt, M, localVolatilitySurface, discountFactorTermStructure);
            result.priceMatrix.col(i+1) = numcpp::solveThomasAlgorithm(explicitMatrix, result.priceMatrix.col(i));
            result.priceMatrix.col(i+1)(2) = std::max(result.priceMatrix.col(i+1)(2),0.0); 
            result.priceMatrix.col(i+1)(1) = std::max(result.priceMatrix.col(i+1)(2),0.0); 
            result.priceMatrix.col(i+1)(0) = std::max(2*result.priceMatrix.col(i+1)(1) - result.priceMatrix.col(i+1)(2),0.0); 

        };

        return result;
    }
}