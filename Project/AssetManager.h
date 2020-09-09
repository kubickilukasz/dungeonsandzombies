#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <unordered_map>
#include <map>
#include <list>
#include "Animation.h"
#include "Log.h"
#include "Singleton.h"
#include "Config.h"
#include <fstream>
#include <sstream>

#ifndef ASSETMANAGER
#define ASSETMANAGER

typedef  std::map<std::string, sf::Image > str_images;
typedef  std::map<std::string, sf::Texture > str_textures;
typedef  std::list<std::string> str_images_names;
typedef  std::unordered_map<std::string , Animation> animations_type;

class AssetManager {

private:

	const std::string images_folder;

	const std::string audio_folder;

	str_images_names images_list_names;

	str_images images;

	str_textures textures;

	animations_type animations;

	sf::Font default_font;

public:

	AssetManager();

	bool loadTextures();

	bool loadAnimations();

	sf::Image & getImage(const std::string name);
	sf::Texture & getTexture(const std::string name);
	Animation getAnimation(const std::string name);
	sf::Font & getFont();

};

#endif
