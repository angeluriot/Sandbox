#include "simulation.h"
#include "materials/salt.h"

Salt::Salt()
{
	state = dust;
	weight = 100;
	fire_level = 0;
	way = rand() % 2 * 2 - 1;
	color_swtich = rand() % 2;
	done = false;
}

Material* Salt::init()
{
	return new Salt();
}

Nature Salt::get_nature()
{
	return salt;
}

bool Salt::can_burn()
{
	return false;
}

sf::Color Salt::get_color()
{
	if (color_swtich)
		return sf::Color(225, 225, 225);

	else
		return sf::Color(255, 255, 255);
}



// Met à jour le matériaux

void Salt::update(int x, int y)
{
	if (rand_probability(0.01))
	{
		if (rand_probability(1. / 4.))
		{
			if (dissolve(x, y, x - 1, y))
				return;
		}

		if (rand_probability(1. / 3.))
		{
			if (dissolve(x, y, x + 1, y))
				return;
		}

		if (rand_probability(1. / 2.))
		{
			if (dissolve(x, y, x, y - 1))
				return;
		}

		if (dissolve(x, y, x, y + 1))
			return;
	}

	update_dust(x, y);
}



// Met à jour le feu

void Salt::update_fire(int x, int y)
{
	fire_level = 0;
	simulation.world[x][y]->draw_material(x, y);
}



// Dissous le sel dans l'eau

bool dissolve(int x, int y, int target_x, int target_y)
{
	if (simulation.in_world(target_x, target_y) and simulation.world[target_x][target_y]->get_nature() == water and !simulation.world[target_x][target_y]->salty)
	{
		simulation.world[target_x][target_y]->salty = true;
		simulation.world[target_x][target_y]->draw_material(target_x, target_y);
		simulation.world[x][y]->disappeared(x, y);

		return true;
	}

	return false;
}