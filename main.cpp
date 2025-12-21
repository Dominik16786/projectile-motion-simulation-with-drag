#include <iostream>
#include <vector>
#include "projectile.h"
#include <cmath>

int main() {
    double g = 9.81;
    double m = 1.0;
    double v0 = 100.0;
    double D = 0.001;
    double a = 0.0;
    double alfa = 2.5;
    double T0 = 293.0;
    double theta0 = 45.0;

    double theta_rad = theta0 * M_PI / 180.0;
    double tmax = 2.0 * v0 * sin(theta_rad)/g;
    double dt = tmax / 500.0;

    simulate_trajectory(dt, v0, theta0, D, a, g, m, alfa, T0, "trajectory.txt");

    
    std::vector<double> theta_sweep;
    for (int i = 0; i <= 10; ++i) theta_sweep.push_back(20.0 + i*5); 
    simulate_range_vs_theta(dt, v0, theta_sweep, D, a, g, m, alfa, T0);

    std::cout << "Simulation finished. Files created: trajectory.txt + trajectory_theta_*.txt\n";
    return 0;
}

