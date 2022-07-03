#include "simulation.h"
#include "materials/wood.h"

Wood::Wood()
{
	state = solid;
	weight = 100;
	fire_level = 0;
	way = rand() % 2 * 2 - 1;
	color_swtich = 0;
	done = false;
}

Material* Wood::init()
{
	return new Wood();
}

Nature Wood::get_nature()
{
	return wood;
}

bool Wood::can_burn()
{
	return true;
}

sf::Color Wood::get_color()
{
	return sf::Color(134, 57, 11);
}



// Met à jour le matériaux

void Wood::update(int x, int y)
{
}



// Met à jour le feu

void Wood::update_fire(int x, int y)
{
	int temp = fire_level;
	fire_level -= 1;

	update_burn(x, y, 1000., 0.2);
	update_fire_propagation(x, y, 0.5);

	if (temp != fire_level)
		simulation.world[x][y]->draw_material(x, y);
}