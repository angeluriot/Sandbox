#ifndef WOOD_H
#define WOOD_H
#include "material.h"



// Classe définissant le bois

class Wood : public Material
{

public:

	Wood();
	
	Material*	init();
	Nature		get_nature();
	bool		can_burn();
	sf::Color	get_color();

	void		update(int x, int y);
	void		update_fire(int x, int y);
};

#endif