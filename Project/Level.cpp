#include "Level.h"

array_position_collision Level::getPositionsCollision(CollisionObject * object) {

	deletePositionsCollision(object);

	array_position_collision temp_positions;

	int x1 = 0;
	int y1 = 0;

	int current_pos_x = max_collision_width.x;
	int current_pos_y = max_collision_width.x;

	while (object->getWorldPositionX1() > current_pos_x) {
		x1++;
		current_pos_x += square_collision;
	}

	while (object->getWorldPositionY1() > current_pos_y) {
		y1++;
		current_pos_y += square_collision;
	}

	if (x1 < 0) x1 = 0;
	if (x1 >= collision_objects.size()) x1 = collision_objects.size() - 1;
	if (y1 < 0) y1 = 0;
	if (y1 >= collision_objects[x1].size()) y1 = collision_objects[x1].size() - 1;

	int x2 = x1;
	int y2 = y1;

	while (object->getWorldPositionX2() >= current_pos_x) {
		x2++;
		current_pos_x += square_collision;
	}

	while (object->getWorldPositionY2() >= current_pos_y) {
		y2++;
		current_pos_y += square_collision;
	}

	if (x2 < 0) x2 = 0;
	if (x2 >= collision_objects.size()) x2 = collision_objects.size() - 1;
	if (y2 < 0) y2 = 0;
	if (y2 >= collision_objects[x1].size()) y2 = collision_objects[x1].size() - 1;

	for (int x = x1; x <= x2; x++) {
		for (int y = y1; y <= y2; y++) {


			collision_objects[x][y].push_back(object);
			temp_positions.emplace_back(x, y);
		}
	}

	object->setPositionsArrayCollision(temp_positions);

	//

	return temp_positions;

}

void Level::deletePositionsCollision(CollisionObject * object) {

	array_position_collision temp_positions = object->getPositionsArrayCollision();

	for (VectorInt i : temp_positions) {

		std::list<CollisionObject*>::iterator it = find(collision_objects[i.x][i.y].begin(), collision_objects[i.x][i.y].end(), object);

		collision_objects[i.x][i.y].erase(it);

	}

	temp_positions.clear();

	object->setPositionsArrayCollision(temp_positions);
}

Level::Level(const int & id_level,const std::string name, GameManager & _game_manager): id_level(id_level) , name(name), square_collision(200), game_manager(_game_manager){

	SLogger::instance()->add({ "_level", "Create level " + name });

};

Level::~Level() {
	this->clear();
}

int Level::getId() {
	return id_level;
}

