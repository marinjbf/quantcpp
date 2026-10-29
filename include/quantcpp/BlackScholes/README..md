# Black-Sholes : Geometric brownian motion

Black-Sholes Model refers to the formulation of a spot price $S_t$ following an geometric brownian motion which satisfies the following SDE: 

$$
dS_t/S_t = \mu_t dt + \sigma(S_t,t)dW_t
$$

Where $\mu_t$ can be extracted from the forward term structure of the spot price. For more details, see the following scientific papers: 

- [1] The pricing of options and corporate liabilities - Black and Scholes (1973) : https://www.jstor.org/stable/1831029
- [2] The pricing of commodity contract - Black (1976) : https://www.sciencedirect.com/science/article/abs/pii/0304405X76900246

## Derivation of the time-dependant drift from the forward term structure 

We assume the forward price being a driftless geometric brownian motion such as: 

$$
\frac{dF_t(T)}{F_t(T)} = \sigma_t\left(F_t(T), t\right) dW_t
$$ 

Thus the dynamic of the log-process $\ln F_t(T)$ is given by: 

$$
d\ln F_t(T) = -\frac{1}{2}\sigma_t\left(F_t(T)\right)^2 dt + \sigma_t\left(F_t(T), t\right)dW_t
$$

The relationship between the log-spot price and the log-forward price is given by: 

$$\ln S_t = \lim_{T \rightarrow t} \ln F_t(T)$$

Thus: 

$$
d\ln S_t = d\ln F_t(T)\mid_{T=t} + \frac{\partial \ln F_t(T)}{\partial T}\mid_{T=t} dt = \left[\frac{\partial \ln F_t(T)}{\partial T}\mid_{T=t} - \frac{1}{2} \sigma_t(S_t, t)^2\right] dt + \sigma_t(S_t, t) dW_t
$$

Under the risk-neutral measure $\mathbb{Q}$, the forward price with maturity $T$ is given by:

$$
F_t(T) = \mathbb{E}^\mathbb{Q}_t\left[S_T\right]
$$

The solution of the log-spot at time $T$ is given by: 

$$
\ln S_T = \ln S_t + \int_t^T \mu_s - \frac{1}{2}\sigma^2_s(S_s, s)ds + \int_t^T \sigma_s(S_s, s) dW_s
$$

Thus: 

$$
S_T = S_t \exp \left[ \int_t^T \mu_s - \frac{1}{2}\sigma^2_s(S_s,s)ds + \int_t^T \sigma_s(S_s,s) dW_s \right]

$$

Finally we have: 

$$
F_t(T) = \mathbb{E}^\mathbb{Q}_t\left[S_T\right] = S_t\exp \left[ \int_t^T \mu_s ds\right] \text{ where } \mu_t = \frac{\partial \ln F_t(T)}{\partial T}\mid_{T=t}
$$