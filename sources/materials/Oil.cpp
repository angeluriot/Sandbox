#include "Simulator.hpp"
#include "materials/Oil.hpp"

Oil::Oil()
{
	nature = Nature::Oil;
	state = State::Liquid;
	weight = 5;
	fire_level = 0;
	can_burn = true;
	way = rand() % 2 * 2 - 1;
	color_type = 0;
	salty = false;
	done = false;
}

Material* Oil::build()
{
	return new Oil();
}

sf::Color Oil::get_color() const
{
	return sf::Color(180, 200, 0);
}

void Oil::update(int x, int y)
{
	update_liquid(x, y);
}

void Oil::update_fire(int x, int y)
{
	fire_level -= 1;
	update_burn(x, y, 300.f, 0.f);
	update_fire_propagation(x, y, 1.f);
}
