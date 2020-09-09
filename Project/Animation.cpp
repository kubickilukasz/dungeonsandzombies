#include "Animation.h"

Animation::Animation() : name("default"), frames({}), speed(1), back(false) , loop(false) {}

Animation::Animation(const std::string _name, Frames _frames, const float _speed, const bool _back, const bool _loop) : name(_name) , frames(_frames) , speed(_speed), back(_back), loop(_loop) {
	current_frame = 0;
}

void Animation::setFrame(const int frame_index) {

	if (frame_index >= 0 && frame_index < frames.size()) {
		current_frame = frame_index;
	}

}

Frame & Animation::getFrame() {
	return frames[current_frame];
}

std::string Animation::getName() {
	return name;
}

int Animation::getIndexFrame() {
	return current_frame;
}

void Animation::update(const float elapsed_time) {

	time += elapsed_time;

	if (time > speed) {
		if (!back) {
			current_frame++;
			if (current_frame >= frames.size()) {
				if (loop) {
					current_frame = 0;
				}else {
					current_frame = frames.size() - 1;
				}
			}
		}else {
			current_frame--;
			if (current_frame < 0) {
				if (!loop) {
					current_frame = 0;
				}
				else {
					current_frame = frames.size() - 1;
				}
			}
		}
		time = 0;
	}
}

void Animation::reset() {
	time = 0;
}

bool Animation::haveFrames() {
	return frames.size() > 0;
}
