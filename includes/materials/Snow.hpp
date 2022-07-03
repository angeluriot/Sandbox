#ifndef SNOW_H
#define SNOW_H
#include "material.h"



// Classe définissant la neige

class Snow : public Material
{

public:

	Snow();

	Material*	init();
	Nature		get_nature();
	bool		can_burn();
	sf::Color	get_color();

	void		update(int x, int y);
	void		update_fire(int x, int y);
};

bool is_not_cold_near(int x, int y);

#endif