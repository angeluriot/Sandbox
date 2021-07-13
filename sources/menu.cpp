#include "menu.h"



// -------------------- Ligne --------------------



// Construit une ligne

Line::Line()
{
}



// Construit une ligne à partir d'une autre ligne

Line::Line(const Line& line)
{
	this->rectangle = line.rectangle;
	left = line.left;
	right = line.right;
}



// Construit une ligne à partir de ces propriétés

Line::Line(const double& size, const double& width, const double& x_position, const double& y_position, const sf::Color& color)
{
	rectangle.setSize(sf::Vector2f(size, width));
	left.setRadius(width / 2.);
	right.setRadius(width / 2.);

	rectangle.setOrigin(size / 2., width / 2.);
	left.setOrigin(width / 2., width / 2.);
	right.setOrigin(width / 2., width / 2.);
	left.setPosition(0., 0.);
	right.setPosition(0., 0.);
	left.setOrigin(size / 2. + width / 2., width / 2.);
	right.setOrigin(-size / 2. + width / 2., width / 2.);

	rectangle.setPosition(x_position, y_position);
	left.setPosition(x_position, y_position);
	right.setPosition(x_position, y_position);

	rectangle.setFillColor(color);
	left.setFillColor(color);
	right.setFillColor(color);
}



// Assignation

void Line::operator=(const Line& line)
{
	this->rectangle = line.rectangle;
	left = line.left;
	right = line.right;
}



// Modifie l'inclinaison de la ligne

void Line::set_rotation(const double& angle)
{
	rectangle.setRotation(angle);
	left.setRotation(angle);
	right.setRotation(angle);
}



// Affiche la ligne

void Line::draw(sf::RenderWindow& window)
{
	window.draw(rectangle);
	window.draw(left);
	window.draw(right);
}



// -------------------- Case --------------------



// Construit une case

Box::Box()
{
}



// Construit une case à partir d'une autre case

Box::Box(const Box& box)
{
	left = box.left;
	right = box.right;
	top = box.top;
	bottom = box.bottom;
	check_left = box.check_left;
	check_right = box.check_right;
	hitbox = box.hitbox;
}



// Construit une case à partir de ces propriétés

Box::Box(const double& size, const double& width, const double& x_position, const double& y_position, const sf::Color& color)
{
	top = Line(size, width, x_position, y_position + size / 2. - size / 10., color);
	bottom = Line(size, width, x_position, y_position - size / 2. - size / 10., color);
	left = Line(size, width, x_position - size / 2., y_position - size / 10., color);
	right = Line(size, width, x_position + size / 2., y_position - size / 10., color);

	left.set_rotation(90);
	right.set_rotation(90);

	check_left = Line(size / 2., width * 1.5, x_position - size / 4., y_position + size / 7. - size / 10., sf::Color(0, 200, 0));
	check_right = Line(size / 1.1, width * 1.5, x_position + size / 3.5, y_position - size / 10., sf::Color(0, 200, 0));

	check_left.set_rotation(45);
	check_right.set_rotation(-45);

	hitbox.setSize(sf::Vector2f(size + width, size + width));
	hitbox.setOrigin(size / 2. + width / 2., size / 2. + width / 2.);
	hitbox.setPosition(x_position, y_position - size / 10.);
}



// Assignation

void Box::operator=(const Box& box)
{
	left = box.left;
	right = box.right;
	top = box.top;
	bottom = box.bottom;
	check_left = box.check_left;
	check_right = box.check_right;
	hitbox = box.hitbox;
}



// Affiche la case

void Box::draw(sf::RenderWindow& window, bool checked)
{
	top.draw(window);
	bottom.draw(window);
	left.draw(window);
	right.draw(window);

	if (checked)
	{
		check_left.draw(window);
		check_right.draw(window);
	}
}



// -------------------- Variable --------------------



// Construit une variable

Variable::Variable()
{
	type = Int;
	bool_value = false;
	int_value = 0;
	int_min = 0;
	int_max = 0;
	double_value = 0.;
	double_min = 0.;
	double_max = 0.;
	precision = 0;
	percent = false;
	checked = false;
	line = Line();
	grabbed = false;
	grab_forbiden = false;
}



// Construit une variable à partir d'une autre variable