void Level::load() {

	max_collision_width = VectorInt(-1000, 10000);
	max_collision_height = VectorInt(-1000, 10000);

	collision_objects.resize((int)((max_collision_width.y - max_collision_width.x) / square_collision));

	int number_of_squares = (int)((max_collision_height.y - max_collision_height.x) / square_collision);

	for (int x = 0; x < collision_objects.size(); x++) {
		collision_objects[x].resize(number_of_squares);
	}

	if (id_level == 0) {
		
		SCamera::instance()->setPosition({0,0});

		int width = SConfig::instance()->getInt("width");
		int height = SConfig::instance()->getInt("height");

		float mn_x = width / 1920.0;
		float mn_y = height / 1080.0;

		createObject(std::shared_ptr<Object>(new Zombie("zombie", "zombie", { (float)0, (float)0 }, { 200 ,200 }, { 1,1 }, { 0,0 }, { 32,32 }, 2, 10, 20, 5, nullptr)));
		createObject(std::shared_ptr<Object>(new Object("floor", "back_01", { 0, 0 }, { 2000 ,500 }, 0, { 2,2 }, { 0,0 }, { 1000,250 }, false, false, -1)));

		createObject(std::shared_ptr<Object>(new Object("blood", "blood", { 200, 50 }, { 200 ,200 }, 0, { 1,1 }, false, false, 1)));
		createObject(std::shared_ptr<Object>(new Object("sword", "sword", { 200, 0 }, { 200 ,200 }, 0, { 1,1 }, false, false, 1)));
		createObject(std::shared_ptr<Object>(new Object("helmet", "helmet", { 200, 51 }, { 200 ,200 }, 0, { 1,1 }, false, false, 1)));

		createGUI(std::shared_ptr<GUIElement>(new Text("title", { (int)(300 * mn_x), (int)(100 * mn_y) }, { (int)(38 * mn_x), 0 }, "sample", sf::Color(255, 255, 255, 255), "DUNGEONS & ZOMBIES")));
		createGUI(std::shared_ptr<GUIElement>(new Text("title", {(int)(300 * mn_x), (int)(170 * mn_y) }, { (int)(17 * mn_x), 0 }, "sample", sf::Color(255, 255, 255, 255), "by Lukasz Kubicki")));
		createGUI(std::shared_ptr<GUIElement>(new ChangeLevelButton("_new_game", { (int)(50 * mn_x) , (int)(300 * mn_y) }, { (int)(350 * mn_x) , (int)(150 * mn_y) }, "button", sf::Color(255, 255, 255, 255), sf::Color(120, 120, 120, 255), game_manager, 1, "NEW GAME")));
		createGUI(std::shared_ptr<GUIElement>(new ChangeLevelButton("_about", { (int)(50 * mn_x) , (int)(500 * mn_y) }, { (int)(350 * mn_x) , (int)(150 * mn_y) }, "button", sf::Color(255, 255, 255, 255), sf::Color(120, 120, 120, 255), game_manager, 2, "ABOUT")));
		createGUI(std::shared_ptr<GUIElement>(new ExitButton("_exit_button", { (int)(50 * mn_x) , (int)(700 * mn_y) }, { (int)(350 * mn_x) , (int)(150 * mn_y) }, "button", sf::Color(255, 255, 255, 255), sf::Color(120, 120, 120, 255), game_manager)));

	}else if (id_level == 1) {


		Player * player = new Player("hero_", "hero", { 0,0 }, { 100 ,100 }, 0, { 1,1 }, { 0,0 }, { 32,32 }, 2, 25);
		player->setCreateMenuDeath(&Level::createMenuDeath);
		createObject(std::shared_ptr<Object>(player));

		VictoryTrigger * menu_victory = new VictoryTrigger("trigger_victory", "end", { 3500.0 , -1950.0 }, { 500,100 }, { 1,1 }, { 0,0 }, { 128,32 }, 2);
		menu_victory->setCreateMenuVictory(&Level::createMenuVictory);
		createObject(std::shared_ptr<Object>(menu_victory));

		//ENEMIES and DECORACTIONS

		createObject(std::shared_ptr<Object>(new Object("crack", "crack", { 0, 50 }, { 100 ,100 }, 0, { 1,1 }, false, false, 1)));

		createObject(std::shared_ptr<Object>(new Zombie("zombie", "zombie", { 400.0, (float)0 }, { 100 ,100 }, { 1,1 }, { 0,0 }, { 32,32 }, 2, 10, 20, 5, player)));

		createObject(std::shared_ptr<Object>(new Zombie("zombie", "zombie", { 810.0, (float)-100 }, { 100 ,100 }, { 1,1 }, { 0,0 }, { 32,32 }, 2, 10, 20, 5, player)));
		createObject(std::shared_ptr<Object>(new Zombie("zombie", "zombie", { 800.0, (float)100 }, { 100 ,100 }, { 1,1 }, { 0,0 }, { 32,32 }, 2, 11, 20, 5, player)));

		createObject(std::shared_ptr<Object>(new Zombie("zombie", "zombie", { 1205.0, (float)-150 }, { 100 ,100 }, { 1,1 }, { 0,0 }, { 32,32 }, 2, 11, 20, 5, player)));
		createObject(std::shared_ptr<Object>(new Zombie("zombie", "zombie", { 1200.0, (float)0 }, { 100 ,100 }, { 1,1 }, { 0,0 }, { 32,32 }, 2, 12, 20, 5, player)));
		createObject(std::shared_ptr<Object>(new Zombie("zombie", "zombie", { 1210.0, (float)159 }, { 100 ,100 }, { 1,1 }, { 0,0 }, { 32,32 }, 2, 11, 20, 5, player)));

		createObject(std::shared_ptr<Object>(new Object("blood", "blood", { 1205.0, -100 }, { 100 ,100 }, 0, { 1,1 }, false, false, 1)));
		createObject(std::shared_ptr<Object>(new Object("sword", "sword", { 1205.0, -90 }, { 100 ,100 }, 0, { 1,1 }, false, false, 1)));

		createObject(std::shared_ptr<Object>(new Mixture("mixture", "mixture_health", { (float)(1400), (float)0 }, { 100 ,100 }, 0, { 1,1 }, { 0,0 }, { 32,32 }, 2, 10, 0)));

		createObject(std::shared_ptr<Object>(new Zombie("zombie", "zombie", { 1510.0, (float)20 }, { 115 ,115 }, { 1,1 }, { 0,0 }, { 32,32 }, 2, 8, 30, 8, player))); // big

		createObject(std::shared_ptr<Object>(new Zombie("zombie", "zombie", { 1510.0, (float)-750 }, { 115 ,115 }, { 1,1 }, { 0,0 }, { 32,32 }, 2, 9, 30, 8, player))); // big
		createObject(std::shared_ptr<Object>(new Zombie("zombie", "zombie", { 1400, (float)-700 }, { 115 ,115 }, { 1,1 }, { 0,0 }, { 32,32 }, 2, 8, 30, 8, player))); // big
		createObject(std::shared_ptr<Object>(new Mixture("mixture", "mixture_damage", { (float)(1400), (float)-800 }, { 100 ,100 }, 0, { 1,1 }, { 0,0 }, { 32,32 }, 2, 0, 5)));

		createObject(std::shared_ptr<Object>(new Object("helmet", "helmet", { 1450, -810 }, { 100 ,100 }, 0, { 1,1 }, false, false, 1)));
		createObject(std::shared_ptr<Object>(new Object("blood", "blood", { 1450, -820 }, { 100 ,100 }, 0, { 1,1 }, false, false, 1)));

		createObject(std::shared_ptr<Object>(new Zombie("zombie", "zombie", { 1650, (float)800 }, { 100 ,100 }, { 1,1 }, { 0,0 }, { 32,32 }, 2, 10, 22, 5, player)));
		createObject(std::shared_ptr<Object>(new Zombie("zombie", "zombie", { 1675, (float)900 }, { 100 ,100 }, { 1,1 }, { 0,0 }, { 32,32 }, 2, 10, 22, 5, player)));
		createObject(std::shared_ptr<Object>(new Zombie("zombie", "zombie", { 1500, (float)825 }, { 100 ,100 }, { 1,1 }, { 0,0 }, { 32,32 }, 2, 11, 20, 5, player)));
		createObject(std::shared_ptr<Object>(new Zombie("zombie", "zombie", { 1600, (float)750 }, { 100 ,100 }, { 1,1 }, { 0,0 }, { 32,32 }, 2, 11, 20, 5, player)));

		createObject(std::shared_ptr<Object>(new Object("helmet", "helmet", { 1600, 1200 }, { 100 ,100 }, 0, { 1,1 }, true, false, 1)));
		createObject(std::shared_ptr<Object>(new Object("crack", "crack", { 1400, 400 }, { 100 ,100 }, 0, { 1,1 }, false, false, 1)));
		createObject(std::shared_ptr<Object>(new Mixture("mixture", "mixture_health", { (float)(1500), (float)1300 }, { 100 ,100 }, 0, { 1,1 }, { 0,0 }, { 32,32 }, 2, 10, 0)));

		createObject(std::shared_ptr<Object>(new Magus("magus", "magus", { (float)(2300), (float)1200 }, { 100 ,100 }, { 1,1 }, { 0,0 }, { 32,32 }, 2, 15, 30, 10, player)));
		createObject(std::shared_ptr<Object>(new Object("crack", "crack", { 2300.0, 1200.0 }, { 100 ,100 }, 0, { 1,1 }, true, false, 1)));

		createObject(std::shared_ptr<Object>(new Zombie("zombie", "zombie", { 3400.0, (float)1150 }, { 115 ,115 }, { 1,1 }, { 0,0 }, { 32,32 }, 2, 9, 35, 10, player))); // big
		createObject(std::shared_ptr<Object>(new Zombie("zombie", "zombie", { 3460.0, (float)1325 }, { 115 ,115 }, { 1,1 }, { 0,0 }, { 32,32 }, 2, 8, 35, 10, player))); // big

		createObject(std::shared_ptr<Object>(new Magus("magus", "magus", { (float)(3700), (float)1250 }, { 100 ,100 }, { 1,1 }, { 0,0 }, { 32,32 }, 2, 15, 30, 10, player)));
		createObject(std::shared_ptr<Object>(new Mixture("mixture", "mixture_health", { (float)(3600), (float)1325 }, { 100 ,100 }, 0, { 1,1 }, { 0,0 }, { 32,32 }, 2, 10, 0)));

		createObject(std::shared_ptr<Object>(new Object("blood", "blood", { 3600.0, -300.0 }, { 100 ,100 }, 0, { 1,1 }, false, false, 1)));
		createObject(std::shared_ptr<Object>(new Mixture("mixture", "mixture_health", { (float)(3600), (float)-200 }, { 100 ,100 }, 0, { 1,1 }, { 0,0 }, { 32,32 }, 2, 10, 0)));

		createObject(std::shared_ptr<Object>(new Object("helmet", "helmet", { 3400, 0 }, { 100 ,100 }, 0, { 1,1 }, false, false, 1)));
		createObject(std::shared_ptr<Object>(new Object("blood", "blood", { 3400, 0 }, { 100 ,100 }, 0, { 1,1 }, false, false, 1)));

		createObject(std::shared_ptr<Object>(new Zombie("zombie", "zombie", { 3400, (float)-400 }, { 100 ,100 }, { 1,1 }, { 0,0 }, { 32,32 }, 2, 12, 20, 5, player)));
		createObject(std::shared_ptr<Object>(new Zombie("zombie", "zombie", { 3700, (float)-425 }, { 100 ,100 }, { 1,1 }, { 0,0 }, { 32,32 }, 2, 11, 25, 5, player)));
		createObject(std::shared_ptr<Object>(new Zombie("zombie", "zombie", { 3300, (float)-480 }, { 100 ,100 }, { 1,1 }, { 0,0 }, { 32,32 }, 2, 11, 25, 5, player)));
		createObject(std::shared_ptr<Object>(new Zombie("zombie", "zombie", { 3450, (float)-500 }, { 100 ,100 }, { 1,1 }, { 0,0 }, { 32,32 }, 2, 13, 25, 5, player)));
		createObject(std::shared_ptr<Object>(new Magus("magus", "magus", { (float)(3600), (float)-500 }, { 100 ,100 }, { 1,1 }, { 0,0 }, { 32,32 }, 2, 15, 30, 10, player)));

		createObject(std::shared_ptr<Object>(new Zombie("zombie", "zombie", { 4500.0, (float)-725 }, { 115 ,115 }, { 1,1 }, { 0,0 }, { 32,32 }, 2, 9, 40, 10, player))); // big
		createObject(std::shared_ptr<Object>(new Zombie("zombie", "zombie", { 4560.0, (float)-770 }, { 115 ,115 }, { 1,1 }, { 0,0 }, { 32,32 }, 2, 8, 40, 10, player))); // big
		createObject(std::shared_ptr<Object>(new Zombie("zombie", "zombie", { 4500.0, (float)-875 }, { 115 ,115 }, { 1,1 }, { 0,0 }, { 32,32 }, 2, 9, 40, 10, player))); // big
		createObject(std::shared_ptr<Object>(new Zombie("zombie", "zombie", { 4560.0, (float)-900 }, { 115 ,115 }, { 1,1 }, { 0,0 }, { 32,32 }, 2, 8, 40, 10, player))); // big
		createObject(std::shared_ptr<Object>(new Magus("magus", "magus", { (float)(4430.0), (float)-722 }, { 100 ,100 }, { 1,1 }, { 0,0 }, { 32,32 }, 2, 15, 30, 10, player)));
		createObject(std::shared_ptr<Object>(new Mixture("mixture", "mixture_damage", { (float)(4660.0), (float)-800 }, { 100 ,100 }, 0, { 1,1 }, { 0,0 }, { 32,32 }, 2, 0, 5)));

		createObject(std::shared_ptr<Object>(new Object("blood", "blood", { 3600.0, -1120 }, { 100 ,100 }, 0, { 1,1 }, false, false, 1)));
		createObject(std::shared_ptr<Object>(new Object("blood", "blood", { 3650.0, -1090 }, { 100 ,100 }, 0, { 1,1 }, false, false, 1)));
		createObject(std::shared_ptr<Object>(new Object("sword", "sword", { 3650.0, -1090 }, { 100 ,100 }, 0, { 1,1 }, false, false, 1)));
		createObject(std::shared_ptr<Object>(new Object("blood", "blood", { 3625.0, -1040 }, { 100 ,100 }, 0, { 1,1 }, false, false, 1)));

		createObject(std::shared_ptr<Object>(new Object("blood", "blood", { 3300.0, -1125 }, { 100 ,100 }, 0, { 1,1 }, false, false, 1)));
		createObject(std::shared_ptr<Object>(new Object("blood", "blood", { 3350.0, -1085 }, { 100 ,100 }, 0, { 1,1 }, false, false, 1)));
		createObject(std::shared_ptr<Object>(new Object("helmet", "helmet", { 3325.0, -1090 }, { 100 ,100 }, 0, { 1,1 }, false, false, 1)));
		createObject(std::shared_ptr<Object>(new Object("blood", "blood", { 3325.0, -1030 }, { 100 ,100 }, 0, { 1,1 }, false, false, 1)));

		createObject(std::shared_ptr<Object>(new Magus("magus", "magus", { (float)(3340.0), (float)-1650 }, { 100 ,100 }, { 1,1 }, { 0,0 }, { 32,32 }, 2, 1, 30, 10, player)));
		createObject(std::shared_ptr<Object>(new Magus("magus", "magus", { (float)(3490.0), (float)-1600 }, { 120 ,120 }, { 1,1 }, { 0,0 }, { 32,32 }, 2, 50, 30, 20, player))); // boss
		createObject(std::shared_ptr<Object>(new Magus("magus", "magus", { (float)(3680.0), (float)-1650 }, { 100 ,100 }, { 1,1 }, { 0,0 }, { 32,32 }, 2, 1, 30, 10, player))); 

		createObject(std::shared_ptr<Object>(new Zombie("zombie", "zombie", { 3300, (float)-1550 }, { 100 ,100 }, { 1,1 }, { 0,0 }, { 32,32 }, 2, 3, 25, 5, player)));
		createObject(std::shared_ptr<Object>(new Zombie("zombie", "zombie", { 3400, (float)-1550 }, { 100 ,100 }, { 1,1 }, { 0,0 }, { 32,32 }, 2, 12, 25, 5, player)));
		createObject(std::shared_ptr<Object>(new Zombie("zombie", "zombie", { 3500, (float)-1550 }, { 100 ,100 }, { 1,1 }, { 0,0 }, { 32,32 }, 2, 12, 25, 5, player)));
		createObject(std::shared_ptr<Object>(new Zombie("zombie", "zombie", { 3600, (float)-1550 }, { 100 ,100 }, { 1,1 }, { 0,0 }, { 32,32 }, 2, 3, 25, 5, player)));

		//WALLS

		std::string wall_texture = "wall_01";

		createFloor({-250, -250}, {1750,250});
		createObject(std::shared_ptr<Object>(new Wall("wall", wall_texture, { -300 ,250 }, { 1650 ,50 }, 0, { 1,1 }, { 0,0 }, { 100,100 }, false, false, 0)));
		createObject(std::shared_ptr<Object>(new Wall("wall", wall_texture, { -300 , -300 }, { 1650 ,50 }, 0, { 1,1 }, { 0,0 }, { 100,100 }, false, false, 0)));
		createObject(std::shared_ptr<Object>(new Wall("wall", wall_texture, { -300 , -300 }, { 50 ,600 }, 0, { 1,1 }, { 0,0 }, { 100,100 }, false, false, 0)));
		

		createFloor({ 1350, -950 }, { 1750,-250 });
		createObject(std::shared_ptr<Object>(new Wall("wall", wall_texture, { 1750 , -1000 }, { 50 , 2050 }, 0, { 1,1 }, { 0,0 }, { 100,100 }, false, false, 0)));
		createObject(std::shared_ptr<Object>(new Wall("wall", wall_texture, { 1300 , -1000 }, { 50 ,700 }, 0, { 1,1 }, { 0,0 }, { 100,100 }, false, false, 0)));
		createObject(std::shared_ptr<Object>(new Wall("wall", wall_texture, { 1300 , -1000 }, { 500 ,50 }, 0, { 1,1 }, { 0,0 }, { 100,100 }, false, false, 0)));
		
		createFloor({ 1350, 250 }, { 1750, 1450 });
		createObject(std::shared_ptr<Object>(new Wall("wall", wall_texture, { 1300 , 1450 }, { 2500 , 50 }, 0, { 1,1 }, { 0,0 }, { 100,100 }, false, false, 0)));
		createObject(std::shared_ptr<Object>(new Wall("wall", wall_texture, { 1300 , 250 }, { 50 , 1250 }, 0, { 1,1 }, { 0,0 }, { 100,100 }, false, false, 0)));
		

		createFloor({ 3250, -2000 }, { 3750, 1050 });
		createObject(std::shared_ptr<Object>(new Wall("wall", wall_texture, { 3750 , -2050 }, { 50 , 1050 }, 0, { 1,1 }, { 0,0 }, { 100,100 }, false, false, 0)));
		createObject(std::shared_ptr<Object>(new Wall("wall", wall_texture, { 3750 , -600 }, { 50 , 2100 }, 0, { 1,1 }, { 0,0 }, { 100,100 }, false, false, 0)));
		createObject(std::shared_ptr<Object>(new Wall("wall", wall_texture, { 3200 , -2050 }, { 50 , 3050 }, 0, { 1,1 }, { 0,0 }, { 100,100 }, false, false, 0)));
		createObject(std::shared_ptr<Object>(new Wall("wall", wall_texture, { 3200 , -2050 }, { 600 , 50 }, 0, { 1,1 }, { 0,0 }, { 100,100 }, false, false, 0)));

		createFloor({ 1750, 1050 }, { 3750, 1450 });
		createObject(std::shared_ptr<Object>(new Wall("wall", wall_texture, { 1750 , 1000 }, { 1500 , 50 }, 0, { 1,1 }, { 0,0 }, { 100,100 }, false, false, 0)));
				
		createFloor({ 3750, -1000 }, { 4750, -600 });
		createObject(std::shared_ptr<Object>(new Wall("wall", wall_texture, { 3750 , -600 }, { 1050 , 50 }, 0, { 1,1 }, { 0,0 }, { 100,100 }, false, false, 0)));
		createObject(std::shared_ptr<Object>(new Wall("wall", wall_texture, { 4750 , -1050 }, { 50 , 450 }, 0, { 1,1 }, { 0,0 }, { 100,100 }, false, false, 0)));
		createObject(std::shared_ptr<Object>(new Wall("wall", wall_texture, { 3750 , -1050 }, { 1050 , 50 }, 0, { 1,1 }, { 0,0 }, { 100,100 }, false, false, 0)));


		//MENU
		createGUI(std::shared_ptr<GUIElement>(new MenuInGame("_menu_in_game" , &game_manager)));


	}else if (id_level == 2) {

		int width = SConfig::instance()->getInt("width");
		int height = SConfig::instance()->getInt("height");

		float mn_x = width / 1920.0;
		float mn_y = height / 1080.0;

		SCamera::instance()->setPosition({ 0,0 });

		createObject(std::shared_ptr<Object>(new Mixture("mixture", "mixture_health", { (float)(0), (float)0 }, { 200 ,200 }, 0, { 1,1 }, { 0,0 }, { 32,32 }, 2, 100, 0)));
		createObject(std::shared_ptr<Object>(new Object("floor", "back_01", { 0, 0 }, { 2000 ,500 }, 0, { 2,2 }, { 0,0 }, { 1000,250 }, false, false, -1)));

		createObject(std::shared_ptr<Object>(new Object("crack", "crack", { 200, 50 }, { 200 ,200 }, 0, { 1,1 }, false, false, 1)));
		createObject(std::shared_ptr<Object>(new Object("helmet", "helmet", { 200, 51 }, { 200 ,200 }, 0, { 1,1 }, false, false, 1)));

		createGUI(std::shared_ptr<GUIElement>(new Text("title", { (int)(300 * mn_x), (int)(100 * mn_y) }, { (int)(38 * mn_x), 0 }, "sample", sf::Color(255, 255, 255, 255), "ABOUT")));
		createGUI(std::shared_ptr<GUIElement>(new Text("t1", { (int)(200 * mn_x), (int)(200 * mn_y) }, { (int)(24 * mn_x), 0 }, "sample", sf::Color(255, 255, 255, 255), "DUNGEONS&ZOMBIES is rouqelike game created in C++ and SFML")));
		createGUI(std::shared_ptr<GUIElement>(new Text("t2", { (int)(200 * mn_x), (int)(275 * mn_y) }, { (int)(24 * mn_x), 0 }, "sample", sf::Color(255, 255, 255, 255), "Your goal is escaping from dungeon")));
		createGUI(std::shared_ptr<GUIElement>(new Text("t3", { (int)(200 * mn_x), (int)(375 * mn_y) }, { (int)(24 * mn_x), 0 }, "sample", sf::Color(255, 255, 255, 255), "Controls:")));
		createGUI(std::shared_ptr<GUIElement>(new Text("t3", { (int)(200 * mn_x), (int)(425 * mn_y) }, { (int)(20 * mn_x), 0 }, "sample", sf::Color(255, 255, 255, 255), "WSAD - moving")));
		createGUI(std::shared_ptr<GUIElement>(new Text("t3", { (int)(200 * mn_x), (int)(475 * mn_y) }, { (int)(20 * mn_x), 0 }, "sample", sf::Color(255, 255, 255, 255), "Mouse - direction of attack")));
		createGUI(std::shared_ptr<GUIElement>(new Text("t3", { (int)(200 * mn_x), (int)(525 * mn_y) }, { (int)(20 * mn_x), 0 }, "sample", sf::Color(255, 255, 255, 255), "Escape - menu")));
		createGUI(std::shared_ptr<GUIElement>(new Text("t3", { (int)(200 * mn_x), (int)(575 * mn_y) }, { (int)(20 * mn_x), 0 }, "sample", sf::Color(255, 255, 255, 255), "Q - get const buffs from mixture")));
		createGUI(std::shared_ptr<GUIElement>(new Text("t3", { (int)(200 * mn_x), (int)(625 * mn_y) }, { (int)(20 * mn_x), 0 }, "sample", sf::Color(255, 255, 255, 255), "E - restore health from mixture")));
		createGUI(std::shared_ptr<GUIElement>(new ChangeLevelButton("_RETURN", { width/2 - (int)(175 * mn_x) , height - (int)(300 * mn_y) }, { (int)(350 * mn_x) , (int)(150 * mn_y) }, "button", sf::Color(255, 255, 255, 255), sf::Color(120, 120, 120, 255), game_manager, 0, "RETURN")));
	}
}

