# Backward solving the Dupire's PDE

Under a log-normal local volatility, $F_t$ satisfies the following geometric Brownian Motion SDE: 

$$
dF_t/F_t = \sigma(F_t,t) dW_t
$$

Furthermore, given a derivative asset $V_t$ written on $S_t$ and with boundary condition $V_T$, its dynamic can be written using Ito's lemma: 

$$
\partial_t V + \frac{\sigma(F_t,t)^2 F_t^2}{2} \partial^2_S V - r V = 0
$$

By setting $x_t = \log(F_t/S_0)$ and using the chain-rule, one can obtain the simplified PDE: 

$$
\partial_t V + \frac{\sigma(x_t,t)^2}{2} \partial^2_x V  - \frac{1}{2}\sigma(x_t,t)^2 \partial_x V - r V = 0
$$

We define the following operator: 

$$
L_nV_n = \frac{1}{2}\sigma(x_n,t_n)\left[ \frac{V^{j+1}_{n} + V^{j-1}_{n} - 2V^{j}_{n}}{(\Delta x_{n})^2} - \frac{V^{j+1}_{n} - V^{j-1}_{n}}{2\Delta x_{n}} \right] = \frac{1}{2\Delta x_{n}}\sigma(x_n,t_n)\left[\left(1/\Delta x_n - \frac{1}{2}\right)V^{j+1}_{n} + \left(1/\Delta x_n + \frac{1}{2}\right)V^{j-1}_{n}-2V^j_n/\Delta x_n\right]
$$

Therefore, the implicit method of solving the PDE reads: 

$$
V^j_{n+1} - V^j_n(1+r\Delta t) + \Delta t L_nV_n = 0 
$$

The explicit method reads: 

$$
V^j_{n+1} - V^j_n(1+r\Delta t) + \Delta t L_{n+1}V_{n+1} = 0
$$

The Crank-Nicolson method reads: 

$$
V^j_{n+1} - V^j_n(1+r\Delta t) + \frac{1}{2} \Delta t (L_{n+1}V_{n+1} + L_{n}V_{n}) = 0
$$

