#include "simulation.h"
#include "materials/oil.h"

Oil::Oil()
{
	state = liquid;
	weight = 5;
	fire_level = 0;
	way = rand() % 2 * 2 - 1;
	color_swtich = 0;
	done = false;
}

Material* Oil::init()
{
	return new Oil();
}

Nature Oil::get_nature()
{
	return oil;
}

bool Oil::can_burn()
{
	return true;
}

sf::Color Oil::get_color()
{
	return sf::Color(213, 222, 0);
}



// Met à jour le matériaux

void Oil::update(int x, int y)
{
	update_liquid(x, y);
}



// Met à jour le feu

void Oil::update_fire(int x, int y)
{
	int temp = fire_level;
	fire_level -= 1;

	update_burn(x, y, 300., 0.);
	update_fire_propagation(x, y, 1.);

	if (temp != fire_level)
		simulation.world[x][y]->draw_material(x, y);
}