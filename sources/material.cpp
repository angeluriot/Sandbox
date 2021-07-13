#include "material.h"
#include "simulation.h"
#include <iostream>



// Contruit un matériaux

Material::Material()
{
	state = empty;
	weight = 0;
	fire_level = 0;
	way = rand() % 2 * 2 - 1;
	color_swtich = 0;
	done = false;
}



// Construit un materiaux à partir d'un autre matériaux

Material::Material(const Material& material)
{
	*this = material;
}



// Assignation

void Material::operator=(const Material& material)
{
	state = material.state;
	weight = material.weight;
	fire_level = material.fire_level;
	way = material.way;
	color_swtich = material.color_swtich;
	done = material.done;

	salty = material.salty;
}



// Regarde si il y a le matériaux donné autour

bool Material::is_around(int x, int y, Nature nature)
{
	for (Position pos : simulation.ways_8)
	{
		if (simulation.in_world(x + pos.x, y + pos.y) and simulation.world[x + pos.x][y + pos.y]->get_nature() == nature)
			return true;
	}

	return false;
}



// Regarde si il a quelque chose de solide autour

bool Material::is_solid_around(int x, int y)
{
	for (Position pos : simulation.ways_8)
	{
		if (!simulation.in_world(x + pos.x, y + pos.y) or (simulation.in_world(x + pos.x, y + pos.y) and (simulation.world[x + pos.x][y + pos.y]->state == solid or simulation.world[x + pos.x][y + pos.y]->state == dust)))
			return true;
	}

	return false;
}



// Regarde si il n'y a pas le matériaux donné autour

bool Material::is_not_around(int x, int y, Nature nature)
{
	for (Position pos : simulation.ways_8)
	{
		if (!(simulation.in_world(x + pos.x, y + pos.y) and simulation.world[x + pos.x][y + pos.y]->get_nature() == nature))
			return true;
	}

	return false;
}



// Regarde si il y a le matériaux donné à côté

bool Material::is_near(int x, int y, Nature nature)
{
	for (Position pos : simulation.ways_4)
	{
		if (simulation.in_world(x + pos.x, y + pos.y) and simulation.world[x + pos.x][y + pos.y]->get_nature() == nature)
			return true;
	}

	return false;
}



// Regarde si il n'y a pas le matériaux donné à côté

bool Material::is_not_near(int x, int y, Nature nature)
{
	for (Position pos : simulation.ways_4)
	{
		if (!(simulation.in_world(x + pos.x, y + pos.y) and simulation.world[x + pos.x][y + pos.y]->get_nature() == nature))
			return true;
	}

	return false;
}



// Dit si le matériaux est un fluide

bool Material::is_fluid()
{
	return (state == liquid or state == gas or state == empty);
}



// Note la case comme étant faite

void Material::set_done()
{
	if (state != empty)
		done = true;
}



// Dit si il est possible de se déplacer

bool Material::can_move_to(int x, int y, int target_x, int target_y)
{
	return (simulation.in_world(target_x, target_y) and !done and !simulation.world[target_x][target_y]->done and simulation.world[target_x][target_y]->is_fluid() and weight > simulation.world[target_x][target_y]->weight);
}



// Déplace une case

void Material::move_to(int x, int y, int target_x, int target_y)
{
	simulation.world[x][y] = simulation.world[target_x][target_y];
	simulation.world[target_x][target_y] = this;

	simulation.world[x][y]->draw_material(x, y);
	simulation.world[target_x][target_y]->draw_material(target_x, target_y);

	simulation.world[x][y]->set_done();
	set_done();
}



// Déplace le feu

void Material::fire_move_to(int x, int y, int target_x, int target_y)
{
	if (simulation.in_world(target_x, target_y) and !done and !simulation.world[target_x][target_y]->done and simulation.world[target_x][target_y]->can_burn() and simulation.world[target_x][target_y]->fire_level < fire_level)
	{
		int temp = fire_level;
		fire_level = simulation.world[target_x][target_y]->fire_level;
		simulation.world[target_x][target_y]->fire_level = temp;

		simulation.world[x][y]->draw_material(x, y);
		simulation.world[target_x][target_y]->draw_material(target_x, target_y);

		simulation.world[x][y]->set_done();
		simulation.world[target_x][target_y]->set_done();
	}
}



// Fait se répandre le feu

void Material::fire_spread_to(int x, int y, int target_x, int target_y)
{
	if (simulation.in_world(target_x, target_y) and simulation.world[target_x][target_y]->fire_level < fire_level - 1 and simulation.world[target_x][target_y]->can_burn())
	{
		simulation.world[target_x][target_y]->fire_level = fire_level - random_int(0, 2);
		simulation.world[target_x][target_y]->draw_material(target_x, target_y);
	}
}



// Regarde si il y a du feu autour

bool Material::is_fire_around(int x, int y)
{
	for (Position pos : simulation.ways_8)
	{
		if (simulation.in_world(x + pos.x, y + pos.y) and simulation.world[x + pos.x][y + pos.y]->fire_level > 0)
			return true;
	}

	return false;
}



// Eteint le feu

