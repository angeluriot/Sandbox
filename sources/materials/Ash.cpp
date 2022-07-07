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
	color_swtich = rand() % 2;
	salty = false;
	done = false;
}

Material* Ash::build()
{
	return new Ash();
}

sf::Color Ash::get_color() const
{
	if (color_swtich)
		return sf::Color(110, 110, 110);
	else
		return sf::Color(170, 170, 170);
}

void Ash::update(int x, int y)
{
	update_dust(x, y);
}

void Ash::update_fire(int x, int y)
{
	fire_level = 0;
}
