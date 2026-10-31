#pragma once 
#include <functional>
#include <limits>

namespace quantcpp {

    struct MarketDataWrapper {

        using LocalVolatilitySurface = std::function<double(double, double)>;

        using DiscountFactorTermStructure = std::function<double(double)>;

        using ForwardTermStructure = std::function<double(double)>;

        using AtTheMoneyTotalVariance = std::function<double(double)>;

        static double atmTotalVariance(double t, const AtTheMoneyTotalVariance& termStructure) {

            return (t==0.0) ? 0.0 : (t<0.0) ? std::numeric_limits<double>::quiet_NaN() : termStructure(t);
        }

        static double localVolatility(double k, double t, const LocalVolatilitySurface& surface) {

            return (t==0.0) ? 0.0 : (t<0.0) ? std::numeric_limits<double>::quiet_NaN() : surface(k,t);
        }

        static double forwardPrice(double t, double S, const ForwardTermStructure& termStructure) {

            return (t==0.0) ? S : (t<0.0) ? std::numeric_limits<double>::quiet_NaN() : termStructure(t);
        }

        static double forwardDiscountFactor(double t1, double t2, const DiscountFactorTermStructure& termStructure) {

            return discountFactor(t1,termStructure)/discountFactor(t2,termStructure);
        }

        static double discountFactor(double t, const DiscountFactorTermStructure& termStructure) {

            return (t==0.0) ? 1.0 : (t<0.0) ? std::numeric_limits<double>::quiet_NaN() : termStructure(t);
        }

    };

}