#include "utils.h"

int screen_width;



// Construit une position

Position::Position()
{
	x = 0;
	y = 0;
}



// Construit une position à partir de son x et de son y

Position::Position(int x, int y)
{
	this->x = x;
	this->y = y;
}



// Construit une position à partir d'une autre position

Position::Position(const Position& position)
{
	*this = position;
}



// Assignation

void Position::operator=(const Position& position)
{
	x = position.x;
	y = position.y;
}



// Donne un entier entre min et max

int random_int(int min, int max)
{
	return rand() % (max - min) + min;
}



// Donne "vrai" avec une probabilité choisie

bool rand_probability(const double& probability)
{
	if (probability < 0.)
		return false;

	if (probability < 1.)
		return ((double)rand() / (double)RAND_MAX < probability);

	return true;
}



// Donne la distance entre deux points

double distance(double position_1_x, double position_1_y, double position_2_x, double position_2_y)
{
	return (int)sqrt(pow(position_1_x - position_2_x, 2) + pow(position_1_y - position_2_y, 2));
}