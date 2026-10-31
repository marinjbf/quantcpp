#include <quantcpp/GeometricLocalVolBackwardPDE/GeometricLocalVolBackwardPDE.hpp>

namespace quantcpp {

    GeometricLocalVolatilityBackwardPDE::ImplicitPricer::ImplicitPricer(
        const MarketDataWrapper::ForwardTermStructure& forwardTermStructure_, 
        const MarketDataWrapper::DiscountFactorTermStructure& discountFactorTermStructure_, 
        const MarketDataWrapper::LocalVolatilitySurface& localVolatilitySurface_): 
    forwardTermStructure(std::move(forwardTermStructure_)), 
    discountFactorTermStructure(std::move(discountFactorTermStructure_)), 
    localVolatilitySurface(std::move(localVolatilitySurface_)){}


}