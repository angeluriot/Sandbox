#include "Simulator.hpp"
#include "materials/Air.hpp"
#include "materials/Stone.hpp"
#include "Menu.hpp"

dim::Vector2int						Simulator::world_size;
std::vector<std::vector<Material*>>	Simulator::world;
std::vector<dim::Vector2int>		Simulator::world_ids;
Material*							Simulator::brush_type = new Stone();
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

dim::Vector2int set_world_size(int size)
{
	float ratio = (float)dim::Scene::get("Simulation").get_size().x / (float)dim::Scene::get("Simulation").get_size().y;

	if (ratio > 1.0f)
		return dim::Vector2int(size, (int)(size / ratio));
	else
		return dim::Vector2int((int)(size * ratio), size);
}

void Simulator::init()
{
	world_size = set_world_size(300);
	image = new sf::Image();
	texture = new sf::Texture();
	sprite = new sf::Sprite();
	reset();
}

void Simulator::reset()
{
	world_size = set_world_size(std::max(world_size.x, world_size.y));

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
	position -= dim::Scene::get("Simulation").get_center() - (dim::Scene::get("Simulation").get_size() / 2.f);

	return dim::Vector2int(((float)(position.x) / (float)dim::Scene::get("Simulation").get_size().x) * world_size.x,
		((float)position.y / (float)dim::Scene::get("Simulation").get_size().y) * world_size.y);
}

dim::Vector2int Simulator::world_to_screen(dim::Vector2int position)
{
	return dim::Vector2int(((float)position.x / (float)world_size.x) * dim::Scene::get("Simulation").get_size().x,
		((float)position.y / (float)world_size.y) * dim::Scene::get("Simulation").get_size().y) +
		dim::Scene::get("Simulation").get_center() - (dim::Scene::get("Simulation").get_size() / 2.f);
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
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) &&
		dim::Scene::get("Simulation").is_in(sf::Mouse::getPosition(dim::Window::get_window())))
	{
		dim::Vector2int position = screen_to_world(sf::Mouse::getPosition(dim::Window::get_window()));
		int radius = floor((float)brush_size / 2.f) + 1;

		// If the material is solid
		if (brush_type->state == Material::State::Solid || (brush_type->state == Material::State::Empty && brush_type->fire_level == 0))
			for (int x = position.x - radius; x <= position.x + radius; x++)
				for (int y = position.y - radius; y <= position.y + radius; y++)
				{
					if (in_world(x, y) && distance(position, x, y) < radius &&
						!(brush_type->nature == world[x][y]->nature && brush_type->fire_level == world[x][y]->fire_level))
					{
						delete world[x][y];
						world[x][y] = brush_type->build();
					}
				}

		// If the material moves
		else
			for (int i = 0; i < radius; i++)
			{
				int x = random_int(position.x - radius, position.x + radius + 1);
				int y = random_int(position.y - radius, position.y + radius + 1);

				if (in_world(x, y) && distance(position, x, y) <= radius && brush_type->state >= world[x][y]->state &&
					!(brush_type->nature == world[x][y]->nature && brush_type->fire_level == world[x][y]->fire_level))
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
}

void Simulator::update()
{
	static int step = 0;
	static dim::Vector2int temp = dim::Scene::get("Simulation").get_size();

	if (step < 10 || temp != dim::Scene::get("Simulation").get_size())
		reset();

	temp = dim::Scene::get("Simulation").get_size();

	for (int i = 0; i < world_ids.size(); i++)
		std::swap(world_ids[i], world_ids[random_int(0, world_ids.size())]);

	// Update each cell
	for (auto& pos : world_ids)
		world[pos.x][pos.y]->update(pos.x, pos.y);

	for (auto& line : world)
		for (auto& cell : line)
			cell->done = false;

	// Update fire
	for (auto& pos : world_ids)
		if (world[pos.x][pos.y]->fire_level > 0 && rand_probability(0.5f))
			world[pos.x][pos.y]->update_fire(pos.x, pos.y);

	for (auto& line : world)
		for (auto& cell : line)
			cell->done = false;

	step++;
}

void Simulator::draw()
{
	for (int x = 0; x < world_size.x; x++)
		for (int y = 0; y < world_size.y; y++)
		{
			sf::Color color = world[x][y]->get_color();
			sf::Color fire_color = world[x][y]->get_fire_color();
			float opacity = (float)fire_color.a / 255.f;

			image->setPixel(x, y, sf::Color(
				(1 - opacity) * color.r + opacity * fire_color.r,
				(1 - opacity) * color.g + opacity * fire_color.g,
				(1 - opacity) * color.b + opacity * fire_color.b
			));
		}

	texture->loadFromImage(*image);
	sprite->setTexture(*texture, true);
	sprite->setScale((dim::Vector2(dim::Scene::get("Simulation").get_size()) / dim::Vector2(world_size)).to_sf_float());
	dim::Scene::get("Simulation").draw(*sprite);
}
