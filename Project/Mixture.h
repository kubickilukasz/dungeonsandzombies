#pragma once
#include "CollisionObject.h"
#include "Player.h"
#include "InputManager.h"

#ifndef  MIXTURE
#define MIXTURE

class Mixture :public CollisionObject{

protected:

	int health;
	int damage;

	bool to_delete = false;
	bool is_player_near = false;


public:
	Mixture(const std::string _name, const std::string texture_name, VectorFloat _position, VectorFloat _size, const float _rotation, VectorFloat _scale, VectorInt offset, VectorInt texture_size, const int _sorting_order, const int _health, const int _damage);

	void update();

	void onTrigger(CollisionObject * other);

	bool isMoving();

};

#endif // ! MIXTURE
