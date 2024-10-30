#ifndef  Map_hpp
#define  Map_hpp

class Chunk {
public:
	sf::Vector2i coords;
    Terrain* terrain;
    Water* water;

    sf::RectangleShape borders;
    sf::Text coordsText;

    std::vector < Nature* > _natures;
    std::vector < ItemOnMap* > _items;
    std::vector < InventoryOnMap* > _inventories;
    std::vector < Path* > _paths;
    std::vector < Monster* > _monsters;
    std::vector < Character* > _characters;
    std::vector < Building* > _buildings;

    bool visible;

    Chunk(short x, short y) {
        coords.x = x;
        coords.y = y;

        terrain = new Terrain(x * 16, y * 16, 16, 16);
        water = new Water(x * 16, y * 16, 16, 16);

        short borderWidth = 2;
        borders = sf::RectangleShape(sf::Vector2f(256 - 2 * borderWidth, 256 - 2 * borderWidth));
        borders.setPosition(x * 256, y * 256);
        borders.setFillColor(sf::Color::Transparent);
        borders.setOutlineColor(sf::Color(128, 48, 48, 128));
        borders.setOutlineThickness(borderWidth);

        coordsText = sf::Text();
        coordsText.setFont(basicFont);
        coordsText.setCharacterSize(16);
        coordsText.setString(to_string(coords.x) + " x " + to_string(coords.y));
        coordsText.setFillColor(textColor);
        coordsText.setPosition(coords.x * 256, coords.y * 256);

        visible = false;

    }

    ~Chunk() {
        // Usuń i zwolnij pamięć dla wszystkich elementów w wektorach
        for (auto& nature : _natures) 
            delete nature;
        _natures.clear();

        for (auto& item : _items) 
            delete item;
        _items.clear();

        for (auto& inventory : _inventories) 
            delete inventory;
        _inventories.clear();

        for (auto& path : _paths) 
            delete path;
        _paths.clear();

        for (auto& monster : _monsters) 
            delete monster;
        _monsters.clear();

        for (auto& character : _characters) 
            delete character;
        _characters.clear();
        
        for (auto& building : _buildings)
            delete building;
        _buildings.clear();

        delete terrain;
        delete water;
    }

    void addGameObjectsToMainLists() {
        // Add all GameObjects of Chunk to Main Lists

        for (auto& nature : _natures) {
            gameObjects.push_back(nature);
            natures.push_back(nature);
        }
        
        for (auto& item : _items) {
            gameObjects.push_back(item);
            itemsOnMap.push_back(item);
        }

        for (auto& inventory : _inventories) {
            gameObjects.push_back(inventory);
            inventoriesOnMap.push_back(inventory);
        }

        for (auto& path : _paths) {
            gameObjects.push_back(path);
            paths.push_back(path);
        }

        for (auto& monster : _monsters) {
            gameObjects.push_back(monster);
            monsters.push_back(monster);
        }

        for (auto& character : _characters) {
            gameObjects.push_back(character);
            characters.push_back(character);
        }

        for (auto& building : _buildings) {

            gameObjects.push_back(building);
            buildings.push_back(building);

            doors.push_back(building->_door);
            gameObjects.push_back(building->_door);

            for (auto& item : building->_items) {
                itemsOnMap.push_back(item);
                gameObjects.push_back(item);
            }
                

            for (auto& furniture : building->_furnitures) {
                furnitures.push_back(furniture);
                gameObjects.push_back(furniture);
            }
                

            for (auto& wall : building->_walls) {
                walls.push_back(wall);
                gameObjects.push_back(wall);
            }
                
        }

    }

