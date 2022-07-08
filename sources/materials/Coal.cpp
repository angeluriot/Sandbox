#include "Simulator.hpp"
#include "materials/Coal.hpp"

Coal::Coal()
{
	nature = Nature::Coal;
	state = State::Solid;
	weight = 100;
	fire_level = 0;
	can_burn = true;
	way = rand() % 2 * 2 - 1;
	color_type = 0;
	salty = false;
	done = false;
}

Material* Coal::build()
{
	return new Coal();
}

sf::Color Coal::get_color() const
{
	return sf::Color(30, 30, 30);
}

void Coal::update(int x, int y) {}

void Coal::update_fire(int x, int y)
{
	fire_level -= 1;
	update_burn(x, y, 3000.f, 0.5f);
	update_fire_propagation(x, y, 0.5f);
}
