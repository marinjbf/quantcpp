#include <cassert>
#include <quantcpp/LetsBeRational/LetsBeRational.hpp>

bool isClose(double a, double b, double tol = 1e-3) {return std::abs(a - b) <= tol;}

void testTemplateHighDimensionLetsBeRational(double sigmaMin, double sigmaMax, double xMin, double xMax) {

    using namespace quantcpp;

    double sigmaDelta = (sigmaMax - sigmaMin)/100.0; 
    double xDelta = (xMax - xMin)/100.0; 
    double sigma = sigmaMin, x = xMin;
    std::vector<double> sigmas, moneyness; 
    double priceCall, estSigmaCall,pricePut, estSigmaPut;
    for (int i = 0; i<100; i++) {
        sigmas.push_back(sigma);
        moneyness.push_back(x);
        x += xDelta; 
        sigma += sigmaDelta;
    }
    
    for (double s : sigmas) {

        for (double xx: moneyness) {

            priceCall = LetsBeRational::_getNormalizedPrice(xx,s,true);
            pricePut = LetsBeRational::_getNormalizedPrice(xx,s,false);

            if (priceCall>LetsBeRational::_getNormalizedIntrisicValue(xx, true)) {
                estSigmaCall = LetsBeRational::_getNormalizedVolatility(priceCall, xx, true);
                if (!std::isnan(estSigmaCall)) {
                    assert(isClose((estSigmaCall-s)/s,0.0,1e-1));
                }
            }

            if (pricePut>LetsBeRational::_getNormalizedIntrisicValue(xx, false)) {
                estSigmaPut = LetsBeRational::_getNormalizedVolatility(pricePut, xx, false);
                if (!std::isnan(estSigmaPut)) {
                    assert(isClose((estSigmaPut-s)/s,0.0,1e-1));
                }
            }         
        }
    }
}

int main() {

    testTemplateHighDimensionLetsBeRational(10e-7,1.22,0,3);
    testTemplateHighDimensionLetsBeRational(10e-5,7.07,0,16);
    testTemplateHighDimensionLetsBeRational(10e-5,0.18,0,10e-5);
    return 0;
}