    void removeGameObjectsFromMainLists() {
        // delete natures
        for (auto& nature : _natures) {
            auto it = std::find(natures.begin(), natures.end(), nature);
            if (it != natures.end())
                natures.erase(it);

            auto go = std::find(gameObjects.begin(), gameObjects.end(), nature);
            if (go != gameObjects.end())
                gameObjects.erase(go);
        }

        // delete items
        for (auto& item : _items) {
            auto it = std::find(itemsOnMap.begin(), itemsOnMap.end(), item);
            if (it != itemsOnMap.end())
                itemsOnMap.erase(it);

            auto go = std::find(gameObjects.begin(), gameObjects.end(), item);
            if (go != gameObjects.end())
                gameObjects.erase(go);
        }

        // delete inventories
        for (auto& inventory : _inventories) {
            auto it = std::find(inventoriesOnMap.begin(), inventoriesOnMap.end(), inventory);
            if (it != inventoriesOnMap.end())
                inventoriesOnMap.erase(it);

            auto go = std::find(gameObjects.begin(), gameObjects.end(), inventory);
            if (go != gameObjects.end())
                gameObjects.erase(go);
        }

        // delete paths
        for (auto& path : _paths) {
            auto it = std::find(paths.begin(), paths.end(), path);
            if (it != paths.end())
                paths.erase(it);

            auto go = std::find(gameObjects.begin(), gameObjects.end(), path);
            if (go != gameObjects.end())
                gameObjects.erase(go);
        }

        // delete monsters
        for (auto& monster : _monsters) {
            auto it = std::find(monsters.begin(), monsters.end(), monster);
            if (it != monsters.end())
                monsters.erase(it);

            auto go = std::find(gameObjects.begin(), gameObjects.end(), monster);
            if (go != gameObjects.end())
                gameObjects.erase(go);
        }

        // delete characters
        for (auto& character : _characters) {
            auto it = std::find(characters.begin(), characters.end(), character);
            if (it != characters.end())
                characters.erase(it);

            auto go = std::find(gameObjects.begin(), gameObjects.end(), character);
            if (go != gameObjects.end())
                gameObjects.erase(go);
        }

        // delete buildings
        for (auto& building : _buildings) {

            auto it = std::find(buildings.begin(), buildings.end(), building);
            if (it != buildings.end())
                buildings.erase(it);

            auto go = std::find(gameObjects.begin(), gameObjects.end(), building);
            if (go != gameObjects.end())
                gameObjects.erase(go);

            // delete door
            auto itd = std::find(doors.begin(), doors.end(), building->_door);
            if (itd != doors.end())
                doors.erase(itd);

            auto god = std::find(gameObjects.begin(), gameObjects.end(), building->_door);
            if (god != gameObjects.end())
                gameObjects.erase(god);

            // delete building _items
            for (auto& item : building->_items) {
                auto it = std::find(itemsOnMap.begin(), itemsOnMap.end(), item);
                if (it != itemsOnMap.end())
                    itemsOnMap.erase(it);

                auto go = std::find(gameObjects.begin(), gameObjects.end(), item);
                if (go != gameObjects.end())
                    gameObjects.erase(go);
            }

            // delete building _furnitures
            for (auto& furniture : building->_furnitures) {
                auto it = std::find(furnitures.begin(), furnitures.end(), furniture);
                if (it != furnitures.end())
                    furnitures.erase(it);

                auto go = std::find(gameObjects.begin(), gameObjects.end(), furniture);
                if (go != gameObjects.end())
                    gameObjects.erase(go);
            }

            // delete building _walls
            for (auto& wall : building->_walls) {
                auto it = std::find(walls.begin(), walls.end(), wall);
                if (it != walls.end())
                    walls.erase(it);

                auto go = std::find(gameObjects.begin(), gameObjects.end(), wall);
                if (go != gameObjects.end())
                    gameObjects.erase(go);
            }

        }
    }

