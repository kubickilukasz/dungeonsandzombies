#pragma once
#include <vector>
#include <string>
#include "Singleton.h"
#include "Logger.h"


#ifndef ANIMATION
#define ANIMATION

struct Frame {

	 int posX;
	 int posY;
	 int width;
	 int height;

	 Frame(int _pos_x, int _pos_y, int _width, int _height) : posX(_pos_x) , posY(_pos_y) , width(_width), height(_height){}

};

typedef std::vector<Frame> Frames;

class Animation
{
	std::string name;
	Frames frames;
	float speed = 1;
	float time = 0;
	int current_frame = 0;
	bool back;
	bool loop;


public:

	Animation();

	Animation(const std::string _name , Frames _frames , const float _speed, const bool _back, const bool _loop);

	void setFrame(const int frame_index);

	Frame & getFrame();

	std::string getName();

	int getIndexFrame();

	void update(const float elapsedTime);

	void reset();

	bool haveFrames();


};

#endif

