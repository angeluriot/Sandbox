#include "Simulator.hpp"
#include "materials/Gas.hpp"

Gas::Gas()
{
	nature = Nature::Gas;
	state = State::Gas;
	weight = -20;
	fire_level = 0;
	can_burn = true;
	way = rand() % 2 * 2 - 1;
	color_type = random_int(0, 3);
	salty = false;
	done = false;
}

Material* Gas::build()
{
	return new Gas();
}

sf::Color Gas::get_color() const
{
	if (color_type == 0)
		return sf::Color(60, 60, 60);

	if (color_type == 1)
		return sf::Color(65, 65, 65);

	return sf::Color(70, 70, 70);
}

void Gas::update(int x, int y)
{
	update_gas(x, y);
}

void Gas::update_fire(int x, int y)
{
	fire_level -= 1;
	update_burn(x, y, 30.f, 0.f);
	update_fire_propagation(x, y, 4.f);
}
