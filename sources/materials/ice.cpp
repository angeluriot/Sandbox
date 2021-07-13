#include "simulation.h"
#include "materials/ice.h"

Ice::Ice()
{
	state = solid;
	weight = 100;
	fire_level = 0;
	way = rand() % 2 * 2 - 1;
	color_swtich = 0;
	done = false;
}

Material* Ice::init()
{
	return new Ice();
}

Nature Ice::get_nature()
{
	return ice;
}

bool Ice::can_burn()
{
	return false;
}

sf::Color Ice::get_color()
{
	return sf::Color(0, 200, 255);
}



// Met à jour le matériaux

void Ice::update(int x, int y)
{
	if ((rand_probability(0.0001) and is_hot_near(x, y)) or is_fire_around(x, y))
		liquefy(x, y);
}



// Met à jour le feu

void Ice::update_fire(int x, int y)
{
	fire_level = 0;
	simulation.world[x][y]->draw_material(x, y);
}



// Dit si il y a un matériaux chaud à côté

bool is_hot_near(int x, int y)
{
	for (Position pos : simulation.ways_4)
	{
		if (!(simulation.in_world(x + pos.x, y + pos.y) and (simulation.world[x + pos.x][y + pos.y]->get_nature() == ice or simulation.world[x + pos.x][y + pos.y]->get_nature() == snow)))
			return true;
	}

	return false;
}