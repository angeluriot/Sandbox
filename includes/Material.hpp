#ifndef MATERIAL_HPP
#define MATERIAL_HPP
#include "libraries.hpp"
#include "utils.hpp"

class Material
{
public:

	enum class State
	{
		Empty,
		Gas,
		Liquid,
		Dust,
		Solid
	};

	enum class Nature
	{
		Air,
		Wood,
		Sand,
		Water,
		Oil,
		Salt,
		Ash,
		Coal,
		Stone,
		Lava,
		Vapor,
		Ice,
		Snow,
		Acid
	};

	Nature	nature;
	State	state;
	int		weight;
	int		fire_level;
	bool	can_burn;
	int		way;
	bool	color_swtich;
	bool	salty;
	bool	done;

	static constexpr int fire_max = 10;
	static const std::vector<Material*> materials;

	Material() = default;
	Material(const Material& material) = default;

	Material& operator=(const Material& material) = default;

	virtual Material* build() = 0;
	static bool is_near(int x, int y, Nature nature);
	static bool is_not_near(int x, int y, Nature nature);
	static bool is_around(int x, int y, Nature nature);
	static bool is_not_around(int x, int y, Nature nature);
	static bool is_near(int x, int y, State state);
	static bool is_not_near(int x, int y, State state);
	static bool is_around(int x, int y, State state);
	static bool is_not_around(int x, int y, State state);
	static bool is_border(int x, int y);
	bool is_fluid() const;
	void set_done();
	bool can_move_to(int x, int y, int target_x, int target_y) const;
	void move_to(int x, int y, int target_x, int target_y);
	void update_dust(int x, int y);
	void update_liquid(int x, int y);
	void update_gas(int x, int y);
	virtual void update(int x, int y) = 0;
	void fire_move_to(int x, int y, int target_x, int target_y);
	void fire_spread_to(int x, int y, int target_x, int target_y);
	bool is_fire_around(int x, int y) const;
	bool turn_off_fire(int x, int y);
	void update_burn(int x, int y, float time, float ash_probability);
	void update_fire_propagation(int x, int y, float speed);
	void update_fire_movement(int x, int y);
	virtual void update_fire(int x, int y) = 0;
	virtual sf::Color get_color() const = 0;
	sf::Color get_fire_color() const;
};

#endif
