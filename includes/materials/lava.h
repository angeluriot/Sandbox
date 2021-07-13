#ifndef LAVA_H
#define LAVA_H
#include "material.h"



// Classe définissant la lave

class Lava : public Material
{

public:

	Lava();

	Material*	init();
	Nature		get_nature();
	bool		can_burn();
	sf::Color	get_color();

	void		update(int x, int y);
	void		update_fire(int x, int y);
};

#endif