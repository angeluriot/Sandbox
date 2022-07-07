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
	color_swtich = 0;
	salty = false;
	done = false;
}

Material* Ice::build()
{
	return new Ice();
}

sf::Color Ice::get_color() const
{
	return sf::Color(0, 200, 255);
}

void Ice::update(int x, int y)
{
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
