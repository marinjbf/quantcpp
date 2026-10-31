# Surface SVI 

Implementation of the Surface SVI (Power-Law) as defined from the following scientific paper: 

- Arbitrage-free SVI volatility surfaces, Jim Gatheral and Antoine Jacquier (2013) : https://arxiv.org/abs/1204.0646

The Power-Law SSVI formalutation of the total variance reads: 

$$
w(k,t) = \frac{\theta_t}{2}\left(1 + \rho \varphi_t k + \sqrt{(\varphi_t k + \rho)^2 + (1-\rho^2)}\right)
$$

with $\rho \in [0,1]$ and $\theta_t : \mathbb{R}_+ \rightarrow \mathbb{R}_+$ represents the term structure of the ATM total variance. Also the Power-Law function is given by: 

$$
\varphi_t = \eta \theta_t^{-\gamma}
$$

with $\eta > 0$ and $\gamma \in (0,1)$. The total variance skew and ATM skew are given by: 

$$
\frac{\partial w}{\partial k} = \frac{\theta_t}{2}\left( \rho\varphi_t + \frac{\varphi_t (\varphi_t k+\rho)}{\sqrt{(\varphi_t k + \rho)^2 + (1-\rho^2)}} \right) \Longleftrightarrow \frac{\partial w}{\partial k}\mid_{k=0} = \theta_t \varphi_t \rho
$$

Also, the second derivative with respect to log-moneyness is given by: 

$$
\frac{\partial^2 w}{\partial k^2} = \frac{\theta_t\varphi_t^2(1-\rho^2)}{2\left(\sqrt{(\varphi_t k + \rho)^2 + (1-\rho^2)}\right)^3}
$$
