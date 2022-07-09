#include "Simulator.hpp"
#include "materials/Ice.hpp"
#include "materials/Water.hpp"

Ice::Ice()
{
	nature = Nature::Ice;
	state = State::Solid;
	weight = 100;
	fire_level = 0;
	can_burn = false;
	way = rand() % 2 * 2 - 1;
	color_type = 1;
	color_type += rand_probability(0.1f) ? 0 : 1;
	color_type -= rand_probability(0.02f) ? 0 : 1;
	salty = false;
	done = false;
}

Material* Ice::build()
{
	return new Ice();
}

sf::Color Ice::get_color() const
{
	if (color_type == 0)
		return sf::Color(80, 230, 255);

	if (color_type == 1)
		return sf::Color(50, 210, 250);

	return sf::Color(65, 220, 252);
}

void Ice::update(int x, int y)
{
	// Melting conditions

	bool is_hot_near = false;

	for (auto& pos : Simulator::ways_4)
		if (!(Simulator::in_world(x + pos.x, y + pos.y) &&
			(Simulator::world[x + pos.x][y + pos.y]->nature == Nature::Ice ||
			Simulator::world[x + pos.x][y + pos.y]->nature == Nature::Snow)))
		{
			is_hot_near = true;
			break;
		}

	if ((rand_probability(0.0001f) && is_hot_near) || is_fire_around(x, y))
	{
		delete Simulator::world[x][y];
		Simulator::world[x][y] = new Water();
	}
}

void Ice::update_fire(int x, int y)
{
	fire_level = 0;
}
