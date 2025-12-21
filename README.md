# Projectile Motion Simulation with Drag

This project simulates **projectile motion including air drag** and optional temperature-dependent air density. It allows exploration of **how launch angle, initial velocity, and drag affect projectile trajectories**, and visually identifies the **fairest trajectory** (the one with the maximum range).

---

## Features
- **Single trajectory simulation:** Animate a single projectile’s flight in real time.  
- **Multi-angle sweep:** Simulate multiple launch angles (e.g., 20° to 70° in 11 steps) to compare ranges.  
- **Highlight the fairest trajectory:** Automatically detects the angle that produces the **longest range** and highlights it in the animation.  
- **Drag force included:** Quadratic velocity-dependent drag with optional altitude-dependent air density.

---

## Physics and Numerical Methods
- **Equations of motion:**  
  The projectile is influenced by gravity \( g \) and drag \( F_d \):
  \[
  F_d = - D \cdot v \cdot \vec{v} \cdot \rho(y)
  \]
  where:  
  - \( D \) = drag coefficient  
  - \( v \) = speed  
  - \( \vec{v} \) = velocity vector  
  - \( \rho(y) = (1 - a \cdot y / T_0)^\alpha \) accounts for **air density decreasing with altitude**

- **Numerical integration:**  
  The motion is solved with **explicit Euler integration**:
  \[
  \begin{aligned}
  x_{n+1} &= x_n + v_x \, dt \\
  y_{n+1} &= y_n + v_y \, dt \\
  v_x^{n+1} &= v_x^n + (F_x / m) \, dt \\
  v_y^{n+1} &= v_y^n + (F_y / m) \, dt
  \end{aligned}
  \]

- **Collision handling:**  
  When the projectile reaches the ground (`y < 0`), **linear interpolation** is used to set `y = 0` exactly.

---

## Usage

### 1. Compile the C++ simulation
```bash
g++ main.cpp projectile.cpp -o projectile -std=c++17 -O2
