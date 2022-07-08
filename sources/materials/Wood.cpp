#include "Simulator.hpp"
#include "materials/Wood.hpp"

Wood::Wood()
{
	nature = Nature::Wood;
	state = State::Solid;
	weight = 100;
	fire_level = 0;
	can_burn = true;
	way = rand() % 2 * 2 - 1;
	color_type = 0;
	salty = false;
	done = false;
}

Material* Wood::build()
{
	return new Wood();
}

sf::Color Wood::get_color() const
{
	return sf::Color(134, 57, 11);
}

void Wood::update(int x, int y) {}

void Wood::update_fire(int x, int y)
{
	fire_level -= 1;
	update_burn(x, y, 1000.f, 0.2f);
	update_fire_propagation(x, y, 0.5f);
}
