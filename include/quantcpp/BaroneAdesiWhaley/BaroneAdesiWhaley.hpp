#pragma once 
#include <functional>
#include <quantcpp/BlackScholes/BlackSholes.hpp>
#include <numcpp/Optimizations/NewtonRaphson.hpp>

namespace quantcpp {

    class BaroneAdesiWhaley {

        public: 

            static double optimalExercisePriceInitialGuess(double mu, double K, double t, double sigma, double r, bool isCall) {

                 double putCallFlag = isCall ? 1.0 : -1.0; 
                double qq_inf_ = getQInf(mu,sigma,r,isCall);
                double Sinf = K/(1 - 1/qq_inf_);
                double payoff = putCallFlag*(Sinf - K); 
                double h = -putCallFlag*(mu*t+putCallFlag*2*sigma*std::sqrt(t))*K/payoff; 
                return Sinf-putCallFlag*std::exp(h)*payoff;
            }

            static double optimalExercisePrice(double mu, double K, double t, double sigma, double r, bool isCall) {
                if (mu >= r and isCall){return 10e9;}
                numcpp::NewtonRaphson res(
                    optimalExercisePriceInitialGuess(mu, K,t,sigma,r,isCall),
                    _getTarget(mu, K, t, sigma, r, isCall),
                    _getTargetFirstDerivative(mu, K,t,sigma,r,isCall),
                    10, 1e-12
                );
                return res.x;
            }

            static double exercisePremium(double F, double mu, double K, double t, double sigma, double r, bool isCall) {

                return _getExercisePremium(F,mu,K,t,sigma,r,isCall,optimalExercisePrice(mu,K,t,sigma,r,isCall));
            }

            static double price(double F, double mu, double K, double t, double sigma, double r, bool isCall) {

                return _getPrice(F,mu,K,t,sigma,r,isCall,optimalExercisePrice(mu,K,t,sigma,r,isCall));
            }

        private: 
            static std::function<double(double)> _getTarget(double mu, double K, double t, double sigma, double r, bool isCall) {

                return [mu, K, t, sigma, r, isCall](double F) -> double {

                    double putCallFlag = isCall ? 1.0 : -1.0;
                    double q = getQ(mu,sigma,r,t,isCall);
                    double price = std::exp(-r*t)*BlackScholes::europeanPrice(F*std::exp(mu*t),K,t,sigma,isCall);
                    double delta = BlackScholes::europeanDelta(F*std::exp(mu*t),mu,K,t,sigma,r,isCall);
                    return putCallFlag*(F-K) - price - putCallFlag*F*(1-putCallFlag*delta)/q;

                };
            }

            static std::function<double(double)> _getTargetFirstDerivative(double mu, double K, double t, double sigma, double r, bool isCall) {

                return [mu, K, t, sigma, r, isCall](double F) {

                    double putCallFlag = isCall ? 1.0 : -1.0;
                    double q = getQ(mu,sigma,r,t,isCall);
                    double delta = BlackScholes::europeanDelta(F*std::exp(mu*t),mu,K,t,sigma,r,isCall);
                    double gamma = BlackScholes::europeanGamma(F*std::exp(mu*t),mu,K,t,sigma,r,isCall);
                    return putCallFlag - delta*(1-1/q) - (putCallFlag-gamma*F)/q;

                };
            }

            static double getQ(double mu, double sigma, double r, double t, bool isCall) {

                double putCallFlag = isCall ? 1.0 : -1.0; 
                double N = 2*mu/(sigma*sigma);
                double M = 2*r/(sigma*sigma);
                return .5*(1-N+putCallFlag*std::sqrt((N-1)*(N-1)+4*M/(1-std::exp(-r*t))));
            }

            static double getQInf(double mu, double sigma, double r, bool isCall) {

                double putCallFlag = isCall ? 1.0 : -1.0; 
                double N = 2*mu/(sigma*sigma);
                double M = 2*r/(sigma*sigma);
                return .5*(1-N+putCallFlag*std::sqrt((N-1)*(N-1)+4*M));
            }

            static double _getExercisePremium(double F, double mu, double K, double t, double sigma, double r, bool isCall, double E) {

                if (mu >= r and isCall){return 0.0;}
                double putCallFlag = isCall ? 1.0 : -1.0;
                double qq_ = getQ(mu,sigma,r,t,isCall);
                double delta = BlackScholes::europeanDelta(E*std::exp(mu*t),mu,K,t,sigma,r,isCall);
                return putCallFlag * E * std::pow(F / E, qq_) * (1 - putCallFlag * delta) / qq_;
            }

            static double _getPrice(double F, double mu, double K, double t, double sigma, double r, bool isCall, double E) {

                double putCallFlag = isCall ? 1.0 : -1.0;
                double euroPrice = std::exp(-r*t)*BlackScholes::europeanPrice(F*std::exp(mu*t),K,t,sigma,isCall);
                double exercisePremium = (mu >= r and isCall) ? 0.0 : (putCallFlag*F >= putCallFlag*E) ? 0.0 : _getExercisePremium(F,mu,K,t,sigma,r,isCall,E);
                return (putCallFlag*F >= putCallFlag*E) ? putCallFlag*(F-K) : euroPrice + exercisePremium;
            }
    };

}