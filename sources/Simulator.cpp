#include "simulation.h"
#include "button.h"
#include <iostream>



// Crée une simulation à partir des données du menu
Simulation::Simulation()
{
}



// Recrrée une simulation à partir des données du menu

void Simulation::restart(const Menu& menu)
{
	pixels_size = menu.variables[0].int_value;
	world_width = floor((double)(menu.width - (SIZE_BUTTON + 2. * DISTANCE_BUTTON_X)) / (double)pixels_size);
	world_height = floor((double)menu.height / (double)pixels_size);

	delete brush;
	brush = new Sand();

	texture.create(menu.width, menu.height);
	texture.clear(sf::Color::Black);
	texture.display();
	sprite = sf::Sprite(texture.getTexture());

	for (auto line : world)
	{
		for (auto mat : line)
			delete mat;
	}

	world.clear();

	for (int i = 0; i < world_width; i++)
	{
		world.push_back({});

		for (int j = 0; j < world_height; j++)
			world[i].push_back(new Air());
	}

	material.setSize(sf::Vector2f(pixels_size, pixels_size));

	ways_4 = { Position(-1, 0), Position(0, -1), Position(0, 1), Position(1, 0) };
	ways_8 = { Position(-1, -1), Position(-1, 0), Position(-1, 1), Position(0, -1), Position(0, 1), Position(1, -1), Position(1, 0), Position(1, 1) };
}



// Empèche de choisir une case en dehors du tableau

bool Simulation::in_world(int x, int y)
{
	return (x >= 0 and y >= 0 and x < world_width and y < world_height);
}



// Ajoute des matériaux en fonction du clic de la souris

void Simulation::imputs(const sf::Vector2i& mouse_position)
{
	int p_x = floor((double)mouse_position.x / (double)pixels_size);
	int p_y = floor((double)mouse_position.y / (double)pixels_size);

	int x;
	int y;

	if (brush->state == solid or (brush->state == empty and brush->fire_level == 0))
	{
		for (int i = p_x - BRUSH_SIZE; i <= p_x + BRUSH_SIZE; i++)
		{
			for (int j = p_y - BRUSH_SIZE; j <= p_y + BRUSH_SIZE; j++)
			{
				if (in_world(i, j) and distance(p_x, p_y, i, j) < BRUSH_SIZE)
				{
					delete world[i][j];
					world[i][j] = brush->init();
					world[i][j]->draw_material(i, j);
				}
			}
		}
	}

	else
	{
		for (int i = 0; i < BRUSH_SPEED; i++)
		{
			x = random_int(p_x - BRUSH_SIZE, p_x + BRUSH_SIZE);
			y = random_int(p_y - BRUSH_SIZE, p_y + BRUSH_SIZE);

			if (in_world(x, y) and distance(p_x, p_y, x, y) < BRUSH_SIZE and brush->state >= world[x][y]->state)
			{
				if (brush->fire_level > 0 and brush->state == empty)
				{
					world[x][y]->fire_level = FIRE_MAX + 1;
					world[x][y]->draw_material(x, y);
				}

				else
				{
					delete world[x][y];
					world[x][y] = brush->init();
					world[x][y]->draw_material(x, y);
				}
			}
		}
	}
}



// Met à jour le monde

void Simulation::update(bool mouse_pressed, const sf::Vector2i& mouse_position)
{
	bool random_1;
	bool random_2;

	if (mouse_pressed)
		imputs(mouse_position);
	
	random_1 = rand() % 2;

	for (int i = 0; i < world_width; i++)
	{
		if (random_1)
			i = world_width - 1 - i;

		random_2 = rand() % 2;
		
		for (int j = 0; j < world_height; j++)
		{
			if (random_2)
				j = world_height - 1 - j;

			world[i][j]->update(i, j);
		}
	}

	for (int i = 0; i < world_width; i++)
	{
		for (int j = 0; j < world_height; j++)
			world[i][j]->done = false;
	}

	random_1 = rand() % 2;

	for (int i = 0; i < world_width; i++)
	{
		if (random_1)
			i = world_width - 1 - i;

		random_2 = rand() % 2;

		for (int j = 0; j < world_height; j++)
		{
			if (world[i][j]->fire_level > 0 and rand_probability(0.2))
				world[i][j]->update_fire(i, j);
		}
	}

	for (int i = 0; i < world_width; i++)
	{
		for (int j = 0; j < world_height; j++)
			world[i][j]->done = false;
	}
}



// Affiche le monde

void Simulation::draw_all()
{
	for (int i = 0; i < world_width; i++)
	{
		for (int j = 0; j < world_height; j++)
			world[i][j]->draw_material(i, j);
	}
}



// Affiche la simulation

void Simulation::draw(sf::RenderWindow& window)
{
	texture.display();
	sprite = sf::Sprite(texture.getTexture());
	sprite.setPosition(SIZE_BUTTON + 2. * DISTANCE_BUTTON_X, 0);
	window.draw(sprite);
}
