#ifndef ACID_HPP
#define ACID_HPP
#include "Material.hpp"

/**
 * @brief A class representing an acid fluid that dissolves other materials.
 */
class Acid : public Material
{
public:

	Acid();
	Acid(const Acid& other) = default;

	Acid& operator=(const Acid& other) = default;

	Material* build() override;
	sf::Color get_color() const override;
	void update(int x, int y) override;
	void update_fire(int x, int y) override;
};

#endif
