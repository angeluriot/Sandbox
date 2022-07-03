#include "simulation.h"
#include "materials/acid.h"

Acid::Acid()
{
	state = liquid;
	weight = 9;
	fire_level = 0;
	way = rand() % 2 * 2 - 1;
	color_swtich = 0;
	done = false;
}

Material* Acid::init()
{
	return new Acid();
}

Nature Acid::get_nature()
{
	return acid;
}

bool Acid::can_burn()
{
	return false;
}

sf::Color Acid::get_color()
{
	return sf::Color(50, 255, 0);
}



// Met à jour le matériaux

void Acid::update(int x, int y)
{
	if (rand_probability(0.01) and corrosion(x, y))
		return;

	update_liquid(x, y);
}



// Met à jour le feu

void Acid::update_fire(int x, int y)
{
	fire_level = 0;
	simulation.world[x][y]->draw_material(x, y);
}



// Regarde si il a quelque chose de solide autour

bool corrosion(int x, int y)
{
	for (Position pos : simulation.ways_8)
	{
		if (simulation.in_world(x + pos.x, y + pos.y) and (simulation.world[x + pos.x][y + pos.y]->state == solid or simulation.world[x + pos.x][y + pos.y]->state == dust))
		{
			delete simulation.world[x + pos.x][y + pos.y];
			delete simulation.world[x][y];
			simulation.world[x + pos.x][y + pos.y] = Air().init();
			simulation.world[x][y] = Air().init();

			simulation.world[x][y]->draw_material(x, y);
			simulation.world[x + pos.x][y + pos.y]->draw_material(x + pos.x, y + pos.y);

			return true;
		}
	}

	return false;
}