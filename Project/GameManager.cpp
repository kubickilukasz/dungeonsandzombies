#include "GameManager.h"

GameManager::GameManager() {

	try {
		if (!Singleton<AssetManager>::instance()->loadTextures()) {
			throw Log("_error_textures", "ERROR WITH LOADING TEXTURES");
		}
	
		if (!Singleton<AssetManager>::instance()->loadAnimations()){
			throw Log("_error_animations", "ERROR WITH LOADING ANIMATIONS");
		}

	}catch (Log expection) {
		Singleton<Logger>::instance()->add(expection);
	}

	id_level_to_clear = 0; // to load first level
}

void GameManager::run() {

	Singleton<Logger>::instance()->add({ "_run", "Function run..." });

	while (window.isOpen()) {

		Time::restartClock();
		sf::Event event;
		while (window.pollEvent(event)) {

			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		if (end_game) {
			window.close();
		}

		window.clear(sf::Color::Black);
		if (current_level != nullptr) {
			current_level->draw(window);

		}else{
			SLogger::instance()->add({ "_error_level", "NO LEVEL IN GAME LOOP" });
			window.close();
		}

		if (id_level_to_clear >= 0 && id_level_to_clear < levels.size()) {
			levels[id_level_to_clear].clear();
			current_level->load();
			id_level_to_clear = -1;
		}

		window.display();
	}
}

void GameManager::createLevels() {

	levels.reserve(3);

	levels.emplace_back(0, "menu", *this);
	levels.emplace_back(1, "level_1", *this);
	levels.emplace_back(2, "about" , *this);

}

void GameManager::start() {

	//load levels

	//sf::VideoMode::GetMode(0)

	createLevels();

	SLogger::instance()->add({ "_start", "Function start..." });

	int width = SConfig::instance()->getInt("width");
	int height = SConfig::instance()->getInt("height");
	int windowed = SConfig::instance()->getInt("windowed");
	std::string window_name = SConfig::instance()->get("window_name");

	if (windowed == 1) {
		window.create(sf::VideoMode(width, height), window_name, sf::Style::Fullscreen);
	}else {
		window.create(sf::VideoMode(width, height), window_name);
	}

	SInputManager::instance()->setRelativeWindow(window);

	int max_frame_rate = SConfig::instance()->getInt("max_frame_rate");

	if (max_frame_rate < 1) {
		max_frame_rate = 1;
	}

	window.setFramerateLimit(max_frame_rate);
	
	try {
		loadLevel(0);
	}
	catch (Log expection) {
		Singleton<Logger>::instance()->add(expection);
	}

	run();

}

void GameManager::loadLevel(const int id_level) {

	if (levels.size() > id_level && id_level >= 0) {

		if (current_level != nullptr) {
			id_level_to_clear = current_level->getId();
		}

		current_level = &levels[id_level];

	}else {
		throw Log("_level_error" , "NO FIND LEVEL");
	}

}

void GameManager::endGame() {
	end_game = true;
}


GameManager::~GameManager() {

}



