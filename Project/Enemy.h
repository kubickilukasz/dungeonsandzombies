#pragma once
#include "Character.h"
#include "Player.h"

#ifndef ENEMY
#define ENEMY

class Player;

class Enemy :public Character
{
protected:

	void onHit(Character * hitter);

	void onDeath();

	VectorFloat hit_direction;

	float hit_time = 8;
	float timer = 10000;

	Player * player;

	bool is_attack = false;
	bool is_hitting = false;

	VectorFloat attack_direction;

	float time_to_destroy = 20;
	float timer_to_death = 0;

public:

	Enemy(const std::string _name, const std::string texture_name, VectorFloat _position, VectorFloat _size, const float _rotation, VectorFloat _scale, const bool _flipX, const bool _flipY, const int _sorting_order, const float _speed, const bool is_trigger,const int _health,const int _max_health,const int _damage, Player * player);

	Enemy(const std::string _name, const std::string texture_name, VectorFloat _position, VectorFloat _size, const float _rotation, VectorFloat _scale, VectorInt offset, VectorInt texture_size, const bool _flipX, const bool _flipY, const int _sorting_order, const float _speed, const bool is_trigger,const int _health,const int _max_health,const int _damage, Player * player);

	void update();

	virtual void updateEnemy() = 0;

};

#endif // ! 

