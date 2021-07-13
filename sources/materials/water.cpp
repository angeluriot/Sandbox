#include "simulation.h"
#include "materials/water.h"

Water::Water()
{
	state = liquid;
	weight = 10;
	fire_level = 0;
	way = rand() % 2 * 2 - 1;
	color_swtich = 0;
	done = false;
}

Material* Water::init()
{
	return new Water();
}

Nature Water::get_nature()
{
	return water;
}

bool Water::can_burn()
{
	return false;
}

sf::Color Water::get_color()
{
	if (salty)
		return sf::Color(0, 100, 255);

	else
		return sf::Color(0, 50, 255);
}



// Met à jour le matériaux

void Water::update(int x, int y)
{
	if (salty and rand_probability(1. / 2.))
	{
		if (rand_probability(1. / 4.))
		{
			if (dilute(x, y, x - 1, y))
				return;
		}

		if (rand_probability(1. / 3.))
		{
			if (dilute(x, y, x + 1, y))
				return;
		}

		if (rand_probability(1. / 2.))
		{
			if (dilute(x, y, x, y - 1))
				return;
		}

		if (dilute(x, y, x, y + 1))
			return;
	}

	if (turn_off_fire(x, y))
	{
		evaporate(x, y);
		return;
	}

	update_liquid(x, y);
}



// Met à jour le feu

void Water::update_fire(int x, int y)
{
	fire_level = 0;
	simulation.world[x][y]->draw_material(x, y);
}



// Dillue l'eau salée dans l'eau

bool dilute(int x, int y, int target_x, int target_y)
{
	if (simulation.in_world(target_x, target_y) and simulation.world[target_x][target_y]->get_nature() == water and !simulation.world[target_x][target_y]->salty)
	{
		simulation.world[target_x][target_y]->salty = true;
		simulation.world[target_x][target_y]->draw_material(target_x, target_y);

		simulation.world[x][y]->salty = false;
		simulation.world[x][y]->draw_material(x, y);

		return true;
	}

	return false;
}