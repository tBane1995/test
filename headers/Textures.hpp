#ifndef Textures_hpp
#define Textures_hpp

using namespace std;

class Texture {
public:
	string name;
	sf::Texture* texture;
	float cx, cy;	// coordinates of center on the texture

	Texture(string pathfile, float cx, float cy) {
		
		name = "";

		short i = int(pathfile.size()) - 5;
		while ( i>=0)
			name = pathfile[i--] + name;

		this->cx = cx;
		this->cy = cy;

		texture = new sf::Texture;
		texture->loadFromFile("assets/" + pathfile);

		//cout << "load texture: " << pathfile << " as: " << name << endl;
	}

	Texture(string name, sf::Image image) {
		this->name = name;

		texture = new sf::Texture;
		texture->loadFromImage(image);

		cx = texture->getSize().x / 2;
		cy = texture->getSize().y / 2;
		
		//cout << "load texture from set as: " << name << endl;
	}

};

std::vector < Texture* > textures;

void loadTexture(string pathfile, float cx, float cy) {
	textures.push_back( new Texture(pathfile, cx, cy) );
}

bool areImagesEqual(sf::Image& img1, sf::Image& img2) {
	if (img1.getSize() != img2.getSize()) {
		return false; // Rozmiary są różne
	}

	// Porównaj każdy piksel
	for (unsigned int y = 0; y < img1.getSize().y; y++) {
		for (unsigned int x = 0; x < img1.getSize().x; x++) {
			if (img1.getPixel(x, y) != img2.getPixel(x, y)) {
				return false; // Piksele są różne
			}
		}
	}
	return true; // Wszystkie piksele są identyczne
}

void loadTextureSets(string pathfile, int tile_width, int tile_height) {


	sf::Image image;
	image.loadFromFile("assets/" + pathfile + ".png");

	short image_width = image.getSize().x;
	short image_height = image.getSize().y;

	//cout << image_width << "x" << image_height << "\n";

	int counter = 0;

	for (short y = 0; y < image_height; y += tile_height)
		for (short x = 0; x < image_width; x += tile_width) {

			// create tile - fragment of texture
			sf::Image tile;
			tile.create(tile_width, tile_height);
			tile.copy(image, 0, 0, sf::IntRect(x, y, tile_width, tile_height));

			// searching - exist doubles or no
			bool existed = false;
			
			for (short i = 0; i < textures.size(); i++) {

				sf::Image img = textures[i]->texture->copyToImage();
				
				if (areImagesEqual(tile, img)) {
					existed = true;
					//cout << "exits now\n";
					break;
				}
			}

			// if no exist then add
			if (existed == false) {
				Texture* new_texture = new Texture(pathfile + "_" + to_string(counter), tile);
				//cout << "created texture: " << pathfile + "_" + to_string(counter) << "\n";
				//cout << "create a texture\n";
				textures.push_back(new_texture);

				counter += 1;

			}

		}

}

