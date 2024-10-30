#ifndef BuildingsManager_hpp
#define BuildingsManager_hpp

void clearAllMainListsOfGameObjects();

class Building : public GameObject {
public:
	sf::Vector2i size;
	
    std::vector < ItemOnMap* > _items;      // from item Manager
	std::vector < Furniture* > _furnitures; // from furniture Manager
	std::vector < Wall* > _walls;           // from wall Manager
    
    Door* _door;
    Floors* floors;
    
    sf::Texture tex;
    sf::Sprite sprite;

    short x1, x2, y1, y2; // corners of building

    Building(int width, int height) : GameObject("empty",0,0) {
        
        type = GameObjectType::Building;
        size.x = width;
        size.y = height;

        position.x = size.x * 16/2;
        position.y = size.y * 16;
         
        floors = new Floors(position.x / 16 - size.x / 2, position.y / 16 - size.y, size.x, size.y);

        loadCollider();
    }

    // FOR BUILDING EDITOR
    Building(string name) : GameObject(name, 0, 0) {
        type = GameObjectType::Building;
        loadWithPositioning();

    }

    // NORMAL INIT FOR GAME/MAP EDITOR
	Building(string name, float x, float y) : GameObject(name, x, y) {

        type = GameObjectType::Building;
        load();
	}

    virtual ~Building() {
        delete _door;
        delete floors;

        for (auto& item : _items)
            delete item;

        for (auto& furniture : _furnitures)
            delete furniture;

        for (auto& wall : _walls)
            delete wall;
    }

    void calculateCorners() {
        x1 = position.x - size.x / 2 * 16;
        x2 = position.x + size.x / 2 * 16;
        y1 = position.y - size.y * 16;
        y2 = position.y;
    }

    virtual void mouseHovering() {

        if (worldMousePosition.x > x1 && worldMousePosition.x < x2 && worldMousePosition.y > y1 && worldMousePosition.y < y2)
            mouseIsHover = true;
        else
            mouseIsHover = false;
    }

    bool playerInside() {

        short x3, y3, rx3, ry3;
        x3 = player->position.x;
        y3 = player->position.y;
        rx3 = (player->collider->width / 2.0f);
        ry3 = (player->collider->length) / 2.0f;

        if (intersectionRectangleWithElipse((x1 + x2) / 2, (y1 + y2) / 2, x2 - x1, y2 - y1, x3, y3, rx3, ry3))
            return true;
        else
            return false;
    }

    void loadName(std::ifstream& file) {

        string line;

        std::getline(file, line);
    }

    void loadTexture(std::ifstream& file) {
        
        string line;

        std::getline(file, line);

        sprite = sf::Sprite();
        tex.loadFromFile("assets/buildings/demo house.png");
        sprite.setTexture(tex);
        sprite.setOrigin(tex.getSize().x / 2, tex.getSize().y);
        sprite.setPosition(position);

    }

    void loadSize(std::ifstream &file) {

        string line;
        string objectType;

        std::getline(file, line);
        std::istringstream lineStream(line);
        lineStream >> objectType;
        lineStream >> size.x >> size.y;

    }

    void loadCollider() {
        if (collider != nullptr)
            delete collider;

        collider = new Collider(size.x * 16, size.y * 16, size.y * 16, true);
        collider->shape->setPosition(position.x, position.y - size.y / 2 * 16);
    }

    void loadDoor(std::ifstream &file) {
        
        string line;

        std::getline(file, line);

        if (_door != nullptr)
            delete _door;

        _door = new Door(getPrefab("doors/door_0"), position.x, position.y);
    }

    void loadFloors(std::ifstream &file) {

        if (floors != nullptr)
            delete floors;

        floors = new Floors(position.x / 16 - size.x / 2, position.y / 16 - size.y, size.x, size.y);

        short value;
        for (short y = 0; y < size.y; y++) {
            for (short x = 0; x < size.x; x++) {
                file >> value;
                floors->edit(x, y, value);
            }
        }
    }

    void loadGameObjects(std::ifstream& file) {

        string line;
        string objectType;
        string objectName;

        while (std::getline(file, line)) {

            if (line.empty()) {
                continue;
            }

            std::istringstream lineStream(line);
            lineStream >> objectType;
            //cout << line << "\n";
            
            if (objectType == "Item") {

                short x, y;
                getline(lineStream, objectName, '"');
                getline(lineStream, objectName, '"');
                lineStream >> x;
                lineStream >> y;

                x = x - (size.x * 16 / 2) + position.x;
                y = y - (size.y * 16) + position.y;

                ItemOnMap* item = new ItemOnMap(getItem(objectName), x, y);
                _items.push_back(item);
            }

            if (objectType == "Furniture") {
                string name;
                short x, y, id;

                getline(lineStream, objectName, '"');
                getline(lineStream, objectName, '"');
                lineStream >> x;
                lineStream >> y;
                lineStream >> id;

                x = x - (size.x * 16 / 2) + position.x;
                y = y - (size.y * 16) + position.y;

                Furniture* furniture = new Furniture(getPrefab(objectName), x, y);
                furniture->inventory = getInventory(id);
                _furnitures.push_back(furniture);
            }

            if (objectType == "Wall") {
                string name;
                short x, y;

                getline(lineStream, objectName, '"');
                getline(lineStream, objectName, '"');
                lineStream >> x;
                lineStream >> y;

                x = x - (size.x * 16 / 2) + position.x;
                y = y - (size.y * 16) + position.y;

                Wall* wall = new Wall(getPrefab(objectName), x, y);
                _walls.push_back(wall);
            }

        }
    }

