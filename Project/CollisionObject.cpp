#include "CollisionObject.h"

CollisionObject::CollisionObject(const std::string _name, const std::string texture_name, VectorFloat _position, VectorFloat _size, const float _rotation, VectorFloat _scale, const bool _flipX, const bool _flipY, const int _sorting_order, const float _speed, const bool is_trigger)
	: MovingObject(_name, texture_name, _position, _size, _rotation, _scale, _flipX, _flipY, _sorting_order, _speed), is_trigger(is_trigger)
{
	offset_collider = VectorFloat();
	size_collider = _size;

}

CollisionObject::CollisionObject(const std::string _name, const std::string texture_name, VectorFloat _position, VectorFloat _size, const float _rotation, VectorFloat _scale, VectorInt offset, VectorInt texture_size, const bool _flipX, const bool _flipY, const int _sorting_order, const float _speed, const bool is_trigger)
	: MovingObject(_name, texture_name, _position, _size, _rotation, _scale, offset, texture_size, _flipX, _flipY, _sorting_order, _speed) , is_trigger(is_trigger)
{
	
	offset_collider = VectorFloat();
	size_collider = _size;
}


VectorFloat CollisionObject::getOffsetCollider() {
	return offset_collider;
}

VectorFloat CollisionObject::getSizeCollider() {
	return size_collider;
}

array_position_collision CollisionObject::getPositionsArrayCollision() {
	return positions_array_collisions;
}

void CollisionObject::setPositionsArrayCollision(array_position_collision _new_postions) {
	positions_array_collisions = _new_postions;
}

float CollisionObject::getWorldPositionX1(){
	return (position.x - size_collider.x / 2) + offset_collider.x;
}

float CollisionObject::getWorldPositionX2() {
	return (position.x + size_collider.x / 2) + offset_collider.x;
}

float CollisionObject::getWorldPositionY1() {
	return (position.y - size_collider.y / 2) + offset_collider.y;
}

float CollisionObject::getWorldPositionY2() {
	return (position.y + size_collider.y / 2) + offset_collider.y;
}

void CollisionObject::onCollision(std::vector<CollisionObject*> others) {

}

void CollisionObject::onTrigger(CollisionObject* other) {

}

bool CollisionObject::isCollision(CollisionObject * _other) {

	return this->getWorldPositionX1() < _other->getWorldPositionX2() && this->getWorldPositionX2() > _other->getWorldPositionX1() 
		&& this->getWorldPositionY1() < _other->getWorldPositionY2() && this->getWorldPositionY2() > _other->getWorldPositionY1();

}

bool CollisionObject::isTrigger() {
	return is_trigger;
}