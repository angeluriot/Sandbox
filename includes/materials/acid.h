#ifndef ACID_H
#define ACID_H
#include "material.h"



// Classe définissant l'acide

class Acid : public Material
{

public:

	Acid();

	Material*	init();
	Nature		get_nature();
	bool		can_burn();
	sf::Color	get_color();

	void		update(int x, int y);
	void		update_fire(int x, int y);
};

bool corrosion(int x, int y);

#endif