Variable::Variable(const Variable& variable)
{
	type = variable.type;
	bool_value = variable.bool_value;
	int_value = variable.int_value;
	int_min = variable.int_min;
	int_max = variable.int_max;
	double_value = variable.double_value;
	double_min = variable.double_min;
	double_max = variable.double_max;
	precision = variable.precision;
	percent = variable.percent;
	name = variable.name;
	value = variable.value;
	box = variable.box;
	checked = variable.checked;
	line = variable.line;
	circle = variable.circle;
	grabbed = variable.grabbed;
	grab_forbiden = variable.grab_forbiden;
}



// Construit une variable à partir de ces paramètres

Variable::Variable(const std::string& name, Variable_type type, const double& initial_value, double min, double max, int precision, bool percent)
{
	this->name.setString(name);
	this->precision = precision;
	this->percent = percent;
	this->type = type;

	if (type == Bool)
	{
		bool_value = initial_value;
		checked = bool_value;
	}

	if (type == Int)
	{
		int_value = initial_value;
		int_min = min;
		int_max = max;
	}

	if (type == Double)
	{
		double_value = initial_value;
		double_min = min;
		double_max = max;
	}

	checked = false;
	grabbed = false;
	grab_forbiden = false;

	if (this->type == Double)
		this->value.setString(double_to_string(double_value, this->precision, this->percent));

	if (this->type == Int)
		this->value.setString(std::to_string(int_value));
}



// Assignation

void Variable::operator=(const Variable& variable)
{
	type = variable.type;
	bool_value = variable.bool_value;
	int_value = variable.int_value;
	int_min = variable.int_min;
	int_max = variable.int_max;
	double_value = variable.double_value;
	double_min = variable.double_min;
	double_max = variable.double_max;
	precision = variable.precision;
	percent = variable.percent;
	name = variable.name;
	value = variable.value;
	box = variable.box;
	checked = variable.checked;
	line = variable.line;
	circle = variable.circle;
	grabbed = variable.grabbed;
	grab_forbiden = variable.grab_forbiden;
}



// Dit si la position se trouve dans la case ou le curseur de la variable

bool Variable::is_in(sf::Vector2f position)
{
	if (type == Bool)
	{
		if (position.x > box.hitbox.getPosition().x - box.hitbox.getSize().x / 2. and position.x < box.hitbox.getPosition().x + box.hitbox.getSize().x / 2. and
			position.y > box.hitbox.getPosition().y - box.hitbox.getSize().y / 2. and position.y < box.hitbox.getPosition().y + box.hitbox.getSize().y / 2.)
			return true;
	}

	else
	{
		if (position.x > circle.getPosition().x - circle.getRadius() and position.x < circle.getPosition().x + circle.getRadius() and
			position.y > circle.getPosition().y - circle.getRadius() and position.y < circle.getPosition().y + circle.getRadius())
			return true;
	}

	return false;
}



// Donne la position du curseur en fonction de la valeur de la variable

sf::Vector2f Variable::get_circle_position()
{
	if (type == Int)
		return sf::Vector2f(((double)((double)int_value - (double)int_min) / (double)((double)int_max - (double)int_min)) * line.rectangle.getSize().x
			+ line.rectangle.getPosition().x - line.rectangle.getSize().x / 2., line.rectangle.getPosition().y);

	if (type == Double)
		return sf::Vector2f(((double_value - double_min) / (double_max - double_min)) * line.rectangle.getSize().x
			+ line.rectangle.getPosition().x - line.rectangle.getSize().x / 2., line.rectangle.getPosition().y);
}



// Donne la valeur de la variable en fonction de la position du curseur

double Variable::get_value_from_circle()
{
	if (type == Int)
		return ((circle.getPosition().x - (line.rectangle.getPosition().x - line.rectangle.getSize().x / 2.)) / line.rectangle.getSize().x) * ((double)int_max - (double)int_min) + (double)int_min;

	if (type == Double)
		return ((circle.getPosition().x - (line.rectangle.getPosition().x - line.rectangle.getSize().x / 2.)) / line.rectangle.getSize().x) * (double_max - double_min) + double_min;
}



// Met à jour la variable

