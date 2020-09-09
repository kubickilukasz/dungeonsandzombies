#include "Wall.h"


Wall::Wall(const std::string _name, const std::string texture_name, VectorFloat _position, VectorFloat _size, const float _rotation, VectorFloat _scale, VectorInt offset, VectorInt texture_size, const bool _flipX, const bool _flipY
	, const int _sorting_order)
	: CollisionObject(_name, texture_name, _position, _size, _rotation, _scale, offset, texture_size, _flipX, _flipY, _sorting_order, 0, false)
{
	sprite.setOrigin(0, 0);
	offset_collider = VectorFloat(size.x/2, size.y /2);
}