    void removeGameObject(GameObject* object) {

        if (object == nullptr)
            return;

        if (object->type == GameObjectType::Nature) {
            auto it = std::find(_natures.begin(), _natures.end(), object);
            if (it != _natures.end())
                _natures.erase(it);
        }

        if (object->type == GameObjectType::ItemOnMap) {
            auto it = std::find(_items.begin(), _items.end(), object);
            if (it != _items.end())
                _items.erase(it);
        }

        if (object->type == GameObjectType::InventoryOnMap) {
            auto it = std::find(_inventories.begin(), _inventories.end(), object);
            if (it != _inventories.end())
                _inventories.erase(it);
        }

        if (object->type == GameObjectType::Path) {
            auto it = std::find(_paths.begin(), _paths.end(), object);
            if (it != _paths.end())
                _paths.erase(it);
        }

        if (object->type == GameObjectType::Monster) {
            auto it = std::find(_monsters.begin(), _monsters.end(), object);
            if (it != _monsters.end())
                _monsters.erase(it);
        }

        if (object->type == GameObjectType::Character) {
            auto it = std::find(_characters.begin(), _characters.end(), object);
            if (it != _characters.end()) {
                cout << "delete character\n";
                _characters.erase(it);
            }
                
        }

        if (object->type == GameObjectType::Building) {
            auto it = std::find(_buildings.begin(), _buildings.end(), object);
            if (it != _buildings.end())
                _buildings.erase(it);
        }

    }

	void update() {

	}

	void draw() {
        window->draw(*terrain);
        water->update();    // TO-DO
        window->draw(*water);
    }

    void drawAllStatistics() {
        if (renderBorders)
            window->draw(borders);

        if (renderCoords)
            window->draw(coordsText);
    }

};

class Mapa {
public:
	std::vector < Chunk* > chunks;
    short width;
    short height;
    Mapa() {
        chunks.clear();
        
        width = 4;
        height = 4;

        for (short y = 0; y < height; y++) {
            for (short x = 0; x < width; x++) {
                Chunk* ch = new Chunk(x, y);
                chunks.push_back(ch);
            }
        }
    }

    Chunk* getChunk(short x, short y) {
        for (auto& chunk : chunks) {
            if (short(chunk->coords.x) == x && short(chunk->coords.y) == y)
                return chunk;
        }

        return nullptr;
    }

    Chunk* getChunk(sf::Vector2f position) {

        float left, right, top, bottom;

        for (auto& chunk : chunks) {

            left = chunk->coords.x * 16 * tileSide;
            right = left + chunk->terrain->width * tileSide;
            top = chunk->coords.y * 16 * tileSide;
            bottom = top + chunk->terrain->height * tileSide;

            if (position.x >= left && position.x < right && position.y >= top && position.y < bottom)
            {
                //cout << m->coords.x << ", " << m->coords.y << "\n";
                return chunk;

            }
        }

        return nullptr;
    }

    void save(string filename = "world/world.map") {
        ofstream file(filename);

        for (auto& chunk : chunks) {
            file << "Chunk ";

            file << "y=" << chunk->coords.y << " ";
            file << "x=" << chunk->coords.x << "\n";

            for (short y = 0; y < 16; y++) {
                for (short x = 0; x < 16; x++) {

                    file << chunk->terrain->tiles[y * 16 + x];
                    
                    if (x != 15)
                        file << " ";
                }

                file << "\n";
            }

            for (auto& nature : chunk->_natures)
                file << "Nature \"" << nature->name << "\" y=" << int(nature->position.y) << " x=" << int(nature->position.x) << "\n";

            for (auto& item : chunk->_items)
                file << "Item \"" << item->name << "\" y=" << int(item->position.y) << " x=" << int(item->position.x) << "\n";

            for (auto& inventory : chunk->_inventories)
                file << "Inventory \"" << inventory->name << "\" y=" << int(inventory->position.y) << " x=" << int(inventory->position.x) << "\n";

            for (auto& path : chunk->_paths)
                file << "Path \"" << path->name << "\" y=" << int(path->position.y) << " x=" << int(path->position.x) << "\n";

            for (auto& monster : chunk->_monsters)
                file << "Monster \"" << monster->name << "\" y=" << int(monster->position.y) << " x=" << int(monster->position.x) << "\n";

            for (auto& character : chunk->_characters)
                file << "Character \"" << character->name << "\" y=" << int(character->position.y) << " x=" << int(character->position.x) << "\n";

            for (auto& building : chunk->_buildings)
                file << "Building \"" << building->name << "\" y=" << int(building->position.y) << " x=" << int(building->position.x) << "\n";

            file << "\n";
        }

        file.close();
    }

