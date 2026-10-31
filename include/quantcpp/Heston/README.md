# Heston model

Heston Model refers to the formulation of a spot price $S_t$ following an geometric brownian motion with CIR stochastic volatility which satisfies the following SDE: 

$$
dS_t/S_t = \mu_t dt + \sqrt{v_t}dW^S_t
$$

$$
dv_t = \kappa(\theta - v_t) + \eta \sqrt{v_t}dW^v_t
$$

with $<dW^S_t, dW^v_t> = \rho dt$

For more details, see the following scientific papers: 

- The volatility surface, a practitioner’s guide, Gatheral (2006) : https://link.springer.com/article/10.1007/s11408-007-0072-4
- The Heston Model and its Extensions in Matlab and C#, Fabrice Douglas Rouah (2013): https://onlinelibrary.wiley.com/doi/book/10.1002/9781118656471
