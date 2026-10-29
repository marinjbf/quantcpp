# Bachelier Model : Arithmetic brownian motion 

Bachelier Model refers to the formulation of a spot price $S_t$ following an arithmetic brownian motion which satisfies the following SDE: 

$$
dS_t = \mu_t dt + \sigma dW_t
$$

Where $\mu_t$ can be extracted from the forward term structure of the spot price. For more details, see the following scientific papers: 

- [1] Théorie de la spéculation - Bachelier (1900) : http://www.numdam.org/item?id=ASENS_1900_3_17__21_0
- [2] Numerical approximation of the implied volatility under arithmetic Brownian motion - Choi, Kim, Kwak (2007) : https://ssrn.com/abstract=990747

## Derivation of the time-dependant drift from the forward term structure 

We assume the forward price being a driftless arithmetic brownian motion such as: 

$$
dF_t(T) = \sigma dW_t
$$

Since the relationship between the spot price and the forward price is given by: 

$$ S_t = \lim_{T \rightarrow t} F_t(T)$$

Thus: 

$$
dS_t = dF_t(T)\mid_{T=t} + \frac{\partial F_t(T)}{\partial T}\mid_{T=t}dt = \frac{\partial F_t(T)}{\partial T}\mid_{T=t}dt + \sigma dW_t
$$

With the solution given by: 

$$
S_T = S_t + \int_t^T \frac{\partial F_s(T)}{\partial T}\mid_{T=s}ds + \int_t^T \sigma dW_s
$$

Finally, the forward price is given by: 

$$
F_t(T) = \mathbb{E}^\mathbb{Q}_t\left[S_T\right] = S_t + \int_t^T \mu_sds  \text{ where } \mu_t = \frac{\partial F_t(T)}{\partial T}\mid_{T=t} 
$$