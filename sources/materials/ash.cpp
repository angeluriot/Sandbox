#include "simulation.h"
#include "materials/ash.h"

Ash::Ash()
{
	state = dust;
	weight = 100;
	fire_level = 0;
	way = rand() % 2 * 2 - 1;
	color_swtich = rand() % 2;
	done = false;
}

Material* Ash::init()
{
	return new Ash();
}

Nature Ash::get_nature()
{
	return ash;
}

bool Ash::can_burn()
{
	return false;
}

sf::Color Ash::get_color()
{
	if (color_swtich)
		return sf::Color(110, 110, 110);

	else
		return sf::Color(170, 170, 170);
}



// Met à jour le matériaux

void Ash::update(int x, int y)
{
	update_dust(x, y);
}



// Met à jour le feu

void Ash::update_fire(int x, int y)
{
	fire_level = 0;
	simulation.world[x][y]->draw_material(x, y);
}