#ifndef SIMULATION_HPP
#define SIMULATION_HPP
#include "Material.hpp"
#include "utils.hpp"

class Simulator
{
public:

	static dim::Vector2int						world_size;
	static std::vector<std::vector<Material*>>	world;
	static std::vector<dim::Vector2int>			world_ids;
	static Material*							brush_type;
	static int									brush_size;
	static const std::array<dim::Vector2int, 4>	ways_4;
	static const std::array<dim::Vector2int, 8>	ways_8;
	static sf::Image*							image;
	static sf::Texture*							texture;
	static sf::Sprite*							sprite;

	static void init();
	static void reset();
	static dim::Vector2int screen_to_world(dim::Vector2int position);
	static dim::Vector2int world_to_screen(dim::Vector2int position);
	static bool in_world(dim::Vector2int position);
	static bool in_world(int x, int y);
	static void inputs();
	static void update();
	static void draw();
};

#endif
