#include "MovingObject.h"

MovingObject::MovingObject(const std::string _name, const std::string texture_name, VectorFloat _position, VectorFloat _size, const float _rotation, VectorFloat _scale, const bool _flipX, const bool _flipY, const int _sorting_order, const float _speed)
: Object(_name, texture_name, _position, _size, _rotation, _scale, _flipX, _flipY, _sorting_order) , speed(_speed) ,can_move(true)
{
	
	direction = VectorFloat();

}

MovingObject::MovingObject(const std::string _name, const std::string texture_name, VectorFloat _position, VectorFloat _size, const float _rotation, VectorFloat _scale, VectorInt offset, VectorInt texture_size, const bool _flipX, const bool _flipY, const int _sorting_order, const float _speed)
	: Object(_name, texture_name, _position, _size, _rotation, _scale, offset , texture_size, _flipX, _flipY, _sorting_order) , speed(_speed), can_move(true)
{

	direction = VectorFloat();

}

void MovingObject::changeDirection(VectorFloat _direction) {
	direction = _direction;
}

void MovingObject::changeDirection(float _x, float _y) {
	direction.x = _x;
	direction.y = _y;
}


void MovingObject::move() {

	VectorFloat new_position = position + (direction * speed * Time::getElapsedTime());

	changePosition(new_position.x, new_position.y);

}

bool MovingObject::isMoving() {
	return direction.length() != 0;
}

VectorFloat MovingObject::getDirection() {
	return direction;
}

float MovingObject::getSpeed() {
	return speed;
}