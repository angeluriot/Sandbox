#include "simulation.h"
#include "materials/snow.h"
#include "materials/ice.h"

Snow::Snow()
{
	state = dust;
	weight = 100;
	fire_level = 0;
	way = rand() % 2 * 2 - 1;
	color_swtich = 0;
	done = false;
}

Material* Snow::init()
{
	return new Snow();
}

Nature Snow::get_nature()
{
	return snow;
}

bool Snow::can_burn()
{
	return false;
}

sf::Color Snow::get_color()
{
	return sf::Color(255, 255, 255);
}



// Met à jour le matériaux

void Snow::update(int x, int y)
{
	if ((rand_probability(0.0001) and is_hot_near(x, y)) or is_fire_around(x, y) or is_near(x, y, salt))
		liquefy(x, y);

	else
		update_dust(x, y);
}



// Met à jour le feu

void Snow::update_fire(int x, int y)
{
	fire_level = 0;
	simulation.world[x][y]->draw_material(x, y);
}