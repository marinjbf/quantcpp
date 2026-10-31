#include <quantcpp/GeometricLocalVolPDE/GeometricLocaVolPDE.hpp>
#include <numcpp/ThomasAlgorithm.hpp>

namespace quantcpp {
    
    Eigen::MatrixXd GeometricLocalVolatilityPDESolver::ImplicitBackwardPricer::europeanVanillaPriceMatrix(double S, double K, double T, bool isCall, size_t N, size_t M) const {

        double dt = T/double(N);
        double atmLocalVol = localVolatilitySurface(0.0,T);
        double xmax = std::abs(NUMBER_SIGMA_DEVIATION)*std::sqrt(T)*atmLocalVol;  
        double dx = xmax/double(M);
        double putCallFlag = isCall ? 1.0 : -1.0;
        double t = T;
        double F = MarketDataWrapper::forwardPrice(T, S, forwardTermStructure); 
        

        Eigen::MatrixXd optionValueMatrix = Eigen::MatrixXd::Zero(2*M+1, N+1);
        optionValueMatrix.col(N)(M) = std::max(putCallFlag*(F-K),0.0) ;

        for (size_t i = 1; i<=M; i++) {

            double F1 = F*std::exp(-double(i)*dx); 
            double F2 = F*std::exp(double(i)*dx); 
  
            optionValueMatrix.col(N)(M-i) = std::max(putCallFlag*(F2-K),0.0);
            optionValueMatrix.col(N)(M+i) = std::max(putCallFlag*(F1-K),0.0);

        }; 

        for (size_t i = N; i>0; i--) {
            t -= dt; 
            t = std::max(dt/5.0, t);
            Eigen::SparseMatrix<double> implicitMatrix = TransitionMatrix::implicitMatrix(t, dx, dt, M, localVolatilitySurface, discountFactorTermStructure);
            
            optionValueMatrix.col(i-1) = numcpp::solveThomasAlgorithm(implicitMatrix, optionValueMatrix.col(i));
            optionValueMatrix.col(i-1)(2) = std::max(optionValueMatrix.col(i-1)(2),0.0); 
            optionValueMatrix.col(i-1)(1) = std::max(optionValueMatrix.col(i-1)(2),0.0); 
            optionValueMatrix.col(i-1)(0) = std::max(2*optionValueMatrix.col(i-1)(1) - optionValueMatrix.col(i-1)(2),0.0); 

        }
        return optionValueMatrix;
    }

}