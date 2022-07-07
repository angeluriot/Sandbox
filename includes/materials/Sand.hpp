#ifndef SAND_HPP
#define SAND_HPP
#include "Material.hpp"

class Sand : public Material
{
public:

	Sand();
	Sand(const Sand& other) = default;

	Sand& operator=(const Sand& other) = default;

	Material* build() override;
	sf::Color get_color() const override;
	void update(int x, int y) override;
	void update_fire(int x, int y) override;
};

#endif
