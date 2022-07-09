#include "Simulator.hpp"
#include "materials/Snow.hpp"
#include "materials/Water.hpp"
#include "materials/Air.hpp"

Snow::Snow()
{
	nature = Nature::Snow;
	state = State::Dust;
	weight = 100;
	fire_level = 0;
	can_burn = false;
	way = rand() % 2 * 2 - 1;
	color_type = random_int(0, 3);
	salty = false;
	done = false;
}

Material* Snow::build()
{
	return new Snow();
}

sf::Color Snow::get_color() const
{
	if (color_type == 0)
		return sf::Color(245, 245, 255);

	if (color_type == 1)
		return sf::Color(250, 250, 255);

	return sf::Color(255, 255, 255);
}

void Snow::update(int x, int y)
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

	if ((rand_probability(0.0001f) && is_hot_near) || (rand_probability(0.01f) && is_around(x, y, Nature::Salt)) || is_fire_around(x, y))
	{
		delete Simulator::world[x][y];

		if (rand_probability(0.5f))
			Simulator::world[x][y] = new Water();
		else
			Simulator::world[x][y] = new Air();

		return;
	}

	update_dust(x, y);
}

void Snow::update_fire(int x, int y)
{
	fire_level = 0;
}
