#ifndef AIR_HPP
#define AIR_HPP
#include "Material.hpp"

class Air : public Material
{
public:

	Air();
	Air(const Air& other) = default;

	Air& operator=(const Air& other) = default;

	Material* build() override;
	sf::Color get_color() const override;
	void update(int x, int y) override;
	void update_fire(int x, int y) override;
};

#endif
