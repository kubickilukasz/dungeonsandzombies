#pragma once
#include "CollisionObject.h"
#include "Camera.h"
#include "Player.h"
#include "Enemy.h"

//#include <math.h>

#ifndef ATTACKDIRECTIONOBJECT
#define ATTACKDIRECTIONOBJECT

class Player;
class Enemy;

class AttackDirectionObject : public CollisionObject
{

	VectorFloat direction;

	int window_width;
	int window_height;

	float min_size_collision = 10;
	float range = 100;

	bool attacked = false;

	Player * target_player;

public:

	AttackDirectionObject(const std::string _name, const std::string texture_name, VectorFloat _position, VectorFloat _size, const float _rotation, VectorFloat _scale, const bool _flipX, const bool _flipY, const int _sorting_order, const float _speed, Player * _target);

	AttackDirectionObject(const std::string _name, const std::string texture_name, VectorFloat _position, VectorFloat _size, const float _rotation, VectorFloat _scale, VectorInt offset, VectorInt texture_size, const bool _flipX, const bool _flipY, const int _sorting_order, const float _speed, Player * _target);

	void start();

	void update();

	VectorFloat getDirection();

	void onCollision(std::vector<CollisionObject*> others);

	bool isMoving();

};

#endif

