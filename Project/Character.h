#pragma once
#include "CollisionObject.h"

#ifndef CHARACTER
#define CHARACTER

class Character :public CollisionObject{

protected:

	int health;
	int max_health;
	int damage;

	virtual void onHit(Character * hitter) = 0;

	virtual void onDeath() = 0;

	bool is_dead = false;

public:

	Character(const std::string _name, const std::string texture_name, VectorFloat _position, VectorFloat _size, const float _rotation, VectorFloat _scale, const bool _flipX, const bool _flipY, const int _sorting_order
		, const float _speed, const bool is_trigger , int _health , int _max_health, int _damage );

	Character(const std::string _name, const std::string texture_name, VectorFloat _position, VectorFloat _size, const float _rotation, VectorFloat _scale, VectorInt offset, VectorInt texture_size, const bool _flipX, const bool _flipY
		, const int _sorting_order, const float _speed, const bool is_trigger, int _health, int _max_health, int _damage);

	int getHealth();

	int getMaxHealth();

	int getDamage();

	void changeDamage(int new_damage);

	void changeMaxHealth(int new_max_health);

	void changeHealth(int new_health);

	void hit(Character * hitter);
	void hit(const int damage);

};

#endif // !1

