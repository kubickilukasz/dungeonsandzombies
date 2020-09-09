#include "Character.h"

Character::Character(const std::string _name, const std::string texture_name, VectorFloat _position, VectorFloat _size, const float _rotation, VectorFloat _scale, const bool _flipX, const bool _flipY, const int _sorting_order, const float _speed, const bool is_trigger, const int _health, const int _max_health, const int _damage)
	: CollisionObject(_name, texture_name, _position, _size, _rotation, _scale, _flipX, _flipY, _sorting_order, _speed, is_trigger) , health(_health) , max_health(_max_health) , damage(_damage)
{

}

Character::Character(const std::string _name, const std::string texture_name, VectorFloat _position, VectorFloat _size, const float _rotation, VectorFloat _scale, VectorInt offset, VectorInt texture_size, const bool _flipX, const bool _flipY, const int _sorting_order, const float _speed, const bool is_trigger, const int _health, const int _max_health, const int _damage)
	: CollisionObject(_name, texture_name, _position, _size, _rotation, _scale, offset, texture_size, _flipX, _flipY, _sorting_order, _speed, is_trigger), health(_health), max_health(_max_health), damage(_damage)
{

}

int Character::getHealth() {
	return health;
}

int Character::getMaxHealth() {
	return max_health;
}

int Character::getDamage() {
	return damage;
}

void Character::changeDamage(int new_damage) {
	damage = new_damage;
}

void Character::changeMaxHealth(int new_max_health) {
	max_health = new_max_health;
}

void Character::changeHealth(int new_health) {
	health = new_health;
}

void Character::hit(Character * hitter) {
	health -= hitter->getDamage();
	onHit(hitter);
	if (health < 0 && !is_dead) {
		is_dead = true;
		onDeath();
	}
}

void Character::hit(const int damage) {
	health -= damage;
	onHit(nullptr);
	if (health < 0 && !is_dead) {
		is_dead = true;
		onDeath();
	}
}

