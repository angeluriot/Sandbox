#include "Material.hpp"
#include "Simulator.hpp"
#include "materials/Air.hpp"
#include "materials/Ash.hpp"

bool Material::is_near(int x, int y, Nature nature)
{
	for (auto& pos : Simulator::ways_4)
		if (Simulator::in_world(x + pos.x, y + pos.y) && Simulator::world[x + pos.x][y + pos.y]->nature == nature)
			return true;

	return false;
}

bool Material::is_not_near(int x, int y, Nature nature)
{
	for (auto& pos : Simulator::ways_4)
		if (!(Simulator::in_world(x + pos.x, y + pos.y) && Simulator::world[x + pos.x][y + pos.y]->nature == nature))
			return true;

	return false;
}

bool Material::is_around(int x, int y, Nature nature)
{
	for (auto& pos : Simulator::ways_8)
		if (Simulator::in_world(x + pos.x, y + pos.y) && Simulator::world[x + pos.x][y + pos.y]->nature == nature)
			return true;

	return false;
}

bool Material::is_not_around(int x, int y, Nature nature)
{
	for (auto& pos : Simulator::ways_8)
		if (!(Simulator::in_world(x + pos.x, y + pos.y) && Simulator::world[x + pos.x][y + pos.y]->nature == nature))
			return true;

	return false;
}

bool Material::is_near(int x, int y, State state)
{
	for (auto& pos : Simulator::ways_4)
		if (Simulator::in_world(x + pos.x, y + pos.y) && Simulator::world[x + pos.x][y + pos.y]->state == state)
			return true;

	return false;
}

bool Material::is_not_near(int x, int y, State state)
{
	for (auto& pos : Simulator::ways_4)
		if (!(Simulator::in_world(x + pos.x, y + pos.y) && Simulator::world[x + pos.x][y + pos.y]->state == state))
			return true;

	return false;
}

bool Material::is_around(int x, int y, State state)
{
	for (auto& pos : Simulator::ways_8)
		if (Simulator::in_world(x + pos.x, y + pos.y) && Simulator::world[x + pos.x][y + pos.y]->state == state)
			return true;

	return false;
}

bool Material::is_not_around(int x, int y, State state)
{
	for (auto& pos : Simulator::ways_8)
		if (!(Simulator::in_world(x + pos.x, y + pos.y) && Simulator::world[x + pos.x][y + pos.y]->state == state))
			return true;

	return false;
}

bool Material::is_border(int x, int y)
{
	for (auto& pos : Simulator::ways_4)
		if (!Simulator::in_world(x + pos.x, y + pos.y))
			return true;

	return false;
}

bool Material::is_fluid() const
{
	return (state == State::Liquid || state == State::Gas || state == State::Empty);
}

void Material::set_done()
{
	if (state != State::Empty)
		done = true;
}

bool Material::can_move_to(int x, int y, int target_x, int target_y) const
{
	return (Simulator::in_world(target_x, target_y) && !done && !Simulator::world[target_x][target_y]->done &&
		Simulator::world[target_x][target_y]->is_fluid() && weight > Simulator::world[target_x][target_y]->weight);
}

void Material::move_to(int x, int y, int target_x, int target_y)
{
	std::swap(Simulator::world[x][y], Simulator::world[target_x][target_y]);

	set_done();
	Simulator::world[x][y]->set_done();
}

void Material::fire_move_to(int x, int y, int target_x, int target_y)
{
	if (Simulator::in_world(target_x, target_y) && !done && !Simulator::world[target_x][target_y]->done &&
		Simulator::world[target_x][target_y]->can_burn && Simulator::world[target_x][target_y]->fire_level < fire_level)
	{
		std::swap(fire_level, Simulator::world[target_x][target_y]->fire_level);

		set_done();
		Simulator::world[target_x][target_y]->set_done();
	}
}

void Material::fire_spread_to(int x, int y, int target_x, int target_y)
{
	if (Simulator::in_world(target_x, target_y) && Simulator::world[target_x][target_y]->fire_level < fire_level - 1 &&
		Simulator::world[target_x][target_y]->can_burn)
		Simulator::world[target_x][target_y]->fire_level = fire_level - random_int(0, 2);
}