void loadTextures() {

	textures.clear();

	// NOISE //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	loadTexture("noise.png", 256, 256);
	loadTexture("noise2.png", 256, 256);
	loadTexture("empty.png", 256, 256);

 	// GUI ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	loadTexture("GUI/slot1.png", 40, 40);
	loadTexture("GUI/slot2.png", 32, 32);
	loadTexture("GUI/selector.png", 40, 40);

	loadTexture("GUI/infoPanel.png", 300, 75);
	loadTexture("GUI/bigPanel.png", 300, 200);

	loadTexture("GUI/wideArrowUp1.png", 80, 20);
	loadTexture("GUI/wideArrowUp2.png", 80, 20);
	loadTexture("GUI/wideArrowDown1.png", 160, 18.5f);
	loadTexture("GUI/wideArrowDown2.png", 160, 18.5f);

	// menu buttons textures
	loadTexture("GUI/menuButtons/menuButton.png", 32, 26);
	loadTexture("GUI/menuButtons/menuButton-terrain.png", 32, 26);
	loadTexture("GUI/menuButtons/menuButton-floors.png", 32, 26);
	loadTexture("GUI/menuButtons/menuButton-furnitures.png", 32, 26);
	loadTexture("GUI/menuButtons/menuButton-walls.png", 32, 26);
	loadTexture("GUI/menuButtons/menuButton-monsters.png", 32, 26);
	loadTexture("GUI/menuButtons/menuButton-paths.png", 32, 26);
	loadTexture("GUI/menuButtons/menuButton-items.png", 32, 26);
	loadTexture("GUI/menuButtons/menuButton-natures.png", 32, 26);

	// small buttons textures
	loadTexture("GUI/smallButtons/smallbutton.png", 20, 20);
	loadTexture("GUI/smallButtons/smallbutton-ArrowUp.png", 20, 20);
	loadTexture("GUI/smallButtons/smallbutton-ArrowDown.png", 20, 20);
	loadTexture("GUI/smallButtons/smallbutton-ArrowLeft.png", 20, 20);
	loadTexture("GUI/smallButtons/smallbutton-ArrowRight.png", 20, 20);

	// tool butttons textures
	loadTexture("GUI/toolButtons/toolbutton.png", 20, 16);
	loadTexture("GUI/toolButtons/toolbutton-cursor.png", 20, 16);
	loadTexture("GUI/toolButtons/toolbutton-brush.png", 20, 16);
	loadTexture("GUI/toolButtons/toolbutton-rect_brush.png", 20, 16);
	loadTexture("GUI/toolButtons/toolbutton-increase.png", 20, 16);
	loadTexture("GUI/toolButtons/toolbutton-decrease.png", 20, 16);
	loadTexture("GUI/toolButtons/toolbutton-rectangle.png", 20, 16);
	loadTexture("GUI/toolButtons/toolbutton-elipse.png", 20, 16);
	loadTexture("GUI/toolButtons/toolbutton-fill.png", 20, 16);
	loadTexture("GUI/toolButtons/toolbutton-eraser.png", 20, 16);

	loadTexture("GUI/spacebutton.png", 80, 20);

	loadTexture("GUI/scrollbar/button_bottom.png", 8, 8);
	loadTexture("GUI/scrollbar/button_top.png", 8, 8);
	loadTexture("GUI/scrollbar/bar_bottom.png", 8, 8);
	loadTexture("GUI/scrollbar/bar_top.png", 8, 8);
	loadTexture("GUI/scrollbar/bar_center.png", 8, 8);
	loadTexture("GUI/scrollbar/scroll_bottom.png", 8, 8);
	loadTexture("GUI/scrollbar/scroll_top.png", 8, 8);
	loadTexture("GUI/scrollbar/scroll_center.png", 8, 8);

	loadTexture("GUI/checkbox/check.png", 8, 8);

	loadTexture("GUI/hand.png", 8, 8);
	loadTexture("GUI/grey_hand.png", 8, 8);
	loadTexture("GUI/talk.png", 8, 8);

	loadTexture("GUI/icons/MapEditor_small_ico.png", 15, 15);
	loadTexture("GUI/icons/dictionary.png", 15, 15);
	loadTexture("GUI/icons/file.png", 15, 15);

	// TILES //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	loadTexture("tiles/0_tileset.png", 0, 0);
	loadTexture("tiles/tile_0_grass.png", 32, 32);
	loadTexture("tiles/tile_1_sands.png", 32, 32);
	loadTexture("tiles/tile_2_water.png", 32, 32);
	loadTexture("tiles/tile_3_gravel.png", 32, 32);
	loadTexture("tiles/tile_4_beach.png", 32, 32);

	// FLOORS
	loadTexture("floors/0_floorset.png", 0, 0);
	loadTexture("floors/floor_0.png", 32, 32);
	loadTexture("floors/floor_1.png", 32, 32);
	loadTexture("floors/floor_2.png", 32, 32);
	loadTexture("floors/floor_3.png", 32, 32);

	// NATURES ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	loadTexture("natures/tree1.png", 126, 185);
	loadTexture("natures/tree2.png", 113, 220);
	loadTexture("natures/tree3.png", 126, 185);
	loadTexture("natures/tree4.png", 113, 220);
	loadTexture("natures/tree5.png", 126, 185);
	loadTexture("natures/tree6.png", 128, 203);
	loadTexture("natures/tree7.png", 125, 180);
	loadTexture("natures/tree8.png", 128, 203);
	loadTexture("natures/tree9.png", 129, 213);
	loadTexture("natures/bush1.png", 140, 150);
	loadTexture("natures/rocks1.png", 130, 170);
	loadTexture("natures/rocks2.png", 130, 190);
	loadTexture("natures/rocks3.png", 130, 160);

	// BUILDINGS ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	loadTexture("buildings/demo house.png", 128, 256); // 128, 384 - 8*16

	// ITEMS ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	loadTexture("items/bag.png", 28, 48);

	// WEAPONS
	loadTexture("items/club.png", 32, 32);
	loadTexture("items/knife.png", 32, 32);
	loadTexture("items/hatchet.png", 32, 32);
	loadTexture("items/sword.png", 32, 32);
	loadTexture("items/dagger.png", 32, 32);
	loadTexture("items/wooden club.png", 32, 32);
	loadTexture("items/long sword.png", 32, 32);
	loadTexture("items/curved sword.png", 32, 32);
	loadTexture("items/wide blade.png", 32, 32);
	loadTexture("items/gladius.png", 32, 32);
	loadTexture("items/iron club.png", 32, 32);
	loadTexture("items/axe.png", 32, 32);
	loadTexture("items/stone hammer.png", 32, 32);

	// HELMET
	loadTexture("items/skin helmet.png", 32, 32);
	loadTexture("items/wool hat.png", 32, 32);

	// ARMORS
	loadTexture("items/plate armor.png", 32, 32);
	loadTexture("items/chain mail.png", 32, 32);
	loadTexture("items/skin jacket.png", 32, 32);
	loadTexture("items/torn shirt.png", 32, 32);
	loadTexture("items/wool shirt.png", 32, 32);

	// PANTS
	loadTexture("items/chain mail pants.png", 32, 32);
	loadTexture("items/skin pants.png", 32, 32);
	loadTexture("items/wool pants.png", 32, 32);

	// SHIELDS
	loadTexture("items/shield.png", 32, 32);	// TO-DO to delete

	// HERBS
	loadTexture("items/mana plant.png", 30, 50);
	loadTexture("items/health herb.png", 32, 34);
	loadTexture("items/health root.png", 31, 46);	
	loadTexture("items/health plant.png", 30, 44);
	loadTexture("items/mushroom.png", 30, 44);

	// POTIONS
	loadTexture("items/potion.png", 32, 32);

	// FOOD
	loadTexture("items/raw meat.png", 32, 32);
	loadTexture("items/roasted meat.png", 32, 32);

	// OTHERS
	loadTexture("items/bone.png", 32, 32);
	loadTexture("items/bone.png", 40, 40);
	loadTexture("items/tooth.png", 32, 32);
	loadTexture("items/spike.png", 32, 32);
	loadTexture("items/wolf skin.png", 32, 32);

	// PATHS ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	loadTexture("paths/stonepath1.png", 32, 32);
	loadTexture("paths/stonepath2.png", 32, 32);

	// DOORS ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	loadTexture("doors/door_close.png", 32, 32);
	loadTexture("doors/door_open.png", 32, 32);

	// MONSTERS
	std::vector < string > monsters;

	monsters.push_back("dziobak");
	monsters.push_back("goblin");
	monsters.push_back("wilczur");
	monsters.push_back("jaszczur");
	monsters.push_back("niedzwiedz");
	monsters.push_back("szpon");
	monsters.push_back("kolcorozec");
	monsters.push_back("golem");
	monsters.push_back("troll");
	monsters.push_back("bies");

	for (auto& m : monsters) {
		for (short i = 0; i < 4; i++) {

			loadTexture("monsters/" + m + ".png", 63, 87);

			loadTexture("monsters/" + m + "/idleTop" + to_string(i) + ".png", 63, 87);
			loadTexture("monsters/" + m + "/idleRight" + to_string(i) + ".png", 63, 87);
			loadTexture("monsters/" + m + "/idleBottom" + to_string(i) + ".png", 63, 87);
			loadTexture("monsters/" + m + "/idleLeft" + to_string(i) + ".png", 63, 87);

			loadTexture("monsters/" + m + "/attackTop" + to_string(i) + ".png", 63, 87);
			loadTexture("monsters/" + m + "/attackRight" + to_string(i) + ".png", 63, 87);
			loadTexture("monsters/" + m + "/attackBottom" + to_string(i) + ".png", 63, 87);
			loadTexture("monsters/" + m + "/attackLeft" + to_string(i) + ".png", 63, 87);

			loadTexture("monsters/" + m + "/runTop" + to_string(i) + ".png", 63, 87);
			loadTexture("monsters/" + m + "/runRight" + to_string(i) + ".png", 63, 87);
			loadTexture("monsters/" + m + "/runBottom" + to_string(i) + ".png", 63, 87);
			loadTexture("monsters/" + m + "/runLeft" + to_string(i) + ".png", 63, 87);

		}
	}
	
	// FURNITURES
	loadTexture("furnitures/table.png", 32, 32);
	loadTexture("furnitures/bench.png", 32, 32);
	loadTexture("furnitures/chest.png", 32, 32);
	loadTexture("furnitures/wardrobe.png", 32, 50);
	loadTexture("furnitures/bookshelf.png", 32, 50);
	loadTexture("furnitures/furnace.png", 32, 50);
	loadTexture("furnitures/bed.png", 32, 50);
	loadTexture("furnitures/chair.png", 34, 38);
	loadTexture("furnitures/barrel.png", 34, 38);
	loadTexture("furnitures/lectern.png", 34, 38);


	// WALLS
	loadTexture("walls/empty_wall.png", 16, 16);

	loadTextureSets("walls/mud_wall", 32, 32);
	loadTextureSets("walls/stone_wall", 32, 32);
	loadTextureSets("walls/wooden_wall", 32, 32);

	loadTexture("walls/wooden_wall_bottom.png", 16, 16);
	loadTexture("walls/wooden_wall_top_0.png", 16, 16);
	loadTexture("walls/wooden_wall_top_1.png", 16, 16);
	loadTexture("walls/wooden_wall_top_2.png", 16, 16);
	loadTexture("walls/wooden_wall_top_3.png", 16, 16);
	loadTexture("walls/wooden_wall_top_4.png", 16, 16);
	loadTexture("walls/wooden_wall_top_5.png", 16, 16);
	loadTexture("walls/wooden_wall_top_6.png", 16, 16);
	loadTexture("walls/wooden_wall_top_7.png", 16, 16);
	loadTexture("walls/wooden_wall_top_8.png", 16, 16);
	loadTexture("walls/wooden_wall_top_9.png", 16, 16);

	loadTexture("walls/stone_wall_bottom.png", 16, 16);
	loadTexture("walls/stone_wall_top_0.png", 16, 16);
	loadTexture("walls/stone_wall_top_1.png", 16, 16);
	loadTexture("walls/stone_wall_top_2.png", 16, 16);
	loadTexture("walls/stone_wall_top_3.png", 16, 16);
	loadTexture("walls/stone_wall_top_4.png", 16, 16);
	loadTexture("walls/stone_wall_top_5.png", 16, 16);
	loadTexture("walls/stone_wall_top_6.png", 16, 16);
	loadTexture("walls/stone_wall_top_7.png", 16, 16);
	loadTexture("walls/stone_wall_top_8.png", 16, 16);
	loadTexture("walls/stone_wall_top_9.png", 16, 16);

	loadTexture("walls/mud_wall_bottom.png", 16, 16);
	loadTexture("walls/mud_wall_top_0.png", 16, 16);
	loadTexture("walls/mud_wall_top_1.png", 16, 16);
	loadTexture("walls/mud_wall_top_2.png", 16, 16);
	loadTexture("walls/mud_wall_top_3.png", 16, 16);
	loadTexture("walls/mud_wall_top_4.png", 16, 16);
	loadTexture("walls/mud_wall_top_5.png", 16, 16);
	loadTexture("walls/mud_wall_top_6.png", 16, 16);
	loadTexture("walls/mud_wall_top_7.png", 16, 16);
	loadTexture("walls/mud_wall_top_8.png", 16, 16);
	loadTexture("walls/mud_wall_top_9.png", 16, 16);
	
	

	// BODY SETS
	std::vector < string > bodySets;
	bodySets.clear();
	bodySets.push_back("boy-redhaired");		// face without beard
	bodySets.push_back("boy-blackhaired");		// face without beard
	bodySets.push_back("boy-brownhaired");		// face without beard

	bodySets.push_back("man-redhaired");		// face have a beard
	bodySets.push_back("man-blackhaired");		// face have a beard
	bodySets.push_back("man-brownhaired");		// face have a beard

	bodySets.push_back("woman-redhaired");		// face with long hair
	bodySets.push_back("woman-blackhaired");	// face with long hair
	bodySets.push_back("woman-brownhaired");	// face with long hair
	
	
	for (auto& set : bodySets) {
		for (short i = 0; i < 4; i++) {

			loadTexture("sets/body/" + set + "/idleTop" + to_string(i) + ".png", 32, 58);
			loadTexture("sets/body/" + set + "/idleRight" + to_string(i) + ".png", 32, 58);
			loadTexture("sets/body/" + set + "/idleBottom" + to_string(i) + ".png", 32, 58);
			loadTexture("sets/body/" + set + "/idleLeft" + to_string(i) + ".png", 32, 58);

			loadTexture("sets/body/" + set + "/runTop" + to_string(i) + ".png", 32, 58);
			loadTexture("sets/body/" + set + "/runRight" + to_string(i) + ".png", 32, 58);
			loadTexture("sets/body/" + set + "/runBottom" + to_string(i) + ".png", 32, 58);
			loadTexture("sets/body/" + set + "/runLeft" + to_string(i) + ".png", 32, 58);

			loadTexture("sets/body/" + set + "/attackTop" + to_string(i) + ".png", 32, 58);
			loadTexture("sets/body/" + set + "/attackRight" + to_string(i) + ".png", 32, 58);
			loadTexture("sets/body/" + set + "/attackBottom" + to_string(i) + ".png", 32, 58);
			loadTexture("sets/body/" + set + "/attackLeft" + to_string(i) + ".png", 32, 58);

		}
	}
	

	// ITEMS SETS
	std::vector < string > itemSets;
	itemSets.clear();
	itemSets.push_back("skin jacket");
	itemSets.push_back("skin pants");
	itemSets.push_back("skin helmet");
	itemSets.push_back("torn shirt");
	itemSets.push_back("wool shirt");
	itemSets.push_back("wool hat");
	itemSets.push_back("wool pants");
	itemSets.push_back("wooden club");
	itemSets.push_back("axe");
	itemSets.push_back("club");
	itemSets.push_back("iron club");
	itemSets.push_back("stone hammer");
	itemSets.push_back("sword");
	itemSets.push_back("long sword");
	itemSets.push_back("gladius");
	itemSets.push_back("wide blade");
	itemSets.push_back("knife");
	itemSets.push_back("dagger");
	itemSets.push_back("hatchet");
	itemSets.push_back("curved sword");
	itemSets.push_back("chain mail");
	itemSets.push_back("chain mail pants");
	itemSets.push_back("plate armor");
	itemSets.push_back("shield");



	for (auto& set : itemSets) {

		for (short i = 0; i < 4; i++) {
			
			loadTexture("sets/items/" + set + "/idleTop" + to_string(i) + ".png", 32, 58);
			loadTexture("sets/items/" + set + "/idleRight" + to_string(i) + ".png", 32, 58);
			loadTexture("sets/items/" + set + "/idleBottom" + to_string(i) + ".png", 32, 58);
			loadTexture("sets/items/" + set + "/idleLeft" + to_string(i) + ".png", 32, 58);

			loadTexture("sets/items/" + set + "/runTop" + to_string(i) + ".png", 32, 58);
			loadTexture("sets/items/" + set + "/runRight" + to_string(i) + ".png", 32, 58);
			loadTexture("sets/items/" + set + "/runBottom" + to_string(i) + ".png", 32, 58);
			loadTexture("sets/items/" + set + "/runLeft" + to_string(i) + ".png", 32, 58);

			loadTexture("sets/items/" + set + "/attackTop" + to_string(i) + ".png", 32, 58);
			loadTexture("sets/items/" + set + "/attackRight" + to_string(i) + ".png", 32, 58);
			loadTexture("sets/items/" + set + "/attackBottom" + to_string(i) + ".png", 32, 58);
			loadTexture("sets/items/" + set + "/attackLeft" + to_string(i) + ".png", 32, 58);

		}
	}
}

Texture* getTexture(string name) {

	for (auto& t : textures) {
		if (t->name == name) {
			return t;
		}
	}

	std::cout << "error - get Texture - Texture: \"" << name << "\" not exists\n";
	return nullptr;
}

#endif