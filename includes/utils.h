#ifndef UTILS_H
#define UTILS_H
#include <SFML/Graphics.hpp>
#include <cmath>
#include <random>
#include <vector>
#include <array>



extern int screen_width; // Largeur de l'écran



// Classe définissant une position

class Position
{

public:

	int x;
	int y;

	Position();
	Position(int x, int y);
	Position(const Position& position);

	void operator=(const Position& position);
};



#define PI			3.14159265359					// Pi
#define RESIZE		((1. / 1920.) * screen_width)	// Coéfficent en fonction de la taille de l'écran

#define BRUSH_SIZE	8								// Taille du brush
#define BRUSH_SPEED	5								// Nombre de particules par secondes par le brush
#define FIRE_MAX	10.								// Valeur maximum du niveau de feu

int		random_int(int min, int max);
bool	rand_probability(const double& probability);
double	distance(double position_1_x, double position_1_y, double position_2_x, double position_2_y);

#endif