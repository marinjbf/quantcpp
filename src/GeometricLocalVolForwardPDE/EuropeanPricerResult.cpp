#include <quantcpp/GeometricLocalVolForwardPDE/GeometricLocalVolForwardPDE.hpp>
#include <limits>

namespace quantcpp {

    double GeometricLocalVolatilityForwardPDE::EuropeanPricerResult::price(double K, double T, bool isCall) const {

        auto it = std::find(timeVector.begin(), timeVector.end(), T);
        size_t M = (priceMatrix.rows()-1)/2;
        size_t N = priceMatrix.cols();

        if (it != timeVector.end()) {

            size_t timeIndex = it - timeVector.begin();

            if (timeVector[timeIndex]==T) {

                double F = forwardPriceVector(timeIndex);
                double x = std::log(F/K);
                it = std::find(logMoneynessVector.begin(), logMoneynessVector.end(), x);

                if (it != logMoneynessVector.end()) {

                    size_t lmIndex = it - logMoneynessVector.begin();
                    double x1 = logMoneynessVector(lmIndex-1);
                    double x2 = logMoneynessVector(lmIndex);
                    double y1 = priceMatrix.col(timeIndex)(lmIndex-1);
                    double y2 = priceMatrix.col(timeIndex)(lmIndex);
                    return y1 + (x1-x)*(y2-y1)/(x2-x1);

                } else {

                    return std::numeric_limits<double>::quiet_NaN();
                }
                 
            } else {

                double F1 = forwardPriceVector(timeIndex-1);
                double F2 = forwardPriceVector(timeIndex);
                double T1 = timeVector(timeIndex-1);
                double T2 = timeVector(timeIndex);
                double F = F1 + (T1-T)*(F2-F1)/(T2-T1);
                double x = std::log(F/K);
                it = std::find(logMoneynessVector.begin(), logMoneynessVector.end(), x);

                if (it != logMoneynessVector.end()) {

                    size_t lmIndex = it - logMoneynessVector.begin();
                    double x1 = logMoneynessVector(lmIndex-1);
                    double x2 = logMoneynessVector(lmIndex);
                    double y1 = priceMatrix.col(timeIndex-1)(lmIndex-1);
                    double y2 = priceMatrix.col(timeIndex-1)(lmIndex);
                    double price1 = y1 + (x1-x)*(y2-y1)/(x2-x1);
                    y1 = priceMatrix.col(timeIndex)(lmIndex-1);
                    y2 = priceMatrix.col(timeIndex)(lmIndex);
                    double price2 = y1 + (x1-x)*(y2-y1)/(x2-x1);
                    return price1 + (T1-T)*(price2-price1)/(T2-T1);

                } else {

                    return std::numeric_limits<double>::quiet_NaN();
                }
            }

        } else {

            return std::numeric_limits<double>::quiet_NaN();
        }
         
    }

}