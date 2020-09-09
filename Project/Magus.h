#pragma once
#include "Enemy.h"
#include "Bullet.h"

#ifndef MAGUS
#define MAGUS

class Magus :public Enemy {

	float range_attack = 300;
	float range_view = 450;

public:

	Magus(const std::string _name, const std::string texture_name, VectorFloat _position, VectorFloat _size, VectorFloat _scale, VectorInt offset, VectorInt texture_size, const int _sorting_order, const float _speed, const int _max_health, const int _damage, Player * player);

	void start();

	void updateEnemy();

};


#endif // !MAGUS



