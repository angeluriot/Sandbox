#include "button.h"
#include <iostream>



// Construit un bouton

Button::Button()
{
	grabbed = false;
	grab_forbiden = false;
	animation = 0;
	material = NULL;
}



// Construit un bouton à partir d'un autre bouton

Button::Button(const Button& button)
{
	*this = button;
}



// Construit un bouton à partir de son matériau associé

Button::Button(Material* material)
{
	grabbed = false;
	grab_forbiden = false;
	animation = 0;
	this->material = material;

	sprite.setSize(sf::Vector2f(SIZE_BUTTON, SIZE_BUTTON));
	sprite.setOrigin(SIZE_BUTTON / 2., SIZE_BUTTON / 2.);
}



// Assignation

void Button::operator=(const Button& button)
{
	texture = button.texture;
	sprite = button.sprite;
	grabbed = button.grabbed;
	grab_forbiden = button.grab_forbiden;
	animation = button.animation;
	material = button.material;
}



// Initialise la texture du bouton

void Button::init(const sf::Texture& texture)
{
	this->texture = texture;
	sprite.setTexture(&(this->texture));
}



// Détecte si la souris est sur le bouton

bool Button::is_in(sf::Vector2f position)
{
	if (position.x > sprite.getPosition().x - sprite.getSize().x / 2. and position.x < sprite.getPosition().x + sprite.getSize().x / 2. and
		position.y > sprite.getPosition().y - sprite.getSize().y / 2. and position.y < sprite.getPosition().y + sprite.getSize().y / 2.)
		return true;

	return false;
}



// Met à jour le bouton

bool Button::update(const sf::Vector2i& mouse_position, bool left_click, Cursor_type& cursor_type)
{
	if (!left_click)
	{
		if (is_in(sf::Vector2f(mouse_position)) and grabbed)
		{
			grab_forbiden = false;
			grabbed = false;
			return true;
		}

		grab_forbiden = false;
		grabbed = false;
	}

	if (!is_in(sf::Vector2f(mouse_position)))
	{
		if (animation > 0)
		{
			sprite.setSize(sf::Vector2f(sprite.getSize().x - 1 * RESIZE, sprite.getSize().y - 1 * RESIZE));
			sprite.setOrigin(sprite.getSize().x / 2., sprite.getSize().y / 2.);
			animation--;
		}

		if (left_click and !grabbed)
			grab_forbiden = true;
	}

	if (is_in(sf::Vector2f(mouse_position)) and !grab_forbiden)
	{
		if (animation < 5)
		{
			sprite.setSize(sf::Vector2f(sprite.getSize().x + 1 * RESIZE, sprite.getSize().y + 1 * RESIZE));
			sprite.setOrigin(sprite.getSize().x / 2., sprite.getSize().y / 2.);
			animation++;
		}

		cursor_type = hand;

		if (left_click)
			grabbed = true;
	}

	return false;
}



// Affiche le bouton

void Button::draw(sf::RenderWindow& window, int position, int first_position)
{
	sprite.setPosition(DISTANCE_BUTTON_X + SIZE_BUTTON / 2, first_position + position * (SIZE_BUTTON + DISTANCE_BUTTON_Y));
	window.draw(sprite);
}



// Crée une liste de boutons

Button_list::Button_list()
{
	list.clear();
	first_position = 0;
}



// Initialise les boutons de la liste

void Button_list::init()
{
	list.clear();
	first_position = FIRST_POSITION;
	Material* material = NULL;

	sf::Texture temp;
	temp.setSmooth(true);
	list.push_back(Button(Air().init()));
	list.push_back(Button(Wood().init()));
	list.push_back(Button(Sand().init()));
	list.push_back(Button(Water().init()));
	list.push_back(Button(Oil().init()));
	list.push_back(Button(Salt().init()));

	delete material;
	material = Air().init();
	material->fire_level = FIRE_MAX;
	list.push_back(material);

	list.push_back(Button(Coal().init()));
	list.push_back(Button(Stone().init()));
	list.push_back(Button(Lava().init()));
	list.push_back(Button(Ice().init()));
	list.push_back(Button(Snow().init()));
	list.push_back(Button(Acid().init()));

	temp.loadFromFile("dependencies/resources/materials/air.png");
	list[0].init(temp);
	temp.loadFromFile("dependencies/resources/materials/wood.png");
	list[1].init(temp);
	temp.loadFromFile("dependencies/resources/materials/sand.png");
	list[2].init(temp);
	temp.loadFromFile("dependencies/resources/materials/water.png");
	list[3].init(temp);
	temp.loadFromFile("dependencies/resources/materials/oil.png");
	list[4].init(temp);
	temp.loadFromFile("dependencies/resources/materials/salt.png");
	list[5].init(temp);
	temp.loadFromFile("dependencies/resources/materials/fire.png");
	list[6].init(temp);
	temp.loadFromFile("dependencies/resources/materials/coal.png");
	list[7].init(temp);
	temp.loadFromFile("dependencies/resources/materials/stone.png");
	list[8].init(temp);
	temp.loadFromFile("dependencies/resources/materials/lava.png");
	list[9].init(temp);
	temp.loadFromFile("dependencies/resources/materials/ice.png");
	list[10].init(temp);
	temp.loadFromFile("dependencies/resources/materials/snow.png");
	list[11].init(temp);
	temp.loadFromFile("dependencies/resources/materials/acid.png");
	list[12].init(temp);
}



// Met à jour les boutons de la liste

void Button_list::update(const sf::Vector2i& mouse_position, bool left_click, sf::Cursor& cursor, Cursor_type& cursor_type, sf::RenderWindow& window, int whell_move, Material*& brush)
{
	if ((whell_move > 0 and first_position <= FIRST_POSITION - (WHEEL_SPEED * whell_move)) or
		(whell_move < 0 and first_position + (list.size() - 1) * (SIZE_BUTTON + DISTANCE_BUTTON_Y) >= (((1080. * RESIZE) - DISTANCE_BUTTON_Y * 2.) - SIZE_BUTTON / 2.) + (WHEEL_SPEED * (- whell_move))))
		first_position += whell_move * WHEEL_SPEED;

	for (int i = 0; i < list.size(); i++)
	{
		if (list[i].update(mouse_position, left_click, cursor_type))
		{
			delete brush;
			brush = list[i].material->init();

			if (list[i].material->fire_level > 0)
				brush->fire_level = FIRE_MAX;
		}
	}
}



// Affiche la liste de boutons

void Button_list::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < list.size(); i++)
		list[i].draw(window, i, first_position);
}