void Level::deleteObjects() {

	collision_objects.clear();
	objects.clear();

}

void Level::deleteGUIElements() {
	gui_elements.clear();
}

void Level::clear() {
	this->deleteObjects();
	this->deleteGUIElements();
}

void Level::createObject(std::shared_ptr<Object> new_object) {

	//object_list::iterator it = objects.begin();

	objects.push_back(new_object);

	if (CollisionObject * collision_object = dynamic_cast<CollisionObject*>(new_object.get())) {
		array_position_collision temp_positions = getPositionsCollision(collision_object);
		collision_object->setPositionsArrayCollision(temp_positions);
	}

	new_object->setLevel(this);
	new_object->setCreateFunction(&Level::createObject);
	new_object->setRemoveFunction(&Level::removeObject);
	new_object->setCreateGUIFunction(&Level::createGUI);
	new_object->setRemoveGUIFunction(&Level::removeGUI);

	new_object->start();

}

void Level::removeObject(Object * object_to_remove) {

	object_list::iterator it = objects.begin();

	while (it != objects.end() && it->get() != object_to_remove && it != objects.end()) {
		it++;
	}

	if (it != objects.end()) {
		if (CollisionObject * collision_object = dynamic_cast<CollisionObject*>(it->get())) {
			deletePositionsCollision(collision_object);
		}

		if ((*iterator_objects).get() == object_to_remove) {
			iterator_objects = objects.erase(it);
			if (iterator_objects != objects.end()) {
				(*iterator_objects)->update();
			}
		}
		else {
			objects.erase(it);
		}
	}

}

