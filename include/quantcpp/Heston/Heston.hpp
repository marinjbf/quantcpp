#pragma once 
#include "numcpp/Quadratures/GaussLaguerre.hpp"
#include <quantcpp/LewisStochasticVolatility/LewisStochasticVolatility.hpp>

namespace quantcpp {

    struct Heston {

        static LewisStochasticVolatility::CharacteristicFunction characteristicFunction(double t, double v0, double theta, double rho, double eta, double kappa) {

            LewisStochasticVolatility::CharacteristicFunction cf = [v0,theta,rho,eta,kappa,t](std::complex<double> u){ 
                std::complex<double> i(0.0, 1.0);
                std::complex<double> beta = kappa - rho*eta*i*u;
                std::complex<double> d = std::sqrt(beta*beta + eta*eta*(i*u + u*u));
                std::complex<double> g = (beta - d)/(beta + d); 
                std::complex<double> D = (beta - d)*(1.0-std::exp(-d*t))/(eta*eta*(1.0-g*std::exp(-d*t)));
                std::complex<double> C = kappa*(t*(beta-d) - 2.0*std::log((1.0-g*std::exp(-d*t))/(1.0-g)))/(eta*eta); 
                return std::exp(C*theta+D*v0); 
            };

            return cf;
        };

        struct GaussLaguerre {

            double v0, theta, rho, eta, kappa;
            numcpp::GaussLaguerreQuadrature gaussLaguerreQuadratures;
            

            GaussLaguerre(double v0_, double theta_, double rho_, double eta_, double kappa_, const numcpp::GaussLaguerreQuadrature& gaussLaguerreQuadratures_): 
            v0(v0_), theta(theta_), rho(rho_), eta(eta_), kappa(kappa_), gaussLaguerreQuadratures(std::move(gaussLaguerreQuadratures_)) {}


            double europeanPrice(double x, double t, bool isCall) {

                auto cf = characteristicFunction(t, v0, theta, rho, eta, kappa);
                return LewisStochasticVolatility::GaussLaguerre::europeanPrice(x,isCall,cf,gaussLaguerreQuadratures);
            }

            double impliedTotalVariance(double x, double t) {

                auto cf = characteristicFunction(t, v0, theta, rho, eta, kappa);
                return LewisStochasticVolatility::GaussLaguerre::impliedTotalVariance(x, cf,gaussLaguerreQuadratures);

            }

            double impliedDensity(double x, double t) {

                auto cf = characteristicFunction(t, v0, theta, rho, eta, kappa);
                return LewisStochasticVolatility::GaussLaguerre::impliedDensity(x, cf, gaussLaguerreQuadratures);
            }


        };

        

    };

}