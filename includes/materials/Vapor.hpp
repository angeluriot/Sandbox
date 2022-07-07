#ifndef VAPOR_HPP
#define VAPOR_HPP
#include "Material.hpp"

class Vapor : public Material
{
public:

	Vapor();
	Vapor(const Vapor& other) = default;

	Vapor& operator=(const Vapor& other) = default;

	Material* build() override;
	sf::Color get_color() const override;
	void update(int x, int y) override;
	void update_fire(int x, int y) override;
};

#endif
