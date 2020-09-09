#include "AssetManager.h"

AssetManager::AssetManager() : images_folder("textures"), audio_folder("audio") {

	int id_texture = 0;

	images_list_names.push_back("sample");
	std::fstream file(Singleton<Config>::instance()->get("images"));

	if (file.is_open()) {

		std::string line;
		while (std::getline(file, line)) {
			images_list_names.push_back(line);
		}
		file.close();

	}else {
		throw Log("_error_asset", "NONE FILE images.txt");
	}

	if (!default_font.loadFromFile("default_font.ttf")) {
		throw Log("_error_asset", "NONE FILE default_font.ttf");
	}

}

bool AssetManager::loadTextures() {

	bool correct_load = true;

	//default
	images["_default_image"].create(1,1,sf::Color(255,0,0));

	for (str_images_names::iterator i = images_list_names.begin(); i != images_list_names.end(); ++i) {

		std::string file_name(images_folder + "/" + *i + ".png");

		if (!images[*i].loadFromFile(file_name)) {

			correct_load = false;

		}
	}

	textures["_default_texture"].create(1,1);

	std::fstream file(Singleton<Config>::instance()->get("textures"));

	if (file.is_open()) {

		std::string line;

		while (std::getline(file, line)) {

			std::istringstream str_stream(line);

			std::string name_texture;
			std::string name_image;
			
			int posX;
			int posY;
			int width;
			int height;
			int repeated;

			str_stream >> name_texture >> name_image;

			if (str_stream.end) {
				str_images::iterator it = images.find(name_image);

				if (it == images.end()) {		 
					correct_load = false;
					break;
				}else {

					str_stream >> posX >> posY;
					str_stream >> width >> height;

					str_stream >> repeated;

					if (width == 0 || height == 0) {
						textures[name_texture] = sf::Texture();
						textures[name_texture].loadFromImage(images[name_image]);
					}else {

						width = width > 0 ? width : 1;
						height = height > 0 ? height : 1;

						textures[name_texture] = sf::Texture();
						textures[name_texture].loadFromImage(images[name_image], { posX , posY , width , height });
					}

					if (repeated == 1) {
						textures[name_texture].setRepeated(true);
					}
				}

			}else {
				correct_load = false;
				break;
			}
		}

		file.close();
	}
	else {
		correct_load = false;
	}

	return correct_load;

}

bool AssetManager::loadAnimations() {

	bool correct_load = true;

	std::fstream file("animations.txt");

	if (file.is_open()) {

		std::string line;

		bool is_reading_frames = false;

		std::string name_animation;
		float speed = 1;
		bool back = false;
		bool loop = false;
		int number_frames = 0;
		Frames frames{};

		while (std::getline(file, line)) {

			std::istringstream str_line(line);

			if (!is_reading_frames) {

				str_line >> name_animation;
				str_line >> number_frames;
				str_line >> speed;
				str_line >> back;
				str_line >> loop;

				frames.reserve(number_frames);

				is_reading_frames = true;

			}else {
				if (number_frames > 0) {

					int pos_x, pos_y, width, height;

					str_line >> pos_x >> pos_y >> width >> height;

					frames.emplace_back(pos_x , pos_y , width , height);

					number_frames--;

					if (number_frames == 0) {

						animations[name_animation] = Animation(name_animation, frames, speed, back, loop);

						frames.clear();

						is_reading_frames = false;

					}
				}
			}



		}


	}else {

		correct_load = false;

	}

	return correct_load;
}

sf::Image & AssetManager::getImage(const std::string name) {

	str_images::iterator i = images.find(name);

	if (i == images.end()) {
		SLogger::instance()->add({ "_none_image" , name });
		return (images.begin())->second;
	}else {
		return i->second;
	}

}

sf::Texture & AssetManager::getTexture(const std::string name) {

	str_textures::iterator i = textures.find(name);

	if (i == textures.end()) {
		SLogger::instance()->add({ "_none_texture" , name });
		return (textures.begin())->second;
	}
	else {
		return i->second;
	}
}

Animation AssetManager::getAnimation(const std::string name) {

	animations_type::iterator i = animations.find(name);

	if (i == animations.end()) {
		SLogger::instance()->add({ "_none_animation" , name });
		return Animation();
	}
	else {
		return i->second;
	}

}

sf::Font & AssetManager::getFont() {
	return default_font;
}