#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <string>
#include <vector>

void simulate_trajectory(double t_delta, double v0, double theta0_deg, double D, double a,
                         double g, double m, double alfa, double T0, const std::string &filename);

double simulate_range(double t_delta, double v0, double theta0_deg, double D, double a,
                      double g, double m, double alfa, double T0, const std::string &filename);

void simulate_range_vs_theta(double t_delta, double v0, const std::vector<double> &theta0_deg,
                             double D, double a, double g, double m, double alfa, double T0);

#endif // PROJECTILE_H
