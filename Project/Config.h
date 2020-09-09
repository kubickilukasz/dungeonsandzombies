#pragma once
#include "Singleton.h"
#include <map>
#include <string>
#include <unordered_map>
#include <fstream>
#include <sstream>

#ifndef CONFIG
#define CONFIG

class Config
{
private:

	std::unordered_map<std::string, std::string> configs;

	void fillDefault(const std::string name, const std::string default_value);

public:

	Config();
	~Config();

	std::string get(const std::string name);
	int getInt(const std::string name);
	float getFloat(const std::string name);



};

typedef Singleton<Config> SConfig;

#endif

