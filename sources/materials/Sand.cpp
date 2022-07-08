#include "Simulator.hpp"
#include "materials/Sand.hpp"

Sand::Sand()
{
	nature = Nature::Sand;
	state = State::Dust;
	weight = 100;
	fire_level = 0;
	can_burn = false;
	way = rand() % 2 * 2 - 1;
	color_type = random_int(0, 3);
	salty = false;
	done = false;
}

Material* Sand::build()
{
	return new Sand();
}

sf::Color Sand::get_color() const
{
	if (color_type == 0)
		return sf::Color(205, 125, 0);

	if (color_type == 1)
		return sf::Color(220, 140, 15);

	return sf::Color(235, 155, 30);
}

void Sand::update(int x, int y)
{
	update_dust(x, y);
}

void Sand::update_fire(int x, int y)
{
	fire_level = 0;
}
