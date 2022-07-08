#include "Simulator.hpp"
#include "materials/Stone.hpp"

Stone::Stone()
{
	nature = Nature::Stone;
	state = State::Solid;
	weight = 100;
	fire_level = 0;
	can_burn = false;
	way = rand() % 2 * 2 - 1;
	color_type = 1;
	color_type += rand_probability(0.015f) ? 0 : 1;
	color_type -= rand_probability(0.015f) ? 0 : 1;
	salty = false;
	done = false;
}

Material* Stone::build()
{
	return new Stone();
}

sf::Color Stone::get_color() const
{
	if (color_type == 0)
		return sf::Color(140, 140, 140);

	if (color_type == 1)
		return sf::Color(150, 150, 150);

	return sf::Color(160, 160, 160);
}

void Stone::update(int x, int y) {}

void Stone::update_fire(int x, int y)
{
	fire_level = 0;
}
