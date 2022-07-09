#include "Simulator.hpp"
#include "materials/Acid.hpp"
#include "materials/Air.hpp"

Acid::Acid()
{
	nature = Nature::Acid;
	state = State::Liquid;
	weight = 9;
	fire_level = 0;
	can_burn = false;
	way = rand() % 2 * 2 - 1;
	color_type = rand_probability(0.05f) ? 0 : 1;
	salty = false;
	done = false;
}

Material* Acid::build()
{
	return new Acid();
}

sf::Color Acid::get_color() const
{
	if (color_type == 0)
		return sf::Color(150, 255, 30);

	return sf::Color(50, 255, 0);
}

void Acid::update(int x, int y)
{
	// Dissolve materials

	if (rand_probability(0.01f))
		for (auto& pos : Simulator::ways_8)
			if (Simulator::in_world(x + pos.x, y + pos.y) &&
				(Simulator::world[x + pos.x][y + pos.y]->state == State::Solid ||
				Simulator::world[x + pos.x][y + pos.y]->state == State::Dust))
			{
				delete Simulator::world[x + pos.x][y + pos.y];
				delete Simulator::world[x][y];

				Simulator::world[x + pos.x][y + pos.y] = new Air();
				Simulator::world[x][y] = new Air();

				return;
			}

	update_liquid(x, y);
}

void Acid::update_fire(int x, int y)
{
	fire_level = 0;
}
