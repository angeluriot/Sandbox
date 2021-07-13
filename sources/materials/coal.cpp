#include "simulation.h"
#include "materials/coal.h"

Coal::Coal()
{
	state = solid;
	weight = 100;
	fire_level = 0;
	way = rand() % 2 * 2 - 1;
	color_swtich = 0;
	done = false;
}

Material* Coal::init()
{
	return new Coal();
}

Nature Coal::get_nature()
{
	return coal;
}

bool Coal::can_burn()
{
	return true;
}

sf::Color Coal::get_color()
{
	return sf::Color(30, 30, 30);
}



// Met à jour le matériaux

void Coal::update(int x, int y)
{
}



// Met à jour le feu

void Coal::update_fire(int x, int y)
{
	int temp = fire_level;
	fire_level -= 1;

	update_burn(x, y, 3000., 0.5);
	update_fire_propagation(x, y, 0.5);

	if (temp != fire_level)
		simulation.world[x][y]->draw_material(x, y);
}