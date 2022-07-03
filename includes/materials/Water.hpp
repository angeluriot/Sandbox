#ifndef WATER_H
#define WATER_H
#include "material.h"



// Classe définissant l'eau

class Water : public Material
{

public:

	Water();
	
	Material*	init();
	Nature		get_nature();
	bool		can_burn();
	sf::Color	get_color();

	void		update(int x, int y);
	void		update_fire(int x, int y);
};

bool dilute(int x, int y, int target_x, int target_y);

#endif