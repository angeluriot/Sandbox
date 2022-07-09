#ifndef WOOD_HPP
#define WOOD_HPP
#include "Material.hpp"

/**
 * @brief A class representing the wood.
 */
class Wood : public Material
{
public:

	Wood();
	Wood(const Wood& other) = default;

	Wood& operator=(const Wood& other) = default;

	Material* build() override;
	sf::Color get_color() const override;
	void update(int x, int y) override;
	void update_fire(int x, int y) override;
};

#endif
