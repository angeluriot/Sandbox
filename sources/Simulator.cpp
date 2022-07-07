#include "Simulator.hpp"
#include "materials/Air.hpp"
#include "materials/Wood.hpp"

dim::Vector2int						Simulator::world_size = dim::Vector2int(100, std::floor(100.f / (16.f / 9.f)));
std::vector<std::vector<Material*>>	Simulator::world;
std::vector<dim::Vector2int>		Simulator::world_ids;
Material*							Simulator::brush_type = new Wood();
int									Simulator::brush_size = 10;
sf::Image*							Simulator::image = nullptr;
sf::Texture*						Simulator::texture = nullptr;
sf::Sprite*							Simulator::sprite = nullptr;

const std::array<dim::Vector2int, 4> Simulator::ways_4 = {
	dim::Vector2int(-1, 0),
	dim::Vector2int(0, -1),
	dim::Vector2int(0, 1),
	dim::Vector2int(1, 0)
};

const std::array<dim::Vector2int, 8> Simulator::ways_8 = {
	dim::Vector2int(-1, -1),
	dim::Vector2int(-1, 0),
	dim::Vector2int(-1, 1),
	dim::Vector2int(0, -1),
	dim::Vector2int(0, 1),
	dim::Vector2int(1, -1),
	dim::Vector2int(1, 0),
	dim::Vector2int(1, 1)
};

void Simulator::init()
{
	image = new sf::Image();
	texture = new sf::Texture();
	sprite = new sf::Sprite();

	reset();
}

void Simulator::reset()
{
	for (auto& line : world)
		for (auto& cell : line)
			delete cell;

	world.clear();
	world.resize(world_size.x, std::vector<Material*>(world_size.y));

	for (auto& line : world)
		for (auto& cell : line)
			cell = new Air();

	world_ids.clear();
	world_ids.resize(world_size.x * world_size.y);

	for (int x = 0; x < world_size.x; x++)
		for (int y = 0; y < world_size.y; y++)
			world_ids[x * world_size.y + y] = dim::Vector2int(x, y);

	image->create(world_size.x, world_size.y, sf::Color::Black);
	texture->create(world_size.x, world_size.y);
}

dim::Vector2int Simulator::screen_to_world(dim::Vector2int position)
{
	return dim::Vector2int(((float)position.x / (float)dim::Window::get_size().x) * world_size.x,
		((float)position.y / (float)dim::Window::get_size().y) * world_size.y);
}

dim::Vector2int Simulator::world_to_screen(dim::Vector2int position)
{
	return dim::Vector2int(((float)position.x / (float)world_size.x) * dim::Window::get_size().x,
		((float)position.y / (float)world_size.y) * dim::Window::get_size().y);
}

bool Simulator::in_world(dim::Vector2int position)
{
	return in_world(position.x, position.y);
}

bool Simulator::in_world(int x, int y)
{
	return (x >= 0 && y >= 0 && x < world_size.x && y < world_size.y);
}

void Simulator::inputs()
{
	dim::Vector2int position = screen_to_world(sf::Mouse::getPosition());

	if (brush_type->state == Material::State::Solid || (brush_type->state == Material::State::Empty && brush_type->fire_level == 0))
		for (int x = position.x - brush_size / 2; x <= position.x + brush_size / 2; x++)
			for (int y = position.y - brush_size / 2; y <= position.y + brush_size / 2; y++)
				if (in_world(x, y) && distance(position, x, y) < brush_size / 2)
				{
					delete world[x][y];
					world[x][y] = brush_type->build();
				}

	else
		for (int i = 0; i < brush_size / 2; i++)
		{
			int x = random_int(position.x - brush_size / 2, position.x + brush_size / 2 + 1);
			int y = random_int(position.y - brush_size / 2, position.y + brush_size / 2 + 1);

			if (in_world(x, y) && distance(position, x, y) < brush_size / 2 && brush_type->state >= world[x][y]->state)
			{
				if (brush_type->fire_level > 0 && brush_type->state == Material::State::Empty)
					world[x][y]->fire_level = Material::fire_max;

				else
				{
					delete world[x][y];
					world[x][y] = brush_type->build();
				}
			}
		}
}

void Simulator::update()
{
	for (int i = 0; i < world_ids.size(); i++)
		std::swap(world_ids[i], world_ids[random_int(0, world_ids.size())]);

	for (auto& pos : world_ids)
		world[pos.x][pos.y]->update(pos.x, pos.y);

	for (auto& line : world)
		for (auto& cell : line)
			cell->done = false;

	for (auto& pos : world_ids)
		if (world[pos.x][pos.y]->fire_level > 0 && rand_probability(0.2f))
			world[pos.x][pos.y]->update_fire(pos.x, pos.y);

	for (auto& line : world)
		for (auto& cell : line)
			cell->done = false;
}

void Simulator::draw()
{
	for (int x = 0; x < world_size.x; x++)
		for (int y = 0; y < world_size.y; y++)
		{
			sf::Color color = world[x][y]->get_color();
			sf::Color fire_color = world[x][y]->get_fire_color();
			float opacity = (float)fire_color.a / 255.f;

			/*image->setPixel(x, y, sf::Color(
				(1 - opacity) * color.r + opacity * fire_color.r,
				(1 - opacity) * color.g + opacity * fire_color.g,
				(1 - opacity) * color.b + opacity * fire_color.b,
				255));*/

			image->setPixel(x, y, sf::Color::Red);
		}

	texture->loadFromImage(*image);
	sprite->setTexture(*texture);
	dim::Window::draw(*sprite);
}
