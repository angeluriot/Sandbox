#ifndef GAS_HPP
#define GAS_HPP
#include "Material.hpp"

/**
 * @brief A class representing a flammable gas.
 */
class Gas : public Material
{
public:

	Gas();
	Gas(const Gas& other) = default;

	Gas& operator=(const Gas& other) = default;

	Material* build() override;
	sf::Color get_color() const override;
	void update(int x, int y) override;
	void update_fire(int x, int y) override;
};

#endif
