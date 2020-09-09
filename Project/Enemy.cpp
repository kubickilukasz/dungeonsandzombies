#include "Enemy.h"


Enemy::Enemy(const std::string _name, const std::string texture_name, VectorFloat _position, VectorFloat _size, const float _rotation, VectorFloat _scale, const bool _flipX, const bool _flipY, const int _sorting_order, const float _speed, const bool is_trigger, const int _health, const int _max_health, const int _damage, Player * player)
	: Character(_name, texture_name, _position, _size, _rotation, _scale, _flipX, _flipY, _sorting_order, _speed, is_trigger, _health , _max_health , _damage), player(player)
{
	size_collider.x = size.x / 3;
	size_collider.y = size.y / 5;

	offset_collider.y += size.y / 2.5;
}

Enemy::Enemy(const std::string _name, const std::string texture_name, VectorFloat _position, VectorFloat _size, const float _rotation, VectorFloat _scale, VectorInt offset, VectorInt texture_size, const bool _flipX, const bool _flipY, const int _sorting_order, const float _speed, const bool is_trigger, const int _health, const int _max_health, const int _damage, Player * player)
	: Character(_name, texture_name, _position, _size, _rotation, _scale, offset, texture_size, _flipX, _flipY, _sorting_order, _speed, is_trigger, _health, _max_health, _damage), player(player)
{
	size_collider.x = size.x / 3;
	size_collider.y = size.y / 5;

	offset_collider.y += size.y / 2.5;
}

void Enemy::update() {

	if (!is_dead) {

		updateEnemy();

		if (!is_dead && timer < hit_time) {

			if (timer / hit_time > 0.2) {
				sprite.setColor(sf::Color(255, 255, 255, 255));
			}
			changeDirection(hit_direction * (1 - timer / hit_time));
			timer += Time::getElapsedTime();
		}

	}else {
		changeDirection(VectorFloat());
		timer_to_death += Time::getElapsedTime();

		if (time_to_destroy < timer_to_death) {
			remove(this);
		}
	}
}

void Enemy::onHit(Character * hitter) {

	if (!is_dead) {

		timer = 0;
		if (hitter != nullptr) {
			hit_direction = (position - hitter->getPosition()).Normalize();
			changeDirection(hit_direction);
		}
	//	is_attack = false;
	//	is_hitting = false;
		sprite.setColor(sf::Color(255, 0, 0, 255));

	}
}

void Enemy::onDeath() {
	
	sprite.setColor(sf::Color(0, 0, 0, 255));
	playAnimation(name + "_death");
	is_attack = false;
	is_trigger = true;

}