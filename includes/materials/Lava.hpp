#ifndef LAVA_HPP
#define LAVA_HPP
#include "Material.hpp"

/**
 * @brief A class representing the lava.
 */
class Lava : public Material
{
public:

	Lava();
	Lava(const Lava& other) = default;

	Lava& operator=(const Lava& other) = default;

	Material* build() override;
	sf::Color get_color() const override;
	void update(int x, int y) override;
	void update_fire(int x, int y) override;
};

#endif