void Variable::update(const sf::Vector2i& previous_mouse_position, const sf::Vector2i& mouse_position, bool left_click)
{
	if (type == Bool)
	{
		if (!left_click)
		{
			grabbed = false;
			grab_forbiden = false;
		}

		if (!is_in(sf::Vector2f(mouse_position)) and left_click)
			grab_forbiden = true;

		if (is_in(sf::Vector2f(mouse_position)) and !grab_forbiden and !grabbed and left_click)
		{
			checked = !checked;
			grabbed = true;
			bool_value = checked;
		}
	}

	else
	{
		if (!left_click)
		{
			grab_forbiden = false;
			grabbed = false;
		}

		if (grabbed and !((mouse_position.x < line.rectangle.getPosition().x - line.rectangle.getSize().x / 2. and circle.getPosition().x <= line.rectangle.getPosition().x - line.rectangle.getSize().x / 2. + 0.1) or
			             (mouse_position.x > line.rectangle.getPosition().x + line.rectangle.getSize().x / 2. and circle.getPosition().x >= line.rectangle.getPosition().x + line.rectangle.getSize().x / 2. - 0.1)))
		{
			circle.move((double)mouse_position.x - (double)previous_mouse_position.x, 0.);

			if (circle.getPosition().x > line.rectangle.getPosition().x + line.rectangle.getSize().x / 2.)
				circle.setPosition(line.rectangle.getPosition().x + line.rectangle.getSize().x / 2., circle.getPosition().y);

			if (circle.getPosition().x < line.rectangle.getPosition().x - line.rectangle.getSize().x / 2.)
				circle.setPosition(line.rectangle.getPosition().x - line.rectangle.getSize().x / 2., circle.getPosition().y);
			
			if (type == Int)
			{
				int_value = get_value_from_circle();
				value.setString(std::to_string(int_value));
			}

			else
			{
				double_value = get_value_from_circle();
				value.setString(double_to_string(double_value, precision, percent));
			}

			value.setOrigin(value.getLocalBounds().width / 2., value.getLocalBounds().height);
			value.setPosition(circle.getPosition().x, value.getPosition().y);
		}

		if (!is_in(sf::Vector2f(mouse_position)) and left_click and !grabbed)
			grab_forbiden = true;

		if (is_in(sf::Vector2f(mouse_position)) and !grab_forbiden and left_click)
			grabbed = true;
	}
}



// Affiche la variable

void Variable::draw(sf::RenderWindow& window)
{
	window.draw(name);
	
	if (type == Bool)
		box.draw(window, checked);

	else
	{
		line.draw(window);
		window.draw(circle);
		window.draw(value);
	}
}



// -------------------- Menu --------------------



// Construit un menu

Menu::Menu()
{
	width = 0;
	height = 0;
	variables.clear();
	grabbed = false;
	grab_forbiden = false;
	end = false;
}



// Construit un menu à partir d'un autre menu

Menu::Menu(const Menu& menu)
{
	width = menu.width;
	height = menu.height;
	variables = menu.variables;
	background = menu.background;
	texts_font = menu.texts_font;
	start_texture = menu.start_texture;
	start_texture_grabbed = menu.start_texture_grabbed;
	start_button = menu.start_button;
	grabbed = menu.grabbed;
	grab_forbiden = menu.grab_forbiden;
	end = menu.end;
}



// Construit un menu à partir de ces paramètres

Menu::Menu(const std::vector<Variable>& variables, const sf::Color& background, int width, int height)
{
	this->width = width;
	this->height = height;

	this->variables = variables;
	this->background = background;

	texts_font.loadFromFile("dependencies/resources/GoogleSans-Bold.ttf");
}



// Initialise le nom des variables

void Menu::init_names(int name_size, const double& names_position, const sf::Color& name_color, const double& y_edges)
{
	for (int i = 0; i < variables.size(); i++)
	{
		variables[i].name.setCharacterSize(resize(name_size, width));
		variables[i].name.setFont(texts_font);
		variables[i].name.setFillColor(name_color);
		variables[i].name.setOrigin(variables[i].name.getLocalBounds().width, resize(name_size, width) / 1.35);
		variables[i].name.setPosition(resize(names_position, width), (((height - (2. * resize(y_edges, width))) / (variables.size() - 1)) * i) + resize(y_edges, width));
	}
}



// Initialise la ligne des curseurs

void Menu::init_lines(const double& lines_sizes, const double& lines_widths, const double& lines_positions, const sf::Color& line_color)
{
	for (int i = 0; i < variables.size(); i++)
	{
		if (variables[i].type != Bool)
			variables[i].line = Line(resize(lines_sizes, width), resize(lines_widths, width), resize(lines_positions, width), variables[i].name.getPosition().y, line_color);
	}
}



// Initialise les curseurs

