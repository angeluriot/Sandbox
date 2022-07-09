#include "Simulator.hpp"
#include "materials/Water.hpp"
#include "materials/Vapor.hpp"

Water::Water()
{
	nature = Nature::Water;
	state = State::Liquid;
	weight = 10;
	fire_level = 0;
	can_burn = false;
	way = rand() % 2 * 2 - 1;
	color_type = 0;
	salty = false;
	done = false;
}

Material* Water::build()
{
	return new Water();
}

sf::Color Water::get_color() const
{
	if (salty)
		return sf::Color(20, 100, 255);
	else
		return sf::Color(10, 70, 255);
}

void Water::update(int x, int y)
{
	// Turn off fire

	for (auto& way : Simulator::ways_4)
	{
		auto pos = dim::Vector2int(x, y) + way;

		if (Simulator::in_world(pos) && Simulator::world[pos.x][pos.y]->fire_level > 0)
		{
			if (Simulator::world[pos.x][pos.y]->nature == Nature::Lava)
				Simulator::world[pos.x][pos.y]->fire_level -= 1;
			else
				Simulator::world[pos.x][pos.y]->fire_level = 0;

			delete Simulator::world[x][y];
			Simulator::world[x][y] = new Vapor();

			return;
		}
	}

	update_liquid(x, y);
}

void Water::update_fire(int x, int y)
{
	fire_level = 0;
}
