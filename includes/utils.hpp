#ifndef UTILS_H
#define UTILS_H
#include <cmath>
#include <random>
#include <vector>
#include <array>

constexpr pi = 3.14159265359

int random_int(int min, int max);
bool rand_probability(const double& probability);
double distance(double position_1_x, double position_1_y, double position_2_x, double position_2_y);

#endif
