#ifndef ASH_HPP
#define ASH_HPP
#include "Material.hpp"

class Ash : public Material
{
public:

	Ash();
	Ash(const Ash& other) = default;

	Ash& operator=(const Ash& other) = default;

	Material* build() override;
	sf::Color get_color() const override;
	void update(int x, int y) override;
	void update_fire(int x, int y) override;
};

#endif
