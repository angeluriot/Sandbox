#ifndef ICE_H
#define ICE_H
#include "material.h"



// Classe définissant la glace

class Ice : public Material
{

public:

	Ice();

	Material*	init();
	Nature		get_nature();
	bool		can_burn();
	sf::Color	get_color();

	void		update(int x, int y);
	void		update_fire(int x, int y);
};

bool is_hot_near(int x, int y);

#endif