void Menu::init_circles(const double& circles_radius, const sf::Color& circle_color)
{
	for (int i = 0; i < variables.size(); i++)
	{
		if (variables[i].type != Bool)
		{
			variables[i].circle = sf::CircleShape(resize(circles_radius, width), 50);
			variables[i].circle.setOrigin(resize(circles_radius, width), resize(circles_radius, width));
			variables[i].circle.setPosition(variables[i].get_circle_position());
			variables[i].circle.setFillColor(circle_color);
		}
	}
}



// Initialise les valeurs affichées

void Menu::init_values(int value_size, const double& values_position, const sf::Color& value_color)
{
	for (int i = 0; i < variables.size(); i++)
	{
		if (variables[i].type != Bool)
		{
			variables[i].value.setCharacterSize(resize(value_size, width));
			variables[i].value.setFont(texts_font);
			variables[i].value.setFillColor(value_color);
			variables[i].value.setOrigin(variables[i].value.getLocalBounds().width / 2., variables[i].value.getLocalBounds().height);
			variables[i].value.setPosition(variables[i].circle.getPosition().x, variables[i].circle.getPosition().y - resize(values_position, width));
		}
	}
}



// Initialise les cases à cocher

void Menu::init_boxes(const double& boxes_sizes, const double& boxes_position, const sf::Color& boxes_color)
{
	for (int i = 0; i < variables.size(); i++)
	{
		if (variables[i].type == Bool)
		{
			variables[i].box = Box(resize(boxes_sizes, width), resize(boxes_sizes, width) / 4., resize(boxes_position, width), variables[i].name.getPosition().y, boxes_color);
			variables[i].checked = variables[i].bool_value;
		}
	}
}



// Initialise le bouton start

void Menu::init_start(const double& start_size, const double& start_x_position, const double& start_y_position, const sf::Color& start_color)
{
	start_texture.loadFromFile("dependencies/resources/start_texture.png");
	start_texture_grabbed.loadFromFile("dependencies/resources/start_texture_grabbed.png");

	start_texture.setSmooth(true);
	start_texture_grabbed.setSmooth(true);

	start_button.setTexture(&start_texture);
	start_button.setSize(sf::Vector2f(resize(start_size, width), resize(start_size, width)));
	start_button.setOrigin(resize(start_size, width) / 2., resize(start_size, width) / 2.);
	start_button.setPosition(resize(start_x_position, width), resize(start_y_position, width));
	start_button.setFillColor(start_color);
}



// Assignation

void Menu::operator=(const Menu& menu)
{
	width = menu.width;
	height = menu.height;
	variables = menu.variables;
	background = menu.background;
	start_texture = menu.start_texture;
	start_button = menu.start_button;
	start_texture_grabbed = menu.start_texture_grabbed;
	texts_font = menu.texts_font;
	grabbed = menu.grabbed;
	grab_forbiden = menu.grab_forbiden;
	end = menu.end;
}



// Dit si laposition est sur le bouton start

bool Menu::is_in(sf::Vector2f position)
{
	if (position.x > start_button.getPosition().x - start_button.getSize().x / 2. and position.x < start_button.getPosition().x + start_button.getSize().x / 2. and
		position.y > start_button.getPosition().y - start_button.getSize().y / 2. and position.y < start_button.getPosition().y + start_button.getSize().x / 2.)
		return true;

	return false;
}



// Met à jour le menu

void Menu::update(const sf::Vector2i& previous_mouse_position, const sf::Vector2i& mouse_position, bool left_click, sf::Cursor& cursor, Cursor_type& cursor_type, sf::RenderWindow& window)
{
	Cursor_type temp = cursor_type;
	cursor_type = arrow;

	for (int i = 0; i < variables.size(); i++)
	{
		variables[i].update(previous_mouse_position, mouse_position, left_click);

		if (variables[i].type == Bool)
		{
			if (variables[i].is_in(sf::Vector2f(mouse_position)) and !variables[i].grab_forbiden)
				cursor_type = hand;
		}

		else
		{
			if ((variables[i].grabbed or variables[i].is_in(sf::Vector2f(mouse_position))) and !variables[i].grab_forbiden)
				cursor_type = resizing;
		}
	}

	if (!left_click)
	{
		if (is_in(sf::Vector2f(mouse_position)) and grabbed)
			end = true;

		else
		{
			grabbed = false;
			grab_forbiden = false;
		}
	}

	if (!is_in(sf::Vector2f(mouse_position)))
	{
		start_button.setTexture(&start_texture);

		if (left_click and !grabbed)
			grab_forbiden = true;
	}

	if (is_in(sf::Vector2f(mouse_position)) and !grab_forbiden)
	{
		start_button.setTexture(&start_texture_grabbed);
		cursor_type = hand;

		if (left_click)
			grabbed = true;
	}

	if (temp != cursor_type)
	{
		if (cursor_type == arrow)
			cursor.loadFromSystem(sf::Cursor::Arrow);

		if (cursor_type == hand)
			cursor.loadFromSystem(sf::Cursor::Hand);

		if (cursor_type == resizing)
			cursor.loadFromSystem(sf::Cursor::SizeHorizontal);

		window.setMouseCursor(cursor);
	}
}



