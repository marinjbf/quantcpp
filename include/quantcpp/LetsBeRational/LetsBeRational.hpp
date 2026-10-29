#pragma once 
#include <functional>

namespace quantcpp {

    struct LetsBeRational {

        static constexpr double H_LARGE = -10.0;
        static constexpr double T_SMALL = 0.21;
        static constexpr double ONE_OVER_SQRT_TWO_PI = 0.3989422804014326779399460599343818684758586311649;   
        static constexpr double ONE_OVER_SQRT_TWO = 0.7071067811865475244008443621048490392848359376887; 
        static constexpr double PI = 3.14159265358979323846;
        static constexpr double SQRT_TWO_PI = 2.50662827463100050242;
        static constexpr int MAX_ITERATIONS = 100;
        static constexpr double TOLERANCE_THRESHOLD = 1e-20;

        static double _getNormalizedIntrisicValue(double x, bool isCall);
        static double _getCallPriceRegion1(double h, double t); 
        static double _getCallPriceRegion2(double h, double t); 
        static double _getCallPriceRegion3(double h, double t); 
        static double _getCallPriceRegion4(double h, double t); 
        static double _getCallPrice(double x, double normalizedSigma);
        static double _getVega(double x, double normalizedSigma);
        static double _getVolga(double x, double normalizedSigma);
        static double _getNormalizedPrice(double x, double normalizedSigma, bool isCall);
        static double _getNormalizedVolatility(double normalizedPrice, double x, bool isCall);

        static double _getRationalCubicInterpolate(double x, double x0, double x1,double y0, double y1,double dy0, double dy1,double r); 

        static double _getRightAsymptoticR(double x0, double x1,double y0, double y1,double dy0, double dy1, double ddy0);
        static double _getRightAsymptotic(double sigma); 
        static double _getFirstDerivativeRightAsymptotic(double x, double sigma);
        static double _getSecondDerivativeRightAsymptotic(double x, double sigma);

        static double _getLeftAsymptoticR(double x0, double x1,double y0, double y1,double dy0, double dy1, double ddy1);
        static double _getLeftAsymptotic(double x, double sigma); 
        static double _getFirstDerivativeLeftAsymptotic(double x, double sigma); 
        static double _getSecondDerivativeLeftAsymptotic(double x, double sigma); 
        static double _getLeftAsymptoticZ(double x, double sigma);

        static std::tuple<double, double, double, double, double, double, double, double, double, double, bool> _getInitialData(double beta, double x, double isCall);
        static double _getInitialGuess(double beta, double x, bool isCall); 
        static std::function<double(double)> _getTarget(double beta, double x, double bLower, double bUpper);
        static std::function<double(double)> _getTargetFirstDerivative(double beta, double x, double bLower, double bUpper); 

    };

    


}