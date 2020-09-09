#pragma once
#include "Log.h"
#include "Singleton.h"
#include <string>
#include <list>
#include <fstream>
#include <iostream>

#ifndef LOGGER
#define LOGGER

class Logger
{

private:

	std::string file_name;

	std::list<Log> list_logs;

public:

	Logger();

	Logger(const std::string file_name);

	~Logger();

	void add(Log exception);

	bool saveToFile();


};

typedef Singleton<Logger> SLogger;

#endif 



