#pragma once 
#include <Eigen/Dense>

namespace quantcpp {

    struct Svensson {

        double beta0, beta1, beta2, beta3, tau1, tau2; 

        Svensson(double beta0_, double beta1_, double beta2_, double beta3_, double tau1_, double tau2_): 
        beta0(beta0_), beta1(beta1_), beta2(beta2_), beta3(beta3_), tau1(tau1_), tau2(tau2_) {}

        struct SpotRateGradients {double beta0, beta1, beta2, beta3, tau1, tau2; };
        struct InstantaneousForwardRateGradients {double beta0, beta1, beta2, beta3, tau1, tau2; };

        double spotRate(double t) const {

            double f1 = tau1*(1-std::exp(-t/tau1))/t; 
            double f2 = tau1*(1-std::exp(-t/tau1))/t - std::exp(-t/tau1);
            double f3 = tau2*(1-std::exp(-t/tau2))/t - std::exp(-t/tau2);
            return beta0 + beta1 * f1 + beta2 * f2 + beta3*f3;
        }

        double instantaneousForwardRate(double t) const {

            double f1 = std::exp(-t/tau1);
            double f2 = t*std::exp(-t/tau1)/tau1;
            double f3 = t*std::exp(-t/tau2)/tau2;
            return beta0 + beta1  * f1 + beta2 * f2 + beta3*f3;
        }

        double derivativeInstantaneousForwardRate(double t) const {

            return std::exp(-t/tau1)*(beta2*(1-t/tau1) - beta1) + beta3*std::exp(-t/tau2)*(1-t/tau2)/tau2;
        }

        double instantaneousSpotRate() const {
            
            return beta0 + beta1;
        }

        SpotRateGradients spotRateGradients(double t) const {

            double dtau1f = (1.0-std::exp(-t/tau1))/t - std::exp(-t/tau1)/tau1;
            double dtau2f = (1.0-std::exp(-t/tau2))/t - std::exp(-t/tau2)/tau2;
  
            return {
                1.0, 
                tau1*(1-std::exp(-t/tau1))/t, 
                tau1*(1-std::exp(-t/tau1))/t - std::exp(-t/tau1),
                tau2*(1-std::exp(-t/tau2))/t - std::exp(-t/tau2), 
                 beta1*dtau1f + beta2*(dtau1f - t*std::exp(-t/tau1)/(tau1*tau1)), 
                 beta3*(dtau2f - t*std::exp(-t/tau2)/(tau2*tau2))
            };
        }

        InstantaneousForwardRateGradients instantaneousForwardRateGradients(double t) const {

            return {
                1.0, 
                std::exp(-t/tau1), 
                t*std::exp(-t/tau1)/tau1, 
                t*std::exp(-t/tau2)/tau2, 
                t*std::exp(-t/tau1)*(beta1+beta2*(t/tau1 - 1.0))/(tau1*tau1), 
                beta3*t*std::exp(-t/tau2)*(t/(tau2*tau2) - tau2)/(tau2*tau2)
            };
        }    
    };

    struct NelsonSiegel : public Svensson {

        NelsonSiegel(double beta0_, double beta1_, double beta2_, double tau1_): 
        Svensson(beta0_, beta1_, beta2_, 0.0, tau1_, 1.0) {}
    };


}