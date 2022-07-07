#ifndef UTILS_HPP
#define UTILS_HPP
#include <cmath>
#include <random>
#include <vector>
#include <array>
#include "libraries.hpp"

constexpr float pi = 3.14159265359f;

int random_int(int min, int max);
bool rand_probability(float probability);
float distance(dim::Vector2 position_1, float position_2_x, float position_2_y);
float distance(float position_1_x, float position_1_y, dim::Vector2 position_2);
float distance(float position_1_x, float position_1_y, float position_2_x, float position_2_y);

#endif