void Level::createGUI(std::shared_ptr<GUIElement> gui_element) {

	gui_elements_list::iterator it = gui_elements.end();
	gui_elements.insert(it, gui_element);

	gui_element->setLevel(this);
	gui_element->setCreateFunction(&Level::createObject);
	gui_element->setRemoveFunction(&Level::removeObject);
	gui_element->setCreateGUIFunction(&Level::createGUI);
	gui_element->setRemoveGUIFunction(&Level::removeGUI);

	gui_element->start();
	
}

void Level::removeGUI(GUIElement * gui_element) {
	gui_elements_list::iterator it = gui_elements.begin();

	while (it != gui_elements.end() && it->get() != gui_element) {
		it++;
	}

	if (it != gui_elements.end()) {

		gui_elements.erase(it);
	}
}

void Level::createMenuDeath() {
	createGUI(std::shared_ptr<GUIElement>(new MenuDeath("menu_death",&game_manager)));
}

void Level::createMenuVictory() {
	createGUI(std::shared_ptr<GUIElement>(new MenuVictory("menu_death", &game_manager)));
}

void Level::createFloor(VectorFloat left_up_corner, VectorFloat right_down_corner) {

	float width = right_down_corner.x - left_up_corner.x;
	float height = right_down_corner.y - left_up_corner.y;

	createObject(std::shared_ptr<Object>(new Object("floor", "back_01", { width/2 + left_up_corner.x, height / 2 + left_up_corner.y }, { width ,height }, 0, { 1,1 }, { 0,0 }, { (int)(width/4),(int)(height / 4) }, false, false, -1)));
}

