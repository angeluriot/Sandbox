#ifndef COAL_HPP
#define COAL_HPP
#include "Material.hpp"

/**
 * @brief A class representing the coal.
 */
class Coal : public Material
{
public:

	Coal();
	Coal(const Coal& other) = default;

	Coal& operator=(const Coal& other) = default;

	Material* build() override;
	sf::Color get_color() const override;
	void update(int x, int y) override;
	void update_fire(int x, int y) override;
};

#endif