    void load() {
        string filename = name;
        ifstream file(filename);

        if (!file.is_open()) {
            cout << "cant open building script: " << filename << "\n";
            return;
        }

        loadName(file);
        loadTexture(file);
        loadSize(file);
        loadCollider();
        loadDoor(file);

        string line;

        std::getline(file, line);
        std::getline(file, line);

        loadFloors(file);
        loadGameObjects(file);

        file.close();
    }

    void loadWithPositioning() {
       
        string filename = name;
        ifstream file(filename);

        if (!file.is_open()) {
            cout << "cant open building script: " << filename << "\n";
            return;
        }

        loadName(file);
        loadTexture(file);
        loadSize(file);

        position.x = size.x * 16 / 2;
        position.y = size.y * 16;

        loadDoor(file);

        // COLLIDER
        loadCollider();

        string line;

        std::getline(file, line);
        std::getline(file, line);

        loadFloors(file);
        loadGameObjects(file);

        file.close();
    }

    void save(string filename) {
        std::ofstream file(filename);

        if (!file.is_open()) {
            cout << "cant open file to save building: " << filename << "\n";
            return;
        }

        file << "name \"testBuilding\"\n";
        file << "texture \"assets/buildings/testBuilding.png\"\n";
        file << "size " << to_string(floors->width) << " " << to_string(floors->height) << "\n";
        file << "door \"door_0\"\n";

        file << "\n";

        // SAVE FLOORS
        file << "// FLOORS\n";
        for (short y = 0; y < floors->height; y++) {
            for (short x = 0; x < floors->width; x++) {
                file << floors->floors[y * floors->width + x];
                if (x != floors->width - 1)
                    file << " ";
            }
            file << "\n";
        }
        file << "\n";

        // SAVE GAMEOBJECTS
        if (_items.size() > 0)
            file << "// ITEMS\n";
        for (auto& item : _items)
            file << "Item " << char(34) << item->name << char(34) << " " << int(item->position.x) << " " << int(item->position.y) << "\n";
        if (_items.size() > 0)
            file << "\n";


        if (_furnitures.size() > 0)
            file << "// FURNITURES\n";
        for (auto& furniture : _furnitures)
            file << "Furniture " << char(34) << furniture->name << char(34) << " " << int(furniture->position.x) << " " << int(furniture->position.y) << "\n";
        if (_furnitures.size() > 0)
            file << "\n";


        if (_walls.size() > 0)
            file << "// WALLS\n";
        for (auto& wall : _walls)
            file << "Wall " << char(34) << wall->name << char(34) << " " << int(wall->position.x) << " " << int(wall->position.y) << "\n";
        if (_walls.size() > 0)
            file << "\n";


        file.close();

    }

    bool isPart(GameObject* object) {
        if (object == nullptr)
            return false;

        for (auto& item : _items)
            if (object == item)
                return true;

        for (auto& furniture : _furnitures)
            if (object == furniture)
                return true;

        for (auto& wall : _walls)
            if (object == wall)
                return true;

        return false;
    }

    virtual void update(float dt) {
        calculateCorners();
        mouseHovering();
    }

    virtual void updateStatistic(float dt) {
        
    }

    virtual void draw() {

        if (isSelected == true) {
            window->draw(*collider->shape);
        }

        if(player!=nullptr && !playerInside()) {
            window->draw(sprite);
        }

        // TO-DO - OR

        if (player == nullptr) {
            if (GameObject::mouseIsHover == false) {
                window->draw(sprite);
            }
        }
  
    }

    virtual void drawAllStatistics() {

    }
};

std::vector < Building* > buildings;
Building* building = nullptr;

void addGameObjectsToMainLists() {
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

void removeGameObjectsFromMainLists() {
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

void createNewBuilding() {
    if (building) {
        removeGameObjectsFromMainLists();   // TO-DO
        delete building;
        building = nullptr;
    }
    
    clearAllMainListsOfGameObjects();
    building = new Building(16,16);
    terrain = new Terrain(0, 0, building->size.x, building->size.y);
    cam->setPosition(building->size.x * 16 / 2 + 160, building->size.y * 16 / 2);

}

void loadBuildingFromFile(string filename = "assets/buildings/testBuilding.txt") {
    if (building) {
        removeGameObjectsFromMainLists();   // TO-DO
        delete building;
        building = nullptr;
    }

    clearAllMainListsOfGameObjects();
    building = new Building(filename);
    terrain = new Terrain(0, 0, building->size.x, building->size.y);
    addGameObjectsToMainLists();    // TO-DO
    
}

void saveBuildingToFile(string filename = "assets/buildings/testBuilding.building") {
    building->save(filename);
}
#endif 