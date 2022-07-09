#ifndef UTILS_HPP
#define UTILS_HPP
#include <cmath>
#include <random>
#include <vector>
#include <array>
#include "libraries.hpp"

/**
 * @brief Give a random number between min and max.
 *
 * @param min the minimum value
 * @param max the maximum value
 * @return the random number
 */
int random_int(int min, int max);

/**
 * @brief Give true with a given probability.
 *
 * @param probability the probability
 * @return true with the given probability
 */
bool rand_probability(float probability);

/**
 * @brief Give the distance between two points.
 *
 * @param position_1 the first position
 * @param position_2_x the second position x
 * @param position_2_y the second position y
 * @return the distance
 */
float distance(dim::Vector2 position_1, float position_2_x, float position_2_y);

/**
 * @brief Give the distance between two points.
 *
 * @param position_1_x the first position x
 * @param position_1_y the second position y
 * @param position_2 the second position
 * @return the distance
 */
float distance(float position_1_x, float position_1_y, dim::Vector2 position_2);

/**
 * @brief Give the distance between two points.
 *
 * @param position_1_x the first position x
 * @param position_1_y the first position y
 * @param position_2_x the second position x
 * @param position_2_y the second position y
 * @return the distance
 */
float distance(float position_1_x, float position_1_y, float position_2_x, float position_2_y);

#endif
