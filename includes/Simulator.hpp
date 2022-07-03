#ifndef SIMULATION_H
#define SIMULATION_H
#include "menu.h"
#include "material.h"
#include "utils.h"
#include "materials/air.h"
#include "materials/wood.h"
#include "materials/sand.h"
#include "materials/water.h"
#include "materials/oil.h"
#include "materials/salt.h"
#include "materials/ash.h"
#include "materials/coal.h"
#include "materials/stone.h"
#include "materials/lava.h"
#include "materials/vapor.h"
#include "materials/ice.h"
#include "materials/snow.h"
#include "materials/acid.h"



// Classe définissant la simulation

class Simulation
{

public:

	int									world_width;	// Largeur du monde
	int									world_height;	// Hauteur du monde
	int									pixels_size;	// Taille des pixels
	sf::RectangleShape					material;		// Un pixel à afficher
	std::vector<std::vector<Material*>>	world;			// Le monde
	Material*							brush;			// Le brush pour ajouter des matériaux
	sf::RenderTexture					texture;		// La texture sur laquelle sont dessinés les pixels
	sf::Sprite							sprite;			// Le sprite servant à afficher la texture
	std::array<Position, 8>				ways_8;			// Liste des 8 directions
	std::array<Position, 4>				ways_4;			// Liste des 4 directions

	Simulation();

	void restart(const Menu& menu);
	bool in_world(int x, int y);
	void imputs(const sf::Vector2i& mouse_position);
	void update(bool mouse_pressed, const sf::Vector2i& mouse_position);
	void draw_all();
	void draw(sf::RenderWindow& window);
};

extern Simulation simulation;

#endif