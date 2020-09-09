#pragma once
#include "CollisionObject.h"
#include "Player.h"

#ifndef BULLET
#define BULLET

class Bullet :public CollisionObject{

	int damage;

	bool to_delete = false;

	float timer = 0;
	float time_to_die = 40;

public:

	Bullet(const std::string _name, const std::string texture_name, VectorFloat _position, VectorFloat _size, const float _rotation, VectorFloat _scale, VectorInt offset, VectorInt texture_size
		, const int _sorting_order, const float _speed, int _damage);

	void update();

	void onTrigger(CollisionObject* other);

};

#endif

