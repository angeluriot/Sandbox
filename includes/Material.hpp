#ifndef MATERIAL_HPP
#define MATERIAL_HPP
#include "libraries.hpp"
#include "utils.hpp"

/**
 * @brief An abstract class representing a material.
 */
class Material
{
public:

	/**
	 * @brief An enum representing the different types of materials.
	 */
	enum class Nature
	{
		Air,
		Stone,
		Sand,
		Water,
		Salt,
		Wood,
		Coal,
		Ash,
		Oil,
		Gas,
		Lava,
		Vapor,
		Ice,
		Snow,
		Acid
	};

	/**
	 * @brief An enum representing the different states of materials.
	 */
	enum class State
	{
		Empty,
		Gas,
		Liquid,
		Dust,
		Solid
	};

	Nature	nature;						// The type of the material.
	State	state;						// The state of the material.
	int		weight;						// The weight of the material.
	int		fire_level;					// The fire level of the material.
	bool	can_burn;					// Whether the material can burn.
	int		way;						// The preferred direction of the material.
	int		color_type;					// The color type of the material.
	bool	salty;						// Whether the material is salty.
	bool	done;						// True when the material was updated.

	static constexpr int fire_max = 10;	// The maximum fire level.

	Material() = default;
	Material(const Material& material) = default;

	Material& operator=(const Material& material) = default;

	/**
	 * @brief Build a new material with the same nature.
	 *
	 * @return a pointer to the new material
	 */
	virtual Material* build() = 0;

	/**
	 * @brief Return true if a material with the given nature is near.
	 *
	 * @param x the x position
	 * @param y the y position
	 * @param nature the nature to check
	 * @return true if a material with the given nature is near
	 */
	static bool is_near(int x, int y, Nature nature);

	/**
	 * @brief Return true if no material with the given nature is near.
	 *
	 * @param x the x position
	 * @param y the y position
	 * @param nature the nature to check
	 * @return true if no material with the given nature is near
	 */
	static bool is_not_near(int x, int y, Nature nature);

	/**
	 * @brief Return true if a material with the given nature is around.
	 *
	 * @param x the x position
	 * @param y the y position
	 * @param nature the nature to check
	 * @return true if a material with the given nature is around
	 */
	static bool is_around(int x, int y, Nature nature);

	/**
	 * @brief Return true if no material with the given nature is around.
	 *
	 * @param x the x position
	 * @param y the y position
	 * @param nature the nature to check
	 * @return true if no material with the given nature is around
	 */
	static bool is_not_around(int x, int y, Nature nature);

	/**
	 * @brief Return true if a material with the given state is near.
	 *
	 * @param x the x position
	 * @param y the y position
	 * @param state the state to check
	 * @return true if a material with the given state is near
	 */
	static bool is_near(int x, int y, State state);

	/**
	 * @brief Return true if no material with the given state is near.
	 *
	 * @param x the x position
	 * @param y the y position
	 * @param state the state to check
	 * @return true if no material with the given state is near
	 */
	static bool is_not_near(int x, int y, State state);

	/**
	 * @brief Return true if a material with the given state is around.
	 *
	 * @param x the x position
	 * @param y the y position
	 * @param state the state to check
	 * @return true if a material with the given state is around
	 */
	static bool is_around(int x, int y, State state);

	/**
	 * @brief Return true if no material with the given state is around.
	 *
	 * @param x the x position
	 * @param y the y position
	 * @param state the state to check
	 * @return true if no material with the given state is around
	 */
	static bool is_not_around(int x, int y, State state);

	/**
	 * @brief Return true if the material is on the border.
	 *
	 * @param x the x position
	 * @param y the y position
	 * @return true if the material is on the border
	 */
	static bool is_border(int x, int y);

	/**
	 * @brief Return true if the material is a fluid.
	 *
	 * @return true if the material is a fluid
	 */
	bool is_fluid() const;

	/**
	 * @brief Set the material done.
	 */
	void set_done();

	/**
	 * @brief Tell if the material can move to the given position.
	 *
	 * @param x the x position
	 * @param y the y position
	 * @param target_x the target x position
	 * @param target_y the target y position
	 * @return true if the material can move to the given position
	 */
	bool can_move_to(int x, int y, int target_x, int target_y) const;

	/**
	 * @brief Move the material to the given position.
	 *
	 * @param x the x position
	 * @param y the y position
	 * @param target_x the target x position
	 * @param target_y the target y position
	 */
	void move_to(int x, int y, int target_x, int target_y);

	/**
	 * @brief Update the dust behavior of the material.
	 *
	 * @param x the x position
	 * @param y the y position
	 */
	void update_dust(int x, int y);

	/**
	 * @brief Update the liquid behavior of the material.
	 *
	 * @param x the x position
	 * @param y the y position
	 */
	void update_liquid(int x, int y);

	/**
	 * @brief Update the gas behavior of the material.
	 *
	 * @param x the x position
	 * @param y the y position
	 */
	void update_gas(int x, int y);

	/**
	 * @brief Update the material.
	 *
	 * @param x the x position
	 * @param y the y position
	 */
	virtual void update(int x, int y) = 0;

	/**
	 * @brief Move the fire to the given position.
	 *
	 * @param x the x position
	 * @param y the y position
	 * @param target_x the target x position
	 * @param target_y the target y position
	 */
	void fire_move_to(int x, int y, int target_x, int target_y);

	/**
	 * @brief Spread the fire to the given position.
	 *
	 * @param x the x position
	 * @param y the y position
	 * @param target_x the target x position
	 * @param target_y the target y position
	 */
	void fire_spread_to(int x, int y, int target_x, int target_y);

	/**
	 * @brief Tell if there is fire around
	 *
	 * @param x the x position
	 * @param y the y position
	 * @return true if there is fire around
	 */
	bool is_fire_around(int x, int y) const;

	/**
	 * @brief Update the burning behavior of the material.
	 *
	 * @param x the x position
	 * @param y the y position
	 * @param time the time to burn
	 * @param ash_probability the probability to create ash
	 */
	void update_burn(int x, int y, float time, float ash_probability);

	/**
	 * @brief Update fire propagation.
	 *
	 * @param x the x position
	 * @param y the y position
	 * @param speed the speed of the propagation
	 */
	void update_fire_propagation(int x, int y, float speed);

	/**
	 * @brief Update the fire movements.
	 *
	 * @param x the x position
	 * @param y the y position
	 */
	void update_fire_movement(int x, int y);

	/**
	 * @brief Update the fire behavior of the material.
	 *
	 * @param x the x position
	 * @param y the y position
	 */
	virtual void update_fire(int x, int y) = 0;

	/**
	 * @brief Give the color of the material.
	 *
	 * @return the color of the material
	 */
	virtual sf::Color get_color() const = 0;

	/**
	 * @brief Give the color of the fire.
	 *
	 * @return the color of the fire
	 */
	sf::Color get_fire_color() const;
};

#endif
