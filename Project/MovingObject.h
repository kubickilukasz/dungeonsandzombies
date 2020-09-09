#pragma once
#include "Object.h"

#ifndef  MOVINGOBJECT
#define MOVINGOBJECT

class MovingObject : public Object
{
private:

	float speed;

	bool can_move = true;

	VectorFloat direction;

public:

	MovingObject(const std::string _name, const std::string texture_name, VectorFloat _position, VectorFloat _size, const float _rotation, VectorFloat _scale, const bool _flipX, const bool _flipY, const int _sorting_order , const float _speed);

	MovingObject(const std::string _name, const std::string texture_name, VectorFloat _position, VectorFloat _size, const float _rotation, VectorFloat _scale, VectorInt offset, VectorInt texture_size, const bool _flipX, const bool _flipY, const int _sorting_order , const float _speed);

	void changeDirection(VectorFloat direction);

	void changeDirection(float _x, float _y);

	void move();

	virtual bool isMoving();

	VectorFloat getDirection();

	float getSpeed();

};

#endif 