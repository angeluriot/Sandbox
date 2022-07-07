#include "utils.hpp"

int random_int(int min, int max)
{
	return rand() % (max - min) + min;
}

bool rand_probability(float probability)
{
	if (probability < 0.f)
		return false;

	if (probability < 1.f)
		return ((float)rand() / (float)RAND_MAX < probability);

	return true;
}

float distance(dim::Vector2 position_1, float position_2_x, float position_2_y)
{
	return sqrt(pow(position_1.x - position_2_x, 2) + pow(position_1.y - position_2_y, 2));
}

float distance(float position_1_x, float position_1_y, dim::Vector2 position_2)
{
	return sqrt(pow(position_1_x - position_2.x, 2) + pow(position_1_y - position_2.y, 2));
}

float distance(float position_1_x, float position_1_y, float position_2_x, float position_2_y)
{
	return sqrt(pow(position_1_x - position_2_x, 2) + pow(position_1_y - position_2_y, 2));
}
