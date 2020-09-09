#include "AttackDirectionObject.h"


AttackDirectionObject::AttackDirectionObject(const std::string _name, const std::string texture_name, VectorFloat _position, VectorFloat _size, const float _rotation, VectorFloat _scale, const bool _flipX, const bool _flipY, const int _sorting_order, const float _speed, Player * _target)
	: CollisionObject( _name,  texture_name,  _position,  _size, _rotation,  _scale,  _flipX,  _flipY, _sorting_order,  _speed , true), target_player(_target)
{
	sprite.setOrigin(width / 2, height);

	window_height = SConfig::instance()->getInt("height");
	window_width = SConfig::instance()->getInt("width");

}

AttackDirectionObject::AttackDirectionObject(const std::string _name, const std::string texture_name, VectorFloat _position, VectorFloat _size, const float _rotation, VectorFloat _scale, VectorInt offset, VectorInt texture_size, const bool _flipX, const bool _flipY, const int _sorting_order, const float _speed, Player * _target)
	: CollisionObject(_name, texture_name, _position, _size, _rotation, _scale, offset , texture_size , _flipX, _flipY, _sorting_order, _speed, true) , target_player(_target)
{

	sprite.setOrigin(width/2 , height);

	window_height = SConfig::instance()->getInt("height");
	window_width = SConfig::instance()->getInt("width");
}

void AttackDirectionObject::start() {

	

}

void AttackDirectionObject::update() {

	VectorFloat mouse_position = SInputManager::instance()->getMousePosition();

	mouse_position.x -= window_width / 2;
	mouse_position.y -= window_height / 2;

	direction = mouse_position.Normalize();

	changeRotation(-VectorFloat::angle(direction , VectorFloat(0,-1)));

	VectorFloat real_direction = target_player->isAttack() ? target_player->getCurrentDirectionAttack().Normalize() : direction;

	offset_collider = (real_direction * range) * 0.5;

	size_collider.x = range;
	size_collider.y = range;

	if (!target_player->isAttack()) {
		attacked = false;
	}

}

VectorFloat AttackDirectionObject::getDirection() {
	return direction;
}

void AttackDirectionObject::onCollision(std::vector<CollisionObject*> others) {

	if (!attacked && target_player != nullptr && target_player->isHitting()) {
		Character * char_player = dynamic_cast<Character*>(target_player);
		for (CollisionObject * obj : others) {
			if (obj != nullptr && !obj->isTrigger()) {
				if (Enemy * enm = dynamic_cast<Enemy*>(obj)) {
					enm->hit(char_player);
				}
			}
		}
		attacked = true;
	}
}

bool AttackDirectionObject::isMoving() {
	return true;
}