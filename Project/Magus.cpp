#include "Magus.h"

Magus::Magus(const std::string _name, const std::string texture_name, VectorFloat _position, VectorFloat _size, VectorFloat _scale, VectorInt offset, VectorInt texture_size, const int _sorting_order, const float _speed, const int _max_health, const int _damage, Player * player)
	: Enemy(_name, texture_name, _position, _size, 0, _scale, offset, texture_size, false, false, _sorting_order, _speed, false, _max_health, _max_health, _damage, player)
{}

void Magus::start() {
	playAnimation("magus_idle");
}

void Magus::updateEnemy() {

	if (player != nullptr) {
		VectorFloat to_player_direction = player->getPosition() - position;

		if (!is_attack) {

			if (to_player_direction.length() < range_view) {
				changeDirection(to_player_direction.Normalize());
				playAnimation("magus_run");
			}
			else {
				changeDirection(VectorFloat());
				playAnimation("magus_idle");
			}

			if (to_player_direction.length() < range_attack && !is_attack) {
				is_attack = true;
				changeDirection(VectorFloat());
				playAnimation("magus_attack");
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

		}else if (is_attack && current_animation.getIndexFrame() >= 9) {

			if (to_player_direction.length() <= range_attack) {
				Bullet * bl = dynamic_cast<Bullet*>(create(std::shared_ptr<Object>(new Bullet("bullet", "bullet", position + VectorFloat(getFlipX() ? -10.0 : 10.0, 0), { 100,100 }, 0, { 1,1 }, { 0,0 }, {32,32}, 10,30,10))));
				bl->changeDirection(to_player_direction.Normalize());
			}

			is_attack = false;
	
		}else if (is_attack) {
			if (getFlipX() && to_player_direction.x > 0) {
				changeFlipX(false);
			}
			else if (!getFlipX() && to_player_direction.x < 0) {
				changeFlipX(true);
			}
		}
	}

}