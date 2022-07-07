#include "Simulator.hpp"
#include "materials/Vapor.hpp"
#include "materials/Water.hpp"

Vapor::Vapor()
{
	nature = Nature::Vapor;
	state = State::Gas;
	weight = -10;
	fire_level = 0;
	can_burn = false;
	way = rand() % 2 * 2 - 1;
	color_swtich = 0;
	salty = false;
	done = false;
}

Material* Vapor::build()
{
	return new Vapor();
}

sf::Color Vapor::get_color() const
{
	return sf::Color(0, 70, 70);
}

void Vapor::update(int x, int y)
{
	for (auto& way : Simulator::ways_4)
	{
		auto pos = dim::Vector2int(x, y) + way;

		if (Simulator::in_world(pos) && (Simulator::world[pos.x][pos.y]->nature == Nature::Ice ||
			Simulator::world[pos.x][pos.y]->nature == Nature::Snow))
		{
			delete Simulator::world[x][y];
			Simulator::world[x][y] = new Water();

			delete Simulator::world[pos.x][pos.y];
			Simulator::world[pos.x][pos.y] = new Water();

			return;
		}
	}

	if (rand_probability(0.1f) && (is_border(x, y) || is_near(x, y, State::Solid) || is_near(x, y, State::Dust)))
	{
		delete Simulator::world[x][y];
		Simulator::world[x][y] = new Water();
		return;
	}

	update_gas(x, y);
}

void Vapor::update_fire(int x, int y)
{
	fire_level = 0;
}
