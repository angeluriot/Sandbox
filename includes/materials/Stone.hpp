#ifndef STONE_HPP
#define STONE_HPP
#include "Material.hpp"

/**
 * @brief A class representing the stone.
 */
class Stone : public Material
{
public:

	Stone();
	Stone(const Stone& other) = default;

	Stone& operator=(const Stone& other) = default;

	Material* build() override;
	sf::Color get_color() const override;
	void update(int x, int y) override;
	void update_fire(int x, int y) override;
};

#endif
