#ifndef WATER_HPP
#define WATER_HPP
#include "Material.hpp"

/**
 * @brief A class representing the water that can evaporate.
 */
class Water : public Material
{
public:

	Water();
	Water(const Water& other) = default;

	Water& operator=(const Water& other) = default;

	Material* build() override;
	sf::Color get_color() const override;
	void update(int x, int y) override;
	void update_fire(int x, int y) override;
};

#endif