    void load(string filename = "world\\world.map") {

        // clearing chunks
        for (auto& chunk : chunks) {
            delete chunk;
        }

        chunks.clear();

        gameObjects.clear();
        natures.clear();
        itemsOnMap.clear();
        inventoriesOnMap.clear();
        paths.clear();
        monsters.clear();
        furnitures.clear();
        walls.clear();
        characters.clear();
        buildings.clear();
        
        // create chunks
        short width = 16;
        short height = 16;
        
        for (short y = 0; y < height; y++) {
            for (short x = 0; x < width; x++) {
                Chunk* ch = new Chunk(x, y);
                chunks.push_back(ch);
            }
        }
        
        // open file map
        ifstream file(filename);

        if (!file.is_open()) {
            cout << "cant open map: " << filename << "\n";
            return;
        }

        cout << "open map: " << filename << "\n";

        string line;
        string objectType;
        Chunk* chunk = nullptr;

        // loading
        while (std::getline(file, line)) {

            if (line.empty()) {
                //cout << "empty line\n";
                continue;
            }

            std::istringstream lineStream(line);
            lineStream >> objectType;

            if (objectType == "Chunk") {

                // load Chunk
                std::regex chunk_regex(R"(Chunk y=([0-9]+) x=([0-9]+))");
                std::smatch chunk_match;

                if (std::regex_search(line, chunk_match, chunk_regex)) {
                    int chunk_y = std::stoi(chunk_match[1]);
                    int chunk_x = std::stoi(chunk_match[2]);
                    
                    // get chunk
                    chunk = getChunk(chunk_x, chunk_y);

                    if (chunk == nullptr) {
                        chunk = new Chunk(chunk_x, chunk_y);
                        chunks.push_back(chunk);
                    }

                    // check the correct of datas
                    std::streampos pos = file.tellg(); // Zapisanie pozycji linii
                    bool correct_data = true;
                    string _line;
                    int y = 0;
                    int x;

                    while (std::getline(file, _line) && _line[0]>='0' && _line[0]<='9') {

                        std::istringstream iss(_line);
                        int val;
                        x = 0;

                        while (iss >> val)
                            x += 1;

                        if (x != 16) {
                            //cout << x << "\n";
                            correct_data = false;
                        }

                        y += 1;
                    };

                    if (y != 16) {
                        //cout << y << "\n";
                        correct_data = false;
                    }

                    // predefine tiles
                    std::vector < int > tiles(256, 0);

                    if (correct_data == true) {
                        file.seekg(pos); // wczytanie pozycji linii

                        // load tiles
                        int y = 0;
                        while (y < 16 && std::getline(file, line)) {
 
                            std::istringstream tileStream(line);
                            int value;
                            int x = 0;

                            while (tileStream >> value) {
                                tiles[y * 16 + x] = value;
                                x += 1;
                            }

                            y += 1;
                        }

                        // set the tiles
                        for (int i = 0; i < tiles.size(); i++) {
                            chunk->terrain->edit(i % 16, i / 16, tiles[i]);
                            
                            // TO-DO
                            /*
                            if (tiles[i] == 2) {
                                chunk->water->edit(i % 16, i / 16, true);
                            }
                            */
                                
                        }
                            
                           
                    }

                    
                }

            } else {
                
                short x, y;
                string temp;
                string objectName;

                getline(lineStream, temp, '"');         // get string to temp to sign "
                getline(lineStream, objectName, '"');   // get string to objectName to sign "
                getline(lineStream, temp, '=');         // get string to temp to sign =
                lineStream >> y;                        // string to y
                getline(lineStream, temp, '=');         // get string to temp to sign =
                lineStream >> x;                        // string to x
                //cout << objectType << " \"" << objectName << "\" " << x << " " << y << "\n";

                chunk = getChunk(sf::Vector2f(x,y));
                if (chunk == nullptr) {
                    chunk = new Chunk(x/256, y/256);
                    chunks.push_back(chunk);
                }

                if (objectType == "Nature") {
                    Nature* nature = new Nature(getPrefab(objectName), x, y);
                    chunk->_natures.push_back(nature);
                }

                if (objectType == "Item") {
                    ItemOnMap* itemOnMap = new ItemOnMap(getItem(objectName), x, y);
                    chunk->_items.push_back(itemOnMap);
                }
                
                if (objectType == "Inventory") {
                    // TO-DO - get Inventory(id)
                    InventoryOnMap* inventory = new InventoryOnMap(getInventory(0), x, y);
                    chunk->_inventories.push_back(inventory);
                }

                if (objectType == "Path") {
                    Path* path = new Path(getPrefab(objectName), x, y);
                    chunk->_paths.push_back(path);
                }

                if (objectType == "Monster") {
                    Monster* monster = new Monster(getPrefab(objectName), x, y);
                    chunk->_monsters.push_back(monster);
                }

                if (objectType == "Character") {
                    // To-DO - get Character
                    Character* character = new Character(getPrefab(objectName), x, y);
                    chunk->_characters.push_back(character);
                }

                if (objectType == "Building") {
                    Building* building = new Building(objectName, x, y);
                    chunk->_buildings.push_back(building);
                }
                
            }

            
        }

        file.close();

        mapVisiblings();

        generateBorders();

    }

