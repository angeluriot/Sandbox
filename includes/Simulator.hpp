#ifndef SIMULATION_HPP
#define SIMULATION_HPP
#include "Material.hpp"
#include "utils.hpp"

/**
 * @brief A static class representing the simulation.
 */
class Simulator
{
public:

	static dim::Vector2int						world_size;	// The size of the world.
	static std::vector<std::vector<Material*>>	world;		// The world grid of the simulation.
	static std::vector<dim::Vector2int>			world_ids;	// Randomly distributed ids of the world grid.
	static Material*							brush_type;	// The type of the brush.
	static int									brush_size;	// The size of the brush.
	static const std::array<dim::Vector2int, 4>	ways_4;		// The 4 ways around a position.
	static const std::array<dim::Vector2int, 8>	ways_8;		// The 8 ways around a position.
	static sf::Image*							image;		// The image of the texture.
	static sf::Texture*							texture;	// The texture of the sprtie.
	static sf::Sprite*							sprite;		// The sprite to show on screen.

	/**
	 * @brief Initialize the simulation.
	 */
	static void init();

	/**
	 * @brief Reset the simulation.
	 */
	static void reset();

	/**
	 * @brief Give the screen position from a world position.
	 *
	 * @param position the world position
	 * @return the screen position
	 */
	static dim::Vector2int screen_to_world(dim::Vector2int position);

	/**
	 * @brief Give the world position from a screen position.
	 *
	 * @param position the screen position
	 * @return the world position
	 */
	static dim::Vector2int world_to_screen(dim::Vector2int position);

	/**
	 * @brief Tell if a position is in the world grid.
	 *
	 * @param position the position
	 * @return true if the position is in the world grid, false otherwise
	 */
	static bool in_world(dim::Vector2int position);

	/**
	 * @brief Tell if a position is in the world grid.
	 *
	 * @param x the x position
	 * @param y the y position
	 * @return true if the position is in the world grid, false otherwise
	 */
	static bool in_world(int x, int y);

	/**
	 * @brief Handle user input.
	 */
	static void inputs();

	/**
	 * @brief Update the simulation.
	 */
	static void update();

	/**
	 * @brief Draw the simulation on the screen.
	 */
	static void draw();
};

#endif
