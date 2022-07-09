#ifndef ICE_HPP
#define ICE_HPP
#include "Material.hpp"

/**
 * @brief A class representing ice.
 */
class Ice : public Material
{
public:

	Ice();
	Ice(const Ice& other) = default;

	Ice& operator=(const Ice& other) = default;

	Material* build() override;
	sf::Color get_color() const override;
	void update(int x, int y) override;
	void update_fire(int x, int y) override;
};

#endif
