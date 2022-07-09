#ifndef SNOW_HPP
#define SNOW_HPP
#include "Material.hpp"

/**
 * @brief A class representing the snow.
 */
class Snow : public Material
{
public:

	Snow();
	Snow(const Snow& other) = default;

	Snow& operator=(const Snow& other) = default;

	Material* build() override;
	sf::Color get_color() const override;
	void update(int x, int y) override;
	void update_fire(int x, int y) override;
};

#endif
