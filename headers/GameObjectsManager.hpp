#ifndef GameObjectsManager_hpp
#define GameObjectsManager_hpp

std::vector < GameObject* > selectedGameObjects;

Building* isPartOfBuilding(GameObject* object) {

    if (object == nullptr)
        return nullptr;

    for (auto& building : buildings)
        if (building->isPart(object)) {
            //cout << "is a part of building\n";
            return building;
        }
            
    //cout << "is not a part of building\n";
    return nullptr;
}

void selectGameObjects(float rect_x, float rect_y, float rect_w, float rect_h) {

    if (!selectedGameObjects.empty())
        for (auto& s : selectedGameObjects)
            s->isSelected = false;

    selectedGameObjects.clear();

    for (auto& go : gameObjects) {

        if (go->type == GameObjectType::Furniture || isPartOfBuilding(go)==nullptr) {
            if (intersectionRectangleWithElipse(rect_x, rect_y, rect_w, rect_h, go->position.x, go->position.y, go->collider->width / 2, go->collider->length / 2)) {
                go->isSelected = true;
                selectedGameObjects.push_back(go);
            }
        }
            
    }
}

void clearAllMainListsOfGameObjects() {
    // clear all main lists

    for (auto& nature : natures) {
        auto it = std::find(natures.begin(), natures.end(), nature);
        if (it != natures.end()) {
            natures.erase(it);
            delete nature;
        }
            
    }

    gameObjects.clear();

    natures.clear();
    itemsOnMap.clear();
    paths.clear();
    furnitures.clear();
    walls.clear();
    doors.clear();
    monsters.clear();
    characters.clear();
    inventoriesOnMap.clear();
    buildings.clear();
}

