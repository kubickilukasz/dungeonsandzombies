#pragma once
#include "Character.h"
#include "AttackDirectionObject.h"
#include "Camera.h"

#ifndef  PLAYER
#define PLAYER

class AttackDirectionObject;

class Player :public Character {

protected:

	bool is_attack = false;
	bool is_hitting = false;
	bool lock_attack = false;
	VectorFloat current_direction_attack;
	AttackDirectionObject * attack_direction;
	GUIElement * health_bar;
	GUIElement * health_bar_back;

	float hit_time = 4;
	float hit_timer = 0;


	void onHit(Character * hitter);

	void onDeath();

	void(Level::*createMenuDeath_ptr)();

public:

	Player(const std::string _name, const std::string texture_name, VectorFloat _position, VectorFloat _size, const float _rotation, VectorFloat _scale, VectorInt offset, VectorInt texture_size, const int _sorting_order, const float _speed);

	void start();

	void setCreateMenuDeath(void(Level::*_createMenuDeath)());

	void createMenuDeath();

	void update();

	void updateHealthBar();

	void onCollision(std::vector<CollisionObject*> others);

	bool isAttack();

	bool isHitting();

	VectorFloat getCurrentDirectionAttack();

};


#endif // ! PLAYER	

