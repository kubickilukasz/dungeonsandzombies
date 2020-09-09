#pragma once
#include "MovingObject.h"

#ifndef COLLISIONOBJECT
#define COLLISIONOBJECT

typedef std::list<VectorInt> array_position_collision;

class CollisionObject : public MovingObject {

protected:

	VectorFloat offset_collider;
	VectorFloat size_collider;
	array_position_collision positions_array_collisions;
	bool is_trigger;

public:

	CollisionObject(const std::string _name, const std::string texture_name, VectorFloat _position, VectorFloat _size, const float _rotation, VectorFloat _scale, const bool _flipX, const bool _flipY, const int _sorting_order, const float _speed , const bool is_trigger);

	CollisionObject(const std::string _name, const std::string texture_name, VectorFloat _position, VectorFloat _size, const float _rotation, VectorFloat _scale, VectorInt offset, VectorInt texture_size, const bool _flipX, const bool _flipY, const int _sorting_order, const float _speed, const bool is_trigger);

	VectorFloat getOffsetCollider();

	VectorFloat getSizeCollider();

	array_position_collision getPositionsArrayCollision();

	void setPositionsArrayCollision(array_position_collision _new_postion);

	float getWorldPositionX1();

	float getWorldPositionX2();

	float getWorldPositionY1();

	float getWorldPositionY2();

	virtual void onCollision(std::vector<CollisionObject*> others);

	virtual void onTrigger(CollisionObject* other);

	bool isCollision(CollisionObject * _other);

	bool isTrigger();

};

#endif