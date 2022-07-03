#include "simulation.h"
#include "materials/lava.h"

Lava::Lava()
{
	state = liquid;
	weight = 15;
	fire_level = FIRE_MAX;
	way = rand() % 2 * 2 - 1;
	color_swtich = 0;
	done = false;
}

Material* Lava::init()
{
	return new Lava();
}

Nature Lava::get_nature()
{
	return lava;
}

bool Lava::can_burn()
{
	return false;
}

sf::Color Lava::get_color()
{
	return sf::Color(255, 127, 0);
}



// Met à jour le matériaux

void Lava::update(int x, int y)
{
	if (fire_level == 0)
	{
		harden(x, y);
		return;
	}

	update_liquid(x, y);
}



// Met à jour le feu

void Lava::update_fire(int x, int y)
{
	if (rand_probability(0.01) and is_solid_around(x, y))
		fire_level--;

	update_fire_propagation(x, y, 0.5);
}