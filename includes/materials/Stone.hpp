#ifndef STONE_H
#define STONE_H
#include "material.h"



// Classe définissant la pierre

class Stone : public Material
{

public:

	Stone();

	Material*	init();
	Nature		get_nature();
	bool		can_burn();
	sf::Color	get_color();

	void		update(int x, int y);
	void		update_fire(int x, int y);
};

#endif