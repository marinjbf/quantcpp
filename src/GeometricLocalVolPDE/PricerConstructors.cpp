#include <quantcpp/GeometricLocalVolPDE/GeometricLocaVolPDE.hpp>

namespace quantcpp {

    GeometricLocalVolatilityPDESolver::ImplicitBackwardPricer::ImplicitBackwardPricer(
        const MarketDataWrapper::ForwardTermStructure& forwardTermStructure_, 
        const MarketDataWrapper::DiscountFactorTermStructure& discountFactorTermStructure_, 
        const MarketDataWrapper::LocalVolatilitySurface& localVolatilitySurface_): 
    forwardTermStructure(std::move(forwardTermStructure_)), 
    discountFactorTermStructure(std::move(discountFactorTermStructure_)), 
    localVolatilitySurface(std::move(localVolatilitySurface_)){}

    GeometricLocalVolatilityPDESolver::ExplicitForwardPricer::ExplicitForwardPricer(
        const MarketDataWrapper::ForwardTermStructure& forwardTermStructure_, 
        const MarketDataWrapper::DiscountFactorTermStructure& discountFactorTermStructure_, 
        const MarketDataWrapper::LocalVolatilitySurface& localVolatilitySurface_): 
    forwardTermStructure(std::move(forwardTermStructure_)), 
    discountFactorTermStructure(std::move(discountFactorTermStructure_)), 
    localVolatilitySurface(std::move(localVolatilitySurface_)){}


}