#pragma once
#include "CollisionObject.h"

#ifndef WALL
#define WALL


class Wall :public CollisionObject
{

public:

	Wall(const std::string _name, const std::string texture_name, VectorFloat _position, VectorFloat _size, const float _rotation, VectorFloat _scale, VectorInt offset, VectorInt texture_size, const bool _flipX, const bool _flipY
		, const int _sorting_order);

};

#endif // !1

