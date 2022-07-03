#include "simulation.h"
#include "materials/air.h"

Air::Air()
{
	state = empty;
	weight = -1000;
	fire_level = 0;
	way = rand() % 2 * 2 - 1;
	color_swtich = 0;
	done = false;
}

Material* Air::init()
{
	return new Air();
}

Nature Air::get_nature()
{
	return air;
}

bool Air::can_burn()
{
	return true;
}

sf::Color Air::get_color()
{
	return sf::Color(0, 0, 0);
}



// Met à jour le matériaux

void Air::update(int x, int y)
{
}



// Met à jour le feu

void Air::update_fire(int x, int y)
{
	int temp = fire_level;
	fire_level -= 1;

	update_fire_propagation(x, y, 0.5);
	update_fire_movement(x, y);

	if (temp != fire_level)
		simulation.world[x][y]->draw_material(x, y);
}