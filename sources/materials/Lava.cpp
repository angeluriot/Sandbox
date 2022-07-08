#include "Simulator.hpp"
#include "materials/Lava.hpp"
#include "materials/Stone.hpp"

Lava::Lava()
{
	nature = Nature::Lava;
	state = State::Liquid;
	weight = 15;
	fire_level = fire_max;
	can_burn = false;
	way = rand() % 2 * 2 - 1;
	color_type = random_int(0, 3);
	salty = false;
	done = false;
}

Material* Lava::build()
{
	return new Lava();
}

sf::Color Lava::get_color() const
{
	if (color_type == 0)
		return sf::Color(255, 100, 0);

	if (color_type == 1)
		return sf::Color(255, 85, 0);

	return sf::Color(255, 70, 0);
}

void Lava::update(int x, int y)
{
	if (fire_level == 0)
	{
		delete Simulator::world[x][y];
		Simulator::world[x][y] = new Stone();
		return;
	}

	update_liquid(x, y);
}

void Lava::update_fire(int x, int y)
{
	if (rand_probability(0.01f) && (is_border(x, y) || is_around(x, y, State::Solid) || is_around(x, y, State::Dust)))
		fire_level--;

	update_fire_propagation(x, y, 0.5f);
}
