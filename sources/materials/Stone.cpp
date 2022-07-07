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
	color_swtich = 0;
	salty = false;
	done = false;
}

Material* Stone::build()
{
	return new Stone();
}

sf::Color Stone::get_color() const
{
	return sf::Color(150, 150, 150);
}

void Stone::update(int x, int y) {}

void Stone::update_fire(int x, int y)
{
	fire_level = 0;
}
