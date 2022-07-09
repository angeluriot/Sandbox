#include "Simulator.hpp"
#include "materials/Vapor.hpp"
#include "materials/Water.hpp"
#include "materials/Air.hpp"

Vapor::Vapor()
{
	nature = Nature::Vapor;
	state = State::Gas;
	weight = -10;
	fire_level = 0;
	can_burn = false;
	way = rand() % 2 * 2 - 1;
	color_type = random_int(0, 3);
	salty = false;
	done = false;
}

Material* Vapor::build()
{
	return new Vapor();
}

sf::Color Vapor::get_color() const
{
	if (color_type == 0)
		return sf::Color(0, 60, 70);

	if (color_type == 1)
		return sf::Color(0, 65, 70);

	return sf::Color(0, 70, 70);
}

void Vapor::update(int x, int y)
{
	// Condensation conditions

	for (auto& way : Simulator::ways_4)
	{
		auto pos = dim::Vector2int(x, y) + way;

		if (Simulator::in_world(pos) && (Simulator::world[pos.x][pos.y]->nature == Nature::Ice ||
			Simulator::world[pos.x][pos.y]->nature == Nature::Snow))
		{
			delete Simulator::world[x][y];
			Simulator::world[x][y] = new Water();

			delete Simulator::world[pos.x][pos.y];

			if (Simulator::world[pos.x][pos.y]->nature == Nature::Ice || rand_probability(0.5f))
				Simulator::world[pos.x][pos.y] = new Water();
			else
				Simulator::world[pos.x][pos.y] = new Air();

			return;
		}
	}

	if (rand_probability(0.03f) && (is_border(x, y) || is_near(x, y, State::Solid) || is_near(x, y, State::Dust)))
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
