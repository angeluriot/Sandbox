#include "Simulator.hpp"
#include "materials/Salt.hpp"
#include "materials/Air.hpp"

Salt::Salt()
{
	nature = Nature::Salt;
	state = State::Dust;
	weight = 100;
	fire_level = 0;
	can_burn = false;
	way = rand() % 2 * 2 - 1;
	color_type = random_int(0, 3);
	salty = false;
	done = false;
}

Material* Salt::build()
{
	return new Salt();
}

sf::Color Salt::get_color() const
{
	if (color_type == 0)
		return sf::Color(210, 210, 210);

	if (color_type == 1)
		return sf::Color(225, 225, 225);

	return sf::Color(240, 240, 240);
}

void Salt::update(int x, int y)
{
	// Dissolve in water

	if (rand_probability(0.01f))
		for (auto& way : Simulator::ways_4)
		{
			auto pos = dim::Vector2int(x, y) + way;

			if (Simulator::in_world(pos) && Simulator::world[pos.x][pos.y]->nature == Nature::Water &&
				!Simulator::world[pos.x][pos.y]->salty)
			{
				Simulator::world[pos.x][pos.y]->salty = true;

				delete Simulator::world[x][y];
				Simulator::world[x][y] = new Air();

				return;
			}
		}

	update_dust(x, y);
}

void Salt::update_fire(int x, int y)
{
	fire_level = 0;
}
