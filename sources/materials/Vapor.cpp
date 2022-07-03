#include "simulation.h"
#include "materials/vapor.h"

Vapor::Vapor()
{
	state = gas;
	weight = -10;
	fire_level = 0;
	way = rand() % 2 * 2 - 1;
	color_swtich = 0;
	done = false;
}

Material* Vapor::init()
{
	return new Vapor();
}

Nature Vapor::get_nature()
{
	return vapor;
}

bool Vapor::can_burn()
{
	return false;
}

sf::Color Vapor::get_color()
{
	return sf::Color(0, 70, 70);
}



// Met à jour le matériaux

void Vapor::update(int x, int y)
{
	if (rand_probability(0.001))
	{
		liquefy(x, y);
		return;
	}

	for (Position pos : simulation.ways_4)
	{
		if (simulation.in_world(x + pos.x, y + pos.y) and (simulation.world[x + pos.x][y + pos.y]->get_nature() == ice or simulation.world[x + pos.x][y + pos.y]->get_nature() == snow))
		{
			liquefy(x, y);
			simulation.world[x + pos.x][y + pos.y]->liquefy(x + pos.x, y + pos.y);
			return;
		}
	}

	update_gas(x, y);
}



// Met à jour le feu

void Vapor::update_fire(int x, int y)
{
	fire_level = 0;
	simulation.world[x][y]->draw_material(x, y);
}