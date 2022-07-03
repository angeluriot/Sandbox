#ifndef AIR_H
#define AIR_H
#include "material.h"



// Classe définissant l'air

class Air : public Material
{

public:

	Air();
	
	Material*	init();
	Nature		get_nature();
	bool		can_burn();
	sf::Color	get_color();
	
	void		update(int x, int y);
	void		update_fire(int x, int y);
};

#endif