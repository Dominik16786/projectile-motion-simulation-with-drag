# Projectile Motion Simulation with Drag

Simulate projectile motion with **air drag** and optional **altitude-dependent air density**. Explore how **launch angle, initial velocity, and drag** affect trajectories and identify the **fairest trajectory** (maximum range).

---

## Features
- **Single trajectory simulation:** Animate a projectile’s flight in real time.  
- **Multi-angle sweep:** Compare trajectories for multiple launch angles (20° to 70°, 11 steps).  
- **Highlight the fairest trajectory:** Automatically detects and highlights the trajectory with the **longest range**.  
- **Drag force included:** Quadratic velocity-dependent drag with optional altitude-dependent air density.  

---

## Physics and Numerical Methods

### Equations of Motion
The projectile is influenced by gravity (`g`) and drag (`F_d`):

$$
F_d = - D \cdot v \cdot \vec{v} \cdot \rho(y)
$$

where:  
- `D` = drag coefficient  
- `v` = speed  
- `\vec{v}` = velocity vector  
- $\rho(y) = (1 - a \cdot y / T_0)^\alpha$ models air density decreasing with altitude  

### Numerical Integration
The motion is solved using **explicit Euler integration**:

$$
\begin{align*}
x_{n+1} &= x_n + v_x \cdot dt \\
y_{n+1} &= y_n + v_y \cdot dt \\
v_x^{n+1} &= v_x^n + \frac{F_x}{m} \cdot dt \\
v_y^{n+1} &= v_y^n + \frac{F_y}{m} \cdot dt
\end{align*}
$$

### Collision Handling
When the projectile reaches the ground (`y < 0`), **linear interpolation** is used to set `y = 0` exactly.