// Affiche le menu

void Menu::draw(sf::RenderWindow& window)
{
	window.clear(background);

	for (int i = 0; i < variables.size(); i++)
		variables[i].draw(window);

	window.draw(start_button);

	window.display();
}



// -------------------- Bouton recommencer --------------------



// Construit un bouton recommencer

Restart::Restart()
{
	grabbed = false;
	grab_forbiden = false;
}



// Construit un bouton recommencer à partir d'un autre

Restart::Restart(const Restart& restart)
{
	button = restart.button;
	texture = restart.texture;
	texture_grabbed = restart.texture_grabbed;
	grabbed = restart.grabbed;
	grab_forbiden = restart.grab_forbiden;
}



// Construit un bouton recommencer à partir de ces paramètres

Restart::Restart(const double& start_size, const double& start_x_position, const double& start_y_position, const sf::Color& start_color, int width, int height)
{
	grabbed = false;
	grab_forbiden = false;

	texture.loadFromFile("dependencies/resources/restart_texture.png");
	texture_grabbed.loadFromFile("dependencies/resources/restart_texture_grabbed.png");

	texture.setSmooth(true);
	texture_grabbed.setSmooth(true);

	button.setTexture(&texture);
	button.setSize(sf::Vector2f(resize(start_size, width), resize(start_size, width)));
	button.setOrigin(resize(start_size, width) / 2., resize(start_size, width) / 2.);
	button.setPosition(resize(start_x_position, width), resize(start_y_position, width));
	button.setFillColor(start_color);
}



// Assignation

void Restart::operator=(const Restart& restart)
{
	button = restart.button;
	texture = restart.texture;
	texture_grabbed = restart.texture_grabbed;
	grabbed = restart.grabbed;
	grab_forbiden = restart.grab_forbiden;
}



// Dit si la position est sur le bouton

bool Restart::is_in(sf::Vector2f position)
{
	if (position.x > button.getPosition().x - button.getSize().x / 2. and position.x < button.getPosition().x + button.getSize().x / 2. and
		position.y > button.getPosition().y - button.getSize().y / 2. and position.y < button.getPosition().y + button.getSize().x / 2.)
		return true;

	return false;
}



// Met à jour le bouton recommencer

bool Restart::update(const sf::Vector2i& mouse_position, bool left_click, sf::Cursor& cursor, Cursor_type& cursor_type, sf::RenderWindow& window)
{
	if (!left_click)
	{
		if (is_in(sf::Vector2f(mouse_position)) and grabbed)
			return true;

		else
		{
			grabbed = false;
			grab_forbiden = false;
		}
	}

	if (!is_in(sf::Vector2f(mouse_position)))
	{
		button.setTexture(&texture);

		if (left_click and !grabbed)
			grab_forbiden = true;
	}

	if (is_in(sf::Vector2f(mouse_position)) and !grab_forbiden)
	{
		button.setTexture(&texture_grabbed);
		cursor_type = hand;

		if (left_click)
			grabbed = true;
	}

	return false;
}



// Affiche le bouton recommencer

void Restart::draw(sf::RenderWindow& window)
{
	window.draw(button);
}



// -------------------- Fonctions --------------------



// Transforme un nombre réel en text

std::string double_to_string(const double& value, int precision, bool percent)
{
	std::string text = std::to_string(value);
	int i = 0;

	while (text[i] != '.')
	{
		i++;

		if (i == text.size())
			return text;
	}

	text[i] = ',';

	i += precision + 1;

	while (text.size() != i)
		text.pop_back();

	if (precision == 0)
		text.pop_back();

	if (percent)
	{
		text.push_back(' ');
		text.push_back('%');
	}

	return text;
}



// Permet de gérer les différentes tailles d'écrans

double resize(double value, double width)
{
	return (value / 1920.) * width;
}