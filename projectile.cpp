#include "projectile.h"
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>

static inline double safe_rho_factor(double a, double y, double T0, double alfa) {
    double base = 1.0 - a * y / T0;
    if (base < 1e-12) base = 1e-12;
    return std::pow(base, alfa);
}

void simulate_trajectory(double t_delta, double v0, double theta0_deg, double D, double a, double g,
                         double m, double alfa, double T0, const std::string &filename) {
    double theta = theta0_deg * M_PI / 180.0;
    double x = 0.0, y = 0.0, t = 0.0;
    double vx = v0 * std::cos(theta);
    double vy = v0 * std::sin(theta);
    bool RUN = true;

    std::ofstream out(filename);
    out << std::setprecision(10);

    while (RUN) {
        double x_old = x, y_old = y, t_old = t;
        double v = std::sqrt(vx*vx + vy*vy);
        double rho_factor = safe_rho_factor(a, y, T0, alfa);
        double Fx = -D*v*vx*rho_factor;
        double Fy = -D*v*vy*rho_factor - m*g;

        x += t_delta*vx;
        y += t_delta*vy;
        vx += t_delta*(Fx/m);
        vy += t_delta*(Fy/m);
        t += t_delta;

        out << t << " " << x << " " << y << "\n";

        if (y < 0.0) {
            double r = (y_old - y != 0.0) ? y_old / (y_old - y) : 0.0;
            x = x_old + (x - x_old) * r;
            y = 0.0;
            t = t_old + r * t_delta;
            out << "# Collision at x=" << x << " m, t=" << t << " s\n";
            RUN = false;
        }
    }
    out.close();
}

double simulate_range(double t_delta, double v0, double theta0_deg, double D, double a, double g,
                      double m, double alfa, double T0, const std::string &filename) {
    double theta = theta0_deg * M_PI / 180.0;
    double x = 0.0, y = 0.0, t = 0.0;
    double vx = v0 * std::cos(theta);
    double vy = v0 * std::sin(theta);
    bool RUN = true;
    double x_max = 0.0;

    std::ofstream out(filename);
    out << std::setprecision(10);

    while (RUN) {
        double x_old = x, y_old = y, t_old = t;
        double v = std::sqrt(vx*vx + vy*vy);
        double rho_factor = safe_rho_factor(a, y, T0, alfa);
        double Fx = -D*v*vx*rho_factor;
        double Fy = -D*v*vy*rho_factor - m*g;

        x += t_delta*vx;
        y += t_delta*vy;
        vx += t_delta*(Fx/m);
        vy += t_delta*(Fy/m);
        t += t_delta;

        out << t << " " << x << " " << y << "\n";

        if (y < 0.0) {
            double r = (y_old - y != 0.0) ? y_old / (y_old - y) : 0.0;
            x = x_old + (x - x_old)*r;
            y = 0.0;
            t = t_old + r*t_delta;
            x_max = x;
            out << "# Collision at x=" << x << " m, t=" << t << " s\n";
            RUN = false;
        }
    }
    out.close();
    return x_max;
}

void simulate_range_vs_theta(double t_delta, double v0, const std::vector<double> &theta0_deg,
                             double D, double a, double g, double m, double alfa, double T0) {
    for (size_t i = 0; i < theta0_deg.size(); ++i) {
        std::string filename = "trajectory_theta_" + std::to_string(int(theta0_deg[i])) + ".txt";
        simulate_trajectory(t_delta, v0, theta0_deg[i], D, a, g, m, alfa, T0, filename);
    }
}
