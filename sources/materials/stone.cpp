#include "simulation.h"
#include "materials/stone.h"

Stone::Stone()
{
	state = solid;
	weight = 100;
	fire_level = 0;
	way = rand() % 2 * 2 - 1;
	color_swtich = 0;
	done = false;
}

Material* Stone::init()
{
	return new Stone();
}

Nature Stone::get_nature()
{
	return stone;
}

bool Stone::can_burn()
{
	return false;
}

sf::Color Stone::get_color()
{
	return sf::Color(150, 150, 150);
}



// Met à jour le matériaux

void Stone::update(int x, int y)
{
}



// Met à jour le feu

void Stone::update_fire(int x, int y)
{
	fire_level = 0;
	simulation.world[x][y]->draw_material(x, y);
}