    bool intersectionTwoRectangles(float x1, float y1, float width1, float height1, float x2, float y2, float width2, float height2) {

        if (abs(x1 - x2) < (width1 + width2) / 2.0f && abs(y1 - y2) < (height1 + height2) / 2.0f)
            return true;

        return false;

    }

    void mapVisiblings() {

        for (auto& chunk : chunks) {

            sf::Vector2f chunk_position;
            chunk_position.x = (chunk->terrain->coords.x * tileSide) + 8 * tileSide;
            chunk_position.y = (chunk->terrain->coords.y * tileSide) + 8 * tileSide;

            // TO-DO
            //float width = screenWidth * 2.0f;
            //float height = screenHeight * 2.0f;

            float width = screenWidth * 4.0f;
            float height = screenHeight * 4.0f;

            bool prevVisible = chunk->visible;

            chunk->visible = intersectionTwoRectangles(cam->position.x, cam->position.y, width, height, chunk_position.x, chunk_position.y, 16 * tileSide, 16 * tileSide);

            if (prevVisible == false && chunk->visible == true) {
                chunk->addGameObjectsToMainLists();
            }
            else if (prevVisible == true && chunk->visible == false) {
                chunk->removeGameObjectsFromMainLists();
            }

        }

    }

    void generateBorders() {
        Chunk* topChunk;
        Chunk* bottomChunk;
        Chunk* leftChunk;
        Chunk* rightChunk;

        Terrain* topTerrain;
        Terrain* bottomTerrain;
        Terrain* leftTerrain;
        Terrain* rightTerrain;

        int y, x;

        for (int i = 0; i < chunks.size(); i++) {

            y = i / width;
            x = i % width;

            topChunk = getChunk(x, y - 1);
            bottomChunk = getChunk(x, y + 1);
            leftChunk = getChunk(x - 1, y);
            rightChunk = getChunk(x + 1, y);
            
            (topChunk != nullptr) ? topTerrain = topChunk->terrain : topTerrain = nullptr;
            (bottomChunk != nullptr) ? bottomTerrain = bottomChunk->terrain : bottomTerrain = nullptr;
            (leftChunk != nullptr) ? leftTerrain = leftChunk->terrain : leftTerrain = nullptr;
            (rightChunk != nullptr) ? rightTerrain = rightChunk->terrain : rightTerrain = nullptr;

            chunks[i]->terrain->generateBorders(topTerrain, bottomTerrain, leftTerrain, rightTerrain);
        }
    }

	void update() {

	}

	void draw() {
        for (auto& chunk : chunks) {
            chunk->draw();
        }
            
	}

    void drawStatistics() {
        for (auto& chunk : chunks) {
            chunk->drawAllStatistics();
        }
    }

};

Mapa* mapa = nullptr;

#endif // ! Map_hpp
