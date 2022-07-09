#ifndef OIL_HPP
#define OIL_HPP
#include "Material.hpp"

/**
 * @brief A class representing flammable oil.
 */
class Oil : public Material
{
public:

	Oil();
	Oil(const Oil& other) = default;

	Oil& operator=(const Oil& other) = default;

	Material* build() override;
	sf::Color get_color() const override;
	void update(int x, int y) override;
	void update_fire(int x, int y) override;
};

#endif
