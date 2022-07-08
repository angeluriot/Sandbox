#include "Simulator.hpp"
#include "materials/Air.hpp"

Air::Air()
{
	nature = Nature::Air;
	state = State::Empty;
	weight = -1000;
	fire_level = 0;
	can_burn = true;
	way = rand() % 2 * 2 - 1;
	color_type = 0;
	salty = false;
	done = false;
}

Material* Air::build()
{
	return new Air();
}

sf::Color Air::get_color() const
{
	return sf::Color(0, 0, 0);
}

void Air::update(int x, int y) {}

void Air::update_fire(int x, int y)
{
	fire_level -= 1;
	update_fire_propagation(x, y, 0.5f);
	update_fire_movement(x, y);
}