bool Material::is_fire_around(int x, int y) const
{
	for (auto& pos : Simulator::ways_8)
		if (Simulator::in_world(x + pos.x, y + pos.y) && Simulator::world[x + pos.x][y + pos.y]->fire_level > 0)
			return true;

	return false;
}

void Material::update_dust(int x, int y)
{
	if (can_move_to(x, y, x, y + 1))
		move_to(x, y, x, y + 1);

	else if (can_move_to(x, y, x - way, y + 1))
		move_to(x, y, x - way, y + 1);

	else if (can_move_to(x, y, x + way, y + 1))
		move_to(x, y, x + way, y + 1);
}

void Material::update_liquid(int x, int y)
{
	if (can_move_to(x, y, x, y + 1))
		move_to(x, y, x, y + 1);

	else if (can_move_to(x, y, x - way, y + 1))
		move_to(x, y, x - way, y + 1);

	else if (can_move_to(x, y, x + way, y + 1))
		move_to(x, y, x + way, y + 1);

	else if (can_move_to(x, y, x - way, y))
		move_to(x, y, x - way, y);

	else if (can_move_to(x, y, x + way, y))
	{
		move_to(x, y, x + way, y);
		way = -way;
	}

	// Moves in the liquid
	else if (rand_probability(0.03f))
	{
		auto pos = dim::Vector2int(x, y) + Simulator::ways_4[random_int(0, 4)];

		if (Simulator::in_world(pos) && Simulator::world[x][y]->nature == Simulator::world[pos.x][pos.y]->nature)
			std::swap(Simulator::world[x][y], Simulator::world[pos.x][pos.y]);
	}
}

void Material::update_gas(int x, int y)
{
	std::array<float, 8> probabilities = { 15.f / 100.f, 10.f / 85.f, 10.f / 75.f, 25.f / 65.f, 5.f / 40.f, 15.f / 35.f, 10.f / 20.f, 1.f };
	int count = 0;

	for (auto& pos : Simulator::ways_8)
	{
		if (rand_probability(probabilities[count]))
		{
			if (can_move_to(x, y, x + pos.x, y + pos.y))
				move_to(x, y, x + pos.x, y + pos.y);

			break;
		}

		count++;
	}

	// Moves in the gas
	auto pos = dim::Vector2int(x, y) + Simulator::ways_4[random_int(0, 4)];

	if (Simulator::in_world(pos) && Simulator::world[x][y]->nature == Simulator::world[pos.x][pos.y]->nature)
		std::swap(Simulator::world[x][y], Simulator::world[pos.x][pos.y]);
}

void Material::update_burn(int x, int y, float time, float ash_probability)
{
	if (fire_level > 0)
	{
		if (is_around(x, y, Nature::Air))
			fire_level = fire_max;
		else
			fire_level = 0;

		if (rand_probability(1.f / time))
		{
			delete Simulator::world[x][y];

			if (rand_probability(ash_probability))
				Simulator::world[x][y] = new Ash();
			else
				Simulator::world[x][y] = new Air();
		}
	}
}

void Material::update_fire_propagation(int x, int y, float speed)
{
	if (fire_level >= fire_max - 1)
		for (auto& pos : Simulator::ways_4)
			if (rand_probability(speed * (1.f / 4.f)))
				fire_spread_to(x, y, x + pos.x, y + pos.y);
}

void Material::update_fire_movement(int x, int y)
{
	if (fire_level > 0)
	{
		if (rand_probability(8.f / 10.f))
			fire_move_to(x, y, x, y - 1);

		else if (rand_probability(1.f / 2.f))
			fire_move_to(x, y, x - 1, y - 1);

		else
			fire_move_to(x, y, x + 1, y - 1);
	}
}

sf::Color Material::get_fire_color() const
{
	if (fire_level == 0 || nature == Nature::Lava)
		return sf::Color(0, 0, 0, 0);

	if (fire_level > fire_max / 3.f)
		return sf::Color(255, (255.f / (fire_max * (2.f / 3.f))) * (fire_level - (fire_max / 3.f)), 0);

	return sf::Color(255, 0, 0, (255.f / (fire_max / 3.f)) * fire_level);
}