void deleteGameObjectFromMainLists(GameObject* object) {

    if (object->type == GameObjectType::Nature) {
        auto it = std::find(natures.begin(), natures.end(), object);
        if (it != natures.end())
            natures.erase(it);

        auto go = std::find(gameObjects.begin(), gameObjects.end(), object);
        if (go != gameObjects.end())
            gameObjects.erase(go);
    }

    if (object->type == GameObjectType::ItemOnMap) {
        auto it = std::find(itemsOnMap.begin(), itemsOnMap.end(), object);
        if (it != itemsOnMap.end())
            itemsOnMap.erase(it);

        auto go = std::find(gameObjects.begin(), gameObjects.end(), object);
        if (go != gameObjects.end())
            gameObjects.erase(go);
    }

    if (object->type == GameObjectType::Path) {
        auto it = std::find(paths.begin(), paths.end(), object);
        if (it != paths.end())
            paths.erase(it);

        auto go = std::find(gameObjects.begin(), gameObjects.end(), object);
        if (go != gameObjects.end())
            gameObjects.erase(go);
    }

    if (object->type == GameObjectType::Furniture) {
        auto it = std::find(furnitures.begin(), furnitures.end(), object);
        if (it != furnitures.end())
            furnitures.erase(it);

        auto go = std::find(gameObjects.begin(), gameObjects.end(), object);
        if (go != gameObjects.end())
            gameObjects.erase(go);
    }

    if (object->type == GameObjectType::Wall) {
        auto it = std::find(walls.begin(), walls.end(), object);
        if (it != walls.end())
            walls.erase(it);

        auto go = std::find(gameObjects.begin(), gameObjects.end(), object);
        if (go != gameObjects.end())
            gameObjects.erase(go);
    }

    if (object->type == GameObjectType::Door) {
        auto it = std::find(doors.begin(), doors.end(), object);
        if (it != doors.end())
            doors.erase(it);

        auto go = std::find(gameObjects.begin(), gameObjects.end(), object);
        if (go != gameObjects.end())
            gameObjects.erase(go);
    }

    if (object->type == GameObjectType::Monster) {
        auto it = std::find(monsters.begin(), monsters.end(), object);
        if (it != monsters.end())
            monsters.erase(it);

        auto go = std::find(gameObjects.begin(), gameObjects.end(), object);
        if (go != gameObjects.end())
            gameObjects.erase(go);
    }

    if (object->type == GameObjectType::Character) {
        auto it = std::find(characters.begin(), characters.end(), object);
        if (it != characters.end())
            characters.erase(it);

        auto go = std::find(gameObjects.begin(), gameObjects.end(), object);
        if (go != gameObjects.end())
            gameObjects.erase(go);
    }

    if (object->type == GameObjectType::InventoryOnMap) {
        auto it = std::find(inventoriesOnMap.begin(), inventoriesOnMap.end(), object);
        if (it != inventoriesOnMap.end())
            inventoriesOnMap.erase(it);

        auto go = std::find(gameObjects.begin(), gameObjects.end(), object);
        if (go != gameObjects.end())
            gameObjects.erase(go);
    }

    // TO-DO BUILDINGS
    if (object->type == GameObjectType::Building) {

        Building* b = dynamic_cast<Building*>(object);

        // delete Doors
        auto d = std::find(doors.begin(), doors.end(), b->_door);
        if (d != doors.end())
            doors.erase(d);

        auto dgo = std::find(gameObjects.begin(), gameObjects.end(), b->_door);
        if (dgo != gameObjects.end())
            gameObjects.erase(dgo);

        // delete items
        for (auto& item : b->_items) {
            auto it = std::find(itemsOnMap.begin(), itemsOnMap.end(), item);
            if (it != itemsOnMap.end())
                itemsOnMap.erase(it);

            auto go = std::find(gameObjects.begin(), gameObjects.end(), item);
            if (go != gameObjects.end())
                gameObjects.erase(go);
        }

        // delete furnitures
        for (auto& furniture : b->_furnitures) {
            auto it = std::find(furnitures.begin(), furnitures.end(), furniture);
            if (it != furnitures.end())
                furnitures.erase(it);

            auto go = std::find(gameObjects.begin(), gameObjects.end(), furniture);
            if (go != gameObjects.end())
                gameObjects.erase(go);
        }

        // delete walls
        for (auto& wall : b->_walls) {
            auto it = std::find(walls.begin(), walls.end(), wall);
            if (it != walls.end())
                walls.erase(it);

            auto go = std::find(gameObjects.begin(), gameObjects.end(), wall);
            if (go != gameObjects.end())
                gameObjects.erase(go);
        }

        auto it = std::find(buildings.begin(), buildings.end(), object);
        if (it != buildings.end())
            buildings.erase(it);

        auto go = std::find(gameObjects.begin(), gameObjects.end(), object);
        if (go != gameObjects.end())
            gameObjects.erase(go);
    }

}

bool visiblings(GameObject* object) {
    // return true if GameObject is visible

    if (object != nullptr) {

        if (object->collider->isRectangular == false) {
            if (intersectionRectangleWithElipse(cam->position.x, cam->position.y, screenWidth * 1.5f, screenHeight * 1.5f, object->position.x, object->position.y, object->collider->width / 2.0f, object->collider->length / 2.0f)) {
                return true;
            }
        }

        if (object->collider->isRectangular == true) {
            if (intersectionTwoRectangles(cam->position.x, cam->position.y, screenWidth * 1.5f, screenHeight * 1.5f, object->position.x, object->position.y, object->collider->width, object->collider->length))
                return true;
        }
    }

    return false;
}

void updateGameObjects() {

	for (auto& go : gameObjects) {
        if (visiblings(go)) {

            go->update(dt);
            
            if (go->type == GameObjectType::Furniture || !isPartOfBuilding(go)) {
                go->mouseHovering();
            }
        }
	}
}

void sortGameObjects() {

    std::sort(gameObjects.begin(), gameObjects.end(), [](const auto& a, const auto& b) { return a->position.y < b->position.y; });
}

void drawGameObjects() {

	for (auto& p : paths) {
		if (visiblings(p))
			p->draw();
	}

	for (auto& go : gameObjects)
		if (go->type != GameObjectType::Path)
			if (go->type == GameObjectType::Building || visiblings(go))
				if(visiblings(go))
                    go->draw();

}

#endif