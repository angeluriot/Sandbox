#include "simulation.h"
#include "materials/sand.h"

Sand::Sand()
{
	state = dust;
	weight = 100;
	fire_level = 0;
	way = rand() % 2 * 2 - 1;
	color_swtich = rand() % 2;
	done = false;
}

Material* Sand::init()
{
	return new Sand();
}

Nature Sand::get_nature()
{
	return sand;
}

bool Sand::can_burn()
{
	return false;
}

sf::Color Sand::get_color()
{
	if (color_swtich)
		return sf::Color(205, 126, 0);

	else
		return sf::Color(235, 156, 30);
}



// Met à jour le matériaux

void Sand::update(int x, int y)
{
	update_dust(x, y);
}



// Met à jour le feu

void Sand::update_fire(int x, int y)
{
	fire_level = 0;
	simulation.world[x][y]->draw_material(x, y);
}