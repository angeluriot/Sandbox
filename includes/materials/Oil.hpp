#ifndef OIL_H
#define OIL_H
#include "material.h"



// Classe définissant l'huile

class Oil : public Material
{

public:

	Oil();
	
	Material*	init();
	Nature		get_nature();
	bool		can_burn();
	sf::Color	get_color();

	void		update(int x, int y);
	void		update_fire(int x, int y);
};

#endif