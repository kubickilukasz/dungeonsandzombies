#pragma once
#include <string>
#include <list>
#include "Time.h"


#ifndef LOG
#define LOG

class Log
{

	std::string code;
	std::string info;
	std::string timestr;

	void setCurrentTime();

public: 

	Log();
	Log(const std::string code);
	Log(const std::string code,const std::string info);
	std::string getStr();

};

#endif