void Level::draw(sf::RenderWindow & window) {

	SCamera::instance()->setTarget(window);

	objects.sort([](std::shared_ptr<Object>  lhs, std::shared_ptr<Object>  rhs) {return  lhs->getSortingOrder() != rhs->getSortingOrder() ? lhs->getSortingOrder() < rhs->getSortingOrder() : lhs->getPosition().y < rhs->getPosition().y; });

	iterator_objects = objects.begin();

	while (iterator_objects != objects.end()) {

		(*iterator_objects)->update();

		if (iterator_objects == objects.end()) {
			break;
		}

		if (MovingObject* moving_object = dynamic_cast<MovingObject*>((*iterator_objects).get())) {

			if (moving_object->isMoving()) {

				//is moving...

				VectorFloat position_before = moving_object->getPosition();
				moving_object->move();

				if (CollisionObject* collision_object = dynamic_cast<CollisionObject*>(moving_object)) {

					//chceck collsions
					array_position_collision positions = getPositionsCollision(collision_object);
					std::vector<CollisionObject*> collided_objects;

					if (collision_object->isTrigger()) {
						for (VectorInt i : positions) {
							for (CollisionObject * obj : collision_objects[i.x][i.y]) {
								std::vector<CollisionObject*>::iterator it = find(collided_objects.begin(), collided_objects.end(), obj);
								if (obj != collision_object && it == collided_objects.end() && collision_object->isCollision(obj)) {
									collided_objects.push_back(obj);

									if (obj->isTrigger()) {
										obj->onTrigger(collision_object);
									}
									collision_object->onTrigger(obj);
								}
							}
						}
					}
					else {
						for (VectorInt i : positions) {
							for (CollisionObject * obj : collision_objects[i.x][i.y]) {

								VectorFloat position_after = moving_object->getPosition();

								std::vector<CollisionObject*>::iterator it = find(collided_objects.begin(), collided_objects.end(), obj);
								if (obj != collision_object && it == collided_objects.end() && collision_object->isCollision(obj)) {
									collided_objects.push_back(obj);

									if (obj->isTrigger()) {
										obj->onTrigger(collision_object);
									}
									else {

										collision_object->changePosition(position_before.x, position_after.y);

										if (collision_object->isCollision(obj)) {
											collision_object->changePosition(position_after.x, position_before.y);
											if (collision_object->isCollision(obj)) {
												collision_object->changePosition(position_before.x, position_before.y);
												if (collision_object->isCollision(obj)) {
													//still collsion
													VectorFloat dir = collision_object->getPosition() - obj->getPosition();
													dir = collision_object->getPosition() + (dir * Time::getElapsedTime());
													collision_object->changePosition(dir.x, dir.y);
												}
											}
										}
									}
								}
							}
						}
					}
					collision_object->onCollision(collided_objects);
				}
			}
		}
	
		(*iterator_objects)->update_animation();

		sf::Sprite & sprite = (*iterator_objects)->getSprite();

		window.draw(sprite);

		iterator_objects++;

	}

	SCamera::instance()->setTargetGUI(window);
	VectorFloat mouse_position = SInputManager::instance()->getMousePosition();

	if (SInputManager::instance()->getMouseLeft()) {
		for (gui_elements_list::iterator i = gui_elements.begin(); i != gui_elements.end(); i++) {

			if ((*i)->active) {
				(*i)->update();
				if (Clickable* clickable = dynamic_cast<Clickable*>((*i).get())) {
					if(clickable->isMouseInButton(mouse_position) && clickable->is_clickable){
						clickable->setHover(true);
						clickable->click();
					}else {
						clickable->setHover(false);
					}
				}
				window.draw((*i)->getRectangleShape());
			}
		}
	}else {

		for (gui_elements_list::iterator i = gui_elements.begin(); i != gui_elements.end(); i++) {

			if ((*i)->active) {
				(*i)->update();
				if (Clickable* clickable = dynamic_cast<Clickable*>((*i).get())) {
					if (clickable->isMouseInButton(mouse_position) && clickable->is_clickable) {
						clickable->setHover(true);
					}
					else {
						clickable->setHover(false);
					}
				}
				window.draw((*i)->getRectangleShape());
			}
		}
	}

}
