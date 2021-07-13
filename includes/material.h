#ifndef PARTICLE_H
#define PARTICLE_H
#include "utils.h"

class Simulation;



// Enumération des états possibles des matériaux

enum State { empty, gas, liquid, dust, solid };



// Enumération des matériaux

enum Nature { air, wood, sand, water, oil, salt, ash, coal, stone, lava, vapor, ice, snow, acid };



// Classe définissant un matériaux

class Material
{

public:

	State		state;			// Etat
	int			weight;			// Densité
	int			fire_level;		// Niveau de feu
	int			way;			// Sens de déplacement privilégié
	bool		color_swtich;	// Couleur plus foncée ou pas
	bool		done;			// Dit si la case a été faite

	bool		salty = false;	// Dit si l'eau est salée

	Material();
	Material(const Material& material);

	void				operator=(const Material& material);

	bool				is_around(int x, int y, Nature nature);
	bool				is_solid_around(int x, int y);
	bool				is_not_around(int x, int y, Nature nature);
	bool				is_near(int x, int y, Nature nature);
	bool				is_not_near(int x, int y, Nature nature);
	bool				is_fluid();
	void				set_done();

	bool				can_move_to(int x, int y, int target_x, int target_y);
	void				move_to(int x, int y, int target_x, int target_y);

	void				update_dust(int x, int y);
	void				update_liquid(int x, int y);
	void				update_gas(int x, int y);
	virtual void		update(int x, int y) = 0;

	void				fire_move_to(int x, int y, int target_x, int target_y);
	void				fire_spread_to(int x, int y, int target_x, int target_y);
	bool				is_fire_around(int x, int y);
	bool				turn_off_fire(int x, int y);

	void				update_burn(int x, int y, const double& time, const double& ash_probability);
	void				update_explosion(int x, int y, const double& time);
	void				update_fire_propagation(int x, int y, const double& speed);
	void				update_fire_movement(int x, int y);
	virtual void		update_fire(int x, int y) = 0;

	void				disappeared(int x, int y);
	void				burned(int x, int y);
	void				evaporate(int x, int y);
	void				liquefy(int x, int y);
	void				harden(int x, int y);

	void				draw_material(int x, int y);
	void				draw_fire(Simulation& simulation);

	virtual Material*	init() = 0;			// Donne un pointeur sur un nouveau matériaux
	virtual Nature		get_nature() = 0;	// Donne la nature du matériaux
	virtual bool		can_burn() = 0;		// Dit si le matériaux peut brûler
	virtual sf::Color	get_color() = 0;	// Donne la couleur du matériaux
};

#endif