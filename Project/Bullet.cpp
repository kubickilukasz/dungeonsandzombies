#include "Bullet.h"

Bullet::Bullet(const std::string _name, const std::string texture_name, VectorFloat _position, VectorFloat _size, const float _rotation, VectorFloat _scale, VectorInt offset, VectorInt texture_size, const int _sorting_order, const float _speed, const int _damage)
	: CollisionObject(_name, texture_name, _position, _size, _rotation, _scale, offset, texture_size, false, false, _sorting_order, _speed, true), damage(_damage)
{
	size_collider = VectorFloat(size.x / 4, size.y/4);
	offset_collider.y += size.y / 2.5;
	playAnimation("bullet");
}

void Bullet::update() {

	timer += Time::getElapsedTime();
	if (to_delete || timer > time_to_die) {
		remove(this);
	}
}

void Bullet::onTrigger(CollisionObject* other) {

	if (Player * player = dynamic_cast<Player *>(other)) {
		player->hit(damage);
		to_delete = true;
	}

}
