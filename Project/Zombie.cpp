#include "Zombie.h"


Zombie::Zombie(const std::string _name, const std::string texture_name, VectorFloat _position, VectorFloat _size, VectorFloat _scale, VectorInt offset, VectorInt texture_size, const int _sorting_order, const float _speed , const int _max_health, const int _damage, Player * player)
	: Enemy(_name, texture_name, _position, _size , 0, _scale, offset , texture_size ,false, false, _sorting_order , _speed , false, _max_health, _max_health, _damage , player )
{}

void Zombie::start() {
	playAnimation("zombie_idle");
}

void Zombie::updateEnemy() {

	if (player != nullptr) {
		VectorFloat to_player_direction = player->getPosition() - position;

		if (!is_attack) {

			if (to_player_direction.length() < range_view) {
				changeDirection(to_player_direction.Normalize());
				playAnimation("zombie_run");
			}else {
				changeDirection(VectorFloat());
				playAnimation("zombie_idle");
			}

			if (to_player_direction.length() < range_attack && !is_attack) {
				is_attack = true;
				attack_direction = to_player_direction.Normalize();
				changeDirection(to_player_direction.Normalize() * 0.5);
				playAnimation("zombie_attack");
			}

		}else if (is_attack && current_animation.getIndexFrame() > 5) {

			if (!is_hitting) {
				//try hit player
				if (to_player_direction.length() <= range_attack && abs(VectorFloat::angle(attack_direction, to_player_direction.Normalize())) < 60) {
					player->hit(this);
				}
				is_hitting = true;
			}

			if (is_attack && current_animation.getIndexFrame() >= 6) {
				//end attack
				is_hitting = false;
				is_attack = false;
			}
		}
	}

	if (timer >= hit_time) {

		// if he is not hitted
		if (getFlipX() && getDirection().x > 0) {
			changeFlipX(false);
		}
		else if (!getFlipX() && getDirection().x < 0) {
			changeFlipX(true);
		}
	}

}