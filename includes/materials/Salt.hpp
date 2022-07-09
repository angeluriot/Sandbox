#ifndef SALT_HPP
#define SALT_HPP
#include "Material.hpp"

/**
 * @brief A class representing the salt that can dissolve in water.
 */
class Salt : public Material
{
public:

	Salt();
	Salt(const Salt& other) = default;

	Salt& operator=(const Salt& other) = default;

	Material* build() override;
	sf::Color get_color() const override;
	void update(int x, int y) override;
	void update_fire(int x, int y) override;
};

#endif
