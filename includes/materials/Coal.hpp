#ifndef COAL_H
#define COAL_H
#include "material.h"



// Classe définissant le charbon

class Coal : public Material
{

public:

	Coal();

	Material*	init();
	Nature		get_nature();
	bool		can_burn();
	sf::Color	get_color();

	void		update(int x, int y);
	void		update_fire(int x, int y);
};

#endif