#pragma once
#include <random>

#include "Enemy.h"

#ifndef ZOMBIE
#define ZOMBIE

class Zombie :public Enemy{

	float range_attack = 80;
	float range_view = 400;

	float time_to_change_direction = 5;
	float timer_to_change_direction = 0;

public:

	Zombie(const std::string _name, const std::string texture_name, VectorFloat _position, VectorFloat _size, VectorFloat _scale, VectorInt offset, VectorInt texture_size, const int _sorting_order, const float _speed, const int _max_health, const int _damage, Player * player);

	void start();

	void updateEnemy();

};

#endif
