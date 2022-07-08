#include "Simulator.hpp"
#include "materials/Ash.hpp"

Ash::Ash()
{
	nature = Nature::Ash;
	state = State::Dust;
	weight = 100;
	fire_level = 0;
	can_burn = false;
	way = rand() % 2 * 2 - 1;
	color_type = random_int(0, 5);
	salty = false;
	done = false;
}

Material* Ash::build()
{
	return new Ash();
}

sf::Color Ash::get_color() const
{
	if (color_type == 0)
		return sf::Color(80, 80, 80);

	if (color_type == 1)
		return sf::Color(100, 100, 100);

	if (color_type == 2)
		return sf::Color(120, 120, 120);

	if (color_type == 3)
		return sf::Color(140, 140, 140);

	return sf::Color(160, 160, 160);
}

void Ash::update(int x, int y)
{
	update_dust(x, y);
}

void Ash::update_fire(int x, int y)
{
	fire_level = 0;
}
