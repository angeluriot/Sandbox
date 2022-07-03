#ifndef SALT_H
#define SALT_H
#include "material.h"



// Classe définissant le sel

class Salt : public Material
{

public:

	Salt();
	
	Material*	init();
	Nature		get_nature();
	bool		can_burn();
	sf::Color	get_color();

	void		update(int x, int y);
	void		update_fire(int x, int y);
};

bool dissolve(int x, int y, int target_x, int target_y);

#endif