bool Material::turn_off_fire(int x, int y)
{
	for (Position pos : simulation.ways_4)
	{
		if (simulation.in_world(x + pos.x, y + pos.y) and simulation.world[x + pos.x][y + pos.y]->fire_level > 0)
		{
			if (simulation.world[x + pos.x][y + pos.y]->get_nature() == lava)
				simulation.world[x + pos.x][y + pos.y]->fire_level -= 1;

			else
				simulation.world[x + pos.x][y + pos.y]->fire_level = 0;

			simulation.world[x + pos.x][y + pos.y]->draw_material(x + pos.x, y + pos.y);
			return true;
		}
	}

	return false;
}



// Met à jour avec un comportement de sable

void Material::update_dust(int x, int y)
{
	if (can_move_to(x, y, x, y + 1))
		move_to(x, y, x, y + 1);

	else if (can_move_to(x, y, x - way, y + 1))
		move_to(x, y, x - way, y + 1);

	else if (can_move_to(x, y, x + way, y + 1))
		move_to(x, y, x + way, y + 1);
}



// Met à jour avec un comportemment de liquide

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
}



// Met à jour avec un comportement de gaz

void Material::update_gas(int x, int y)
{
	std::array<double, 8> probabilities = { 15. / 100., 10. / 85., 10. / 75., 25. / 65., 5. / 40., 15. / 35., 10. / 20., 1. };
	int count = 0;

	for (Position pos : simulation.ways_8)
	{
		if (rand_probability(probabilities[count]))
		{
			if (can_move_to(x, y, x + pos.x, y + pos.y))
				move_to(x, y, x + pos.x, y + pos.y);

			return;
		}

		count++;
	}
}



// Met à jour le feu si le matériaux brûle

void Material::update_burn(int x, int y, const double& time, const double& ash_probability)
{
	if (fire_level > 0)
	{
		if (is_around(x, y, air))
		{
			fire_level = FIRE_MAX;
			simulation.world[x][y]->draw_material(x, y);
		}

		else
			fire_level = 0;

		if (rand_probability(1. / time))
		{
			if (rand_probability(ash_probability))
				burned(x, y);

			else
				disappeared(x, y);
		}
	}
}



// Met à jour le feu si le matériaux explose

void Material::update_explosion(int x, int y, const double& time)
{
	if (fire_level > 0)
	{
		fire_level = FIRE_MAX;
		simulation.world[x][y]->draw_material(x, y);

		if (rand_probability(1. / time))
			disappeared(x, y);
	}
}



// Met à jour la propagation du feu

void Material::update_fire_propagation(int x, int y, const double& speed)
{
	if (fire_level >= FIRE_MAX - 1)
	{
		for (Position pos : simulation.ways_4)
		{
			if (rand_probability(speed * (1. / 4.)))
				fire_spread_to(x, y, x + pos.x, y + pos.y);
		}
	}
}



// Met à jour le déplacement du feu

void Material::update_fire_movement(int x, int y)
{
	if (fire_level > 0)
	{
		if (rand_probability(8. / 10.))
			fire_move_to(x, y, x, y - 1);

		else if (rand_probability(1. / 2.))
			fire_move_to(x, y, x - 1, y - 1);

		else
			fire_move_to(x, y, x + 1, y - 1);
	}
}



// Fait disparaître la case

void Material::disappeared(int x, int y)
{
	delete simulation.world[x][y];
	simulation.world[x][y] = Air().init();
	simulation.world[x][y]->draw_material(x, y);
}



// Transforme la case en cendre

void Material::burned(int x, int y)
{
	delete simulation.world[x][y];
	simulation.world[x][y] = Ash().init();
	simulation.world[x][y]->draw_material(x, y);
}



// Fait évaporer l'eau

void Material::evaporate(int x, int y)
{
	delete simulation.world[x][y];
	simulation.world[x][y] = Vapor().init();
	simulation.world[x][y]->draw_material(x, y);
}



// Transforme en eau

void Material::liquefy(int x, int y)
{
	delete simulation.world[x][y];
	simulation.world[x][y] = Water().init();
	simulation.world[x][y]->draw_material(x, y);
}


// Fait durcir la lave

void Material::harden(int x, int y)
{
	delete simulation.world[x][y];
	simulation.world[x][y] = Stone().init();
	simulation.world[x][y]->draw_material(x, y);
}



// Affiche la case

void Material::draw_material(int x, int y)
{
	simulation.material.setPosition(x * simulation.pixels_size, y * simulation.pixels_size);
	simulation.material.setFillColor(get_color());
	simulation.texture.draw(simulation.material);

	if (fire_level > 0 and get_nature() != lava)
		draw_fire(simulation);
}



// Affiche le feu

void Material::draw_fire(Simulation& simulation)
{
	if (fire_level > FIRE_MAX / 3.)
		simulation.material.setFillColor(sf::Color(255, (255. / (FIRE_MAX * (2. / 3.))) * (fire_level - (FIRE_MAX / 3.)), 0));

	else
		simulation.material.setFillColor(sf::Color(255, 0, 0, (255. / (FIRE_MAX / 3.)) * fire_level));

	simulation.texture.draw(simulation.material);
}