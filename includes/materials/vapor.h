#ifndef VAPOR_H
#define VAPOR_H
#include "material.h"



// Classe définissant la vapeur

class Vapor : public Material
{

public:

	Vapor();

	Material*	init();
	Nature		get_nature();
	bool		can_burn();
	sf::Color	get_color();

	void		update(int x, int y);
	void		update_fire(int x, int y);
};

#endif