#ifndef BUTTON_H
#define BUTTON_H
#include <SFML/Graphics.hpp>
#include "simulation.h"

#define FIRST_POSITION		(70. * RESIZE)	// Position du premier bouton
#define SIZE_BUTTON			(100. * RESIZE) // Taille des boutons
#define DISTANCE_BUTTON_X	(20. * RESIZE)	// Distance entre les boutons et les bords
#define DISTANCE_BUTTON_Y	(23. * RESIZE)	// Distance entre les boutons
#define WHEEL_SPEED			(30. * RESIZE)	// Vitesse de la molette



// Classe définissant un boutton

class Button
{
public:

	sf::Texture			texture;		// Texture du bouton
	sf::RectangleShape	sprite;			// Sprite affichant la texture
	bool				grabbed;		// Dit si on appuie sur le bouton
	bool				grab_forbiden;	// Dit si on peut cliquer sur le bouton
	int					animation;		// Nombre de frames de l'animation du bouton
	Material*			material;		// Type de matérieaux associé au bouton

	Button();
	Button(const Button& button);
	Button(Material* material);

	void operator=(const Button& button);

	void init(const sf::Texture& texture);
	bool is_in(sf::Vector2f position);
	bool update(const sf::Vector2i& mouse_position, bool left_click, Cursor_type& cursor_type);
	void draw(sf::RenderWindow& window, int position, int first_position);
};



// Classe définissant une liste de bouttons

class Button_list
{
public:

	std::vector<Button>	list;			// Liste des boutons
	int					first_position;	// Position du premier bouton
	
	Button_list();
	
	void init();
	void update(const sf::Vector2i& mouse_position, bool left_click, sf::Cursor& cursor, Cursor_type& cursor_type, sf::RenderWindow& window, int whell_move, Material*& brush);
	void draw(sf::RenderWindow& window);
};

#endif