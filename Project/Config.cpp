#include "Config.h"

void Config::fillDefault(const std::string name, const std::string default_value) {

	std::unordered_map<std::string, std::string>::iterator position = configs.find(name);

	if (position == configs.end()) {
		configs[name] = default_value;
	}

}

Config::Config() {

	std::fstream file("config.txt");

	if (file.is_open()) {

		std::string line;

		while (std::getline(file, line)) {

			std::istringstream str_stream(line);
			std::string _name;
			std::string _value;
			str_stream >> _name;
			str_stream >> _value;

			configs[_name] = _value;

		}

		file.close();

	}

	fillDefault("window_name", "Game");
	fillDefault("width", "800");
	fillDefault("height", "600");
	fillDefault("windowed", "0");
	fillDefault("textures", "textures.txt");
	fillDefault("images", "images.txt");
	fillDefault("levels_folder", "levels");
	fillDefault("zoom", "1");
	fillDefault("max_frame_rate" , "250");


}

Config::~Config() {}

std::string Config::get(const std::string name) {

	std::unordered_map<std::string, std::string>::iterator position = configs.find(name);

	if (position == configs.end()) {
		return "";
	}else {
		return position->second;
	}

}

int Config::getInt(const std::string name) {

	std::string value = get(name);

	return std::stoi(value);

}

float Config::getFloat(const std::string name) {

	std::string value = get(name);

	return std::stof(value);

}