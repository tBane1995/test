#ifndef MapEditorPalette_hpp
#define MapEditorPalette_hpp
/*
sf::Vector2f paletteButtonSize = sf::Vector2f(80.0f, 80.0f);
sf::Vector2f palettePosition;
std::vector < GameObject* > availableGameObjects;
std::vector < GameObject* > terrainGameObjects;
std::vector < GameObject* > floorGameObjects;
std::vector < GameObject* > buildingGameObjects;


short paletteScroll;
short paletteCols;
short paletteRows;
*/

toolType tool;
short brushSize;

class ButtonWithImage {
public:

    sf::Vector2f position;
    sf::Sprite sprite;
    ButtonState state;
    std::function<void()> func;
    sf::Time clickTime;

    ButtonWithImage() {
        sprite = sf::Sprite();
        state = ButtonState::Idle;
        func = { };
        
        clickTime = currentTime;
        changeColor();
    }

    ButtonWithImage(ButtonWithImage* btn) {

        this->position = btn->position;
        this->sprite = btn->sprite;
        state = ButtonState::Idle;
        this->func = btn->func;

        clickTime = currentTime;
        changeColor();
    }

    ButtonWithImage(ButtonWithImage* btn, sf::Vector2f position) {


        this->position = position;
        this->sprite = btn->sprite;
        state = ButtonState::Idle;
        this->func = btn->func;

        clickTime = currentTime;
        changeColor();
    }

    ButtonWithImage(Texture* texture, sf::Vector2f position) {
        this->position = position;

        sprite = sf::Sprite();

        state = ButtonState::Idle;

        if (texture != nullptr) {
            sprite.setTexture(*texture->texture);
            sprite.setOrigin(texture->texture->getSize().x / 2.0f, texture->texture->getSize().y / 2.0f);
        }

        func = { };

        clickTime = currentTime;
        changeColor();
    }

    virtual void setTexture(Texture* texture) {
        sprite = sf::Sprite();
        sprite.setTexture(*texture->texture);
        sprite.setOrigin(texture->texture->getSize().x / 2, texture->texture->getSize().y / 2);
    }

    virtual void setPosition(sf::Vector2f position) {
        this->position = position;
        sprite.setPosition(position);
    }

    virtual void changeColor() {

        if (state == ButtonState::Pressed) {
            sprite.setColor(spritePressedColor);
        }
        else if (state == ButtonState::Hover) {
            sprite.setColor(spriteHoverColor);
        }
        else {
            sprite.setColor(spriteIdleColor);
        }
            
    }

    virtual void unclick() {
        if ((currentTime - clickTime).asSeconds() > 0.1f) {
            state = ButtonState::Idle;
            changeColor();
        }
            
    }

    virtual void hover() {
        if (state != ButtonState::Pressed) {

            float w = sprite.getTexture()->getSize().x;
            float h = sprite.getTexture()->getSize().y;
            float x = sprite.getPosition().x;
            float y = sprite.getPosition().y;

            if (worldMousePosition.x > x - w / 2.0f && worldMousePosition.x < x + w / 2.0f &&
                worldMousePosition.y > y - h / 2.0f && worldMousePosition.y < y + h / 2.0f) {

                state = ButtonState::Hover;
                changeColor();
                GUIwasHover = true;
            }
        }
        else {
            // GUI WAS PRESSED
            GUIwasHover = true;
        }
    }

    virtual void click() {
        float w = sprite.getTexture()->getSize().x;
        float h = sprite.getTexture()->getSize().y;
        float x = sprite.getPosition().x;
        float y = sprite.getPosition().y;

        if (worldMousePosition.x > x - w / 2.0f && worldMousePosition.x < x + w / 2.0f &&
            worldMousePosition.y > y - h / 2.0f && worldMousePosition.y < y + h / 2.0f) {
            
            state = ButtonState::Pressed;
            changeColor();
            GUIwasClicked = true;
            clickTime = currentTime;

            if (func) {
                func();
            }
                
    
        }

    }

    virtual void update(float dt) {
        sprite.setPosition(cam->position.x + position.x, cam->position.y + position.y);
    }

    virtual void draw() {

        window->draw(sprite);
    }
};


enum class PaletteType { MapEditor, BuildingEditor };

class PaletteButton : public ButtonWithImage {
public:

    GameObject* object;
    sf::Sprite sprite;

    PaletteButton(sf::Vector2f position) : ButtonWithImage(getTexture("GUI/slot2"), position) {
        object = nullptr;
    }

    void setGameObject(GameObject* object) {
        this->object = object;

        sprite = sf::Sprite();

        if (object != nullptr) {
            
            sprite.setTexture(*getTexture(object->name)->texture);

            if (object->type != GameObjectType::ItemOnMap) {

                sf::Vector2f o; // origin
                o.x = sprite.getTexture()->getSize().x / 2.0f;
                o.y = sprite.getTexture()->getSize().y / 2.0f;
                sprite.setOrigin(o);

                sf::Vector2f s; // scale
                s.x = 64.0f / float(sprite.getTexture()->getSize().x) * 0.75f;
                s.y = 64.0f / float(sprite.getTexture()->getSize().y) * 0.75f;
                sprite.setScale(s);
            }
            else {
                // Items
                sprite.setOrigin(28, 28);
                sprite.setTextureRect(sf::IntRect(4, 4, 56, 56));
            }

            func = [this]() {
                tool = toolType::AddGameObject;
                prefabToPaint = this->object;
                };
        }
        
        sprite.setPosition(position.x + cam->position.x, position.y + cam->position.y);
        
    }

    virtual void update(float dt) {
        ButtonWithImage::update(dt);
        sprite.setPosition(position.x + cam->position.x, position.y + cam->position.y);
    }

    virtual void draw() {
        ButtonWithImage::draw();
        
        if (object != nullptr)
            window->draw(sprite);
        
    }
};

class Palette {
public:

    PaletteType type;
    sf::Vector2i size;

    std::vector < GameObject* > terrainGameObjects;
    std::vector < GameObject* > floorGameObjects;

    std::vector < ButtonWithImage* > groupButtons;
    std::vector < ButtonWithImage* > toolsButtons;
    std::vector < PaletteButton* > paletteButtons;

    ButtonWithImage* selectedGroupButton;
    ButtonWithImage* selectedToolButton;
    PaletteButton* selectedPaletteButton;

    ButtonWithImage* buttonUp;
    ButtonWithImage* buttonDown;

    short scroll;

    ButtonWithImage* btnGroupEmpty;
    ButtonWithImage* btnGroupTerrain;
    ButtonWithImage* btnGroupFloors;
    ButtonWithImage* btnGroupFurnitures;
    ButtonWithImage* btnGroupWalls;
    ButtonWithImage* btnGroupMonsters;
    ButtonWithImage* btnGroupPaths;
    ButtonWithImage* btnGroupItems;
    ButtonWithImage* btnGroupNatures;

    ButtonWithImage* btnToolsEmpty;
    ButtonWithImage* btnToolsCursor;
    ButtonWithImage* btnToolsBrush;
    ButtonWithImage* btnToolsRectBrush;
    ButtonWithImage* btnToolsIncrease;
    ButtonWithImage* btnToolsDecrease;
    ButtonWithImage* btnToolsRectangle;
    ButtonWithImage* btnToolsElipse;
    ButtonWithImage* btnToolsFill;
    ButtonWithImage* btnToolsEraser;

    std::vector < GameObject* > availableGameObjects;

    Palette(PaletteType type) {
        this->type = type;

        createTerrainPrefabs();
        createFloorsPrefabs();
        
        
        createPaletteButtons(5,7);
        createToolsButtons();
        createNavButtons();
        createGroupButtons();


        if(type == PaletteType::MapEditor)        selectedGroupButton = btnGroupTerrain;
        if(type == PaletteType::BuildingEditor)   selectedGroupButton = btnGroupFloors;
        
        selectedToolButton = btnToolsCursor;
        selectedPaletteButton = nullptr;

        if(type == PaletteType::MapEditor)       setTerrainObjectsToPalette();
        if(type == PaletteType::BuildingEditor)  setFloorsObjectsToPalette();

        loadPalette();

        ///////////////////////

        tool = toolType::Cursor;
        brushSize = 0;
    }

    void createTerrainPrefabs() {
        terrainGameObjects.clear();
        terrainGameObjects.push_back(new TerrainPrefab("tiles/tile_0_grass", terrainType::grass));
        terrainGameObjects.push_back(new TerrainPrefab("tiles/tile_1_sands", terrainType::sands));
        terrainGameObjects.push_back(new TerrainPrefab("tiles/tile_2_water", terrainType::water));
        terrainGameObjects.push_back(new TerrainPrefab("tiles/tile_3_gravel", terrainType::gravel));
        terrainGameObjects.push_back(new TerrainPrefab("tiles/tile_4_beach", terrainType::beach));
    }

    void createFloorsPrefabs() {
        floorGameObjects.clear();
        floorGameObjects.push_back(new FloorPrefab("floors/floor_0", floorType::floor_0));
        floorGameObjects.push_back(new FloorPrefab("floors/floor_1", floorType::floor_1));
        floorGameObjects.push_back(new FloorPrefab("floors/floor_2", floorType::floor_2));
        floorGameObjects.push_back(new FloorPrefab("floors/floor_3", floorType::floor_3));
    }

    void deletePaletteButtons() {
        if (paletteButtons.size() > 0) {
            for (int i = 0; i < paletteButtons.size(); i++) {
                delete paletteButtons[i];
            }

            paletteButtons.clear();
        }
    }

    void deleteNavButtons() {
        if (buttonUp != nullptr) {
            delete buttonUp;
            buttonUp = nullptr;
        }

        if (buttonDown != nullptr) {
            delete buttonDown;
            buttonDown = nullptr;
        }
    }

    void deleteToolsButtons() {
        if (toolsButtons.size() > 0) {
            for (int i = 0; i < toolsButtons.size(); i++) {
                delete toolsButtons[i];
            }

            toolsButtons.clear();
        }

        cout << "delete Tools Buttons\n";
    }

    void deleteGroupButtons() {
        if (groupButtons.size() > 0) {
            for (int i = 0; i < groupButtons.size(); i++) {
                delete groupButtons[i];
            }

            groupButtons.clear();
        }
    }

    void createPaletteButtons(short size_x, short size_y) {

        deletePaletteButtons();
        
        size.x = size_x;
        size.y = size_y;

        sf::Vector2f start_pos; // left bottom 
        start_pos.x = 0;
        start_pos.x = screenWidth/2.0f - size.x*64 + 32;
        start_pos.y = screenHeight/2.0f - 37 - 32;

        for (short y = 0; y < size.y; y++) {
            for (short x = 0; x < size.x; x++) {

                sf::Vector2f pos;
                pos.x = start_pos.x + x * 64;
                pos.y = start_pos.y - (size.y -1 - y) * 64;

                PaletteButton* btn = new PaletteButton(pos);
                paletteButtons.push_back(btn);
            }
        }
        


    }

    void setTerrainObjectsToPalette() {

        availableGameObjects.clear();

        for (auto& terrain : terrainGameObjects)
            availableGameObjects.push_back(terrain);

    }

    void setFloorsObjectsToPalette() {

        availableGameObjects.clear();

        for (auto& floor : floorGameObjects)
            availableGameObjects.push_back(floor);

    }

    void setFurnituresObjectsToPalette() {
        availableGameObjects.clear();

        for (auto& f : furnitures)
            availableGameObjects.push_back(f);
    }

    void setWallsObjectsToPalette() {
        availableGameObjects.clear();

        availableGameObjects.push_back(getPrefab("walls/mud_wall_0"));
        availableGameObjects.push_back(getPrefab("walls/mud_wall_1"));
        availableGameObjects.push_back(getPrefab("walls/mud_wall_1"));
        availableGameObjects.push_back(getPrefab("walls/mud_wall_1"));
        availableGameObjects.push_back(getPrefab("walls/mud_wall_2"));

        availableGameObjects.push_back(getPrefab("walls/mud_wall_3"));
        availableGameObjects.push_back(getPrefab("walls/empty_wall"));
        availableGameObjects.push_back(getPrefab("walls/empty_wall"));
        availableGameObjects.push_back(getPrefab("walls/empty_wall"));
        availableGameObjects.push_back(getPrefab("walls/mud_wall_3"));

        availableGameObjects.push_back(getPrefab("walls/mud_wall_3"));
        availableGameObjects.push_back(getPrefab("walls/empty_wall"));
        availableGameObjects.push_back(getPrefab("walls/mud_wall_4"));
        availableGameObjects.push_back(getPrefab("walls/empty_wall"));
        availableGameObjects.push_back(getPrefab("walls/mud_wall_3"));

        availableGameObjects.push_back(getPrefab("walls/mud_wall_3"));
        availableGameObjects.push_back(getPrefab("walls/empty_wall"));
        availableGameObjects.push_back(getPrefab("walls/mud_wall_5"));
        availableGameObjects.push_back(getPrefab("walls/empty_wall"));
        availableGameObjects.push_back(getPrefab("walls/mud_wall_3"));
    
        availableGameObjects.push_back(getPrefab("walls/mud_wall_6"));
        availableGameObjects.push_back(getPrefab("walls/mud_wall_7"));
        availableGameObjects.push_back(getPrefab("walls/empty_wall"));
        availableGameObjects.push_back(getPrefab("walls/mud_wall_8"));
        availableGameObjects.push_back(getPrefab("walls/mud_wall_9"));

        availableGameObjects.push_back(getPrefab("walls/mud_wall_5"));
        availableGameObjects.push_back(getPrefab("walls/mud_wall_5"));
        availableGameObjects.push_back(getPrefab("walls/empty_wall"));
        availableGameObjects.push_back(getPrefab("walls/mud_wall_5"));
        availableGameObjects.push_back(getPrefab("walls/mud_wall_5"));

        availableGameObjects.push_back(nullptr);
        availableGameObjects.push_back(nullptr);
        availableGameObjects.push_back(nullptr);
        availableGameObjects.push_back(nullptr);
        availableGameObjects.push_back(nullptr);

        availableGameObjects.push_back(getPrefab("walls/stone_wall_0"));
        availableGameObjects.push_back(getPrefab("walls/stone_wall_1"));
        availableGameObjects.push_back(getPrefab("walls/stone_wall_1"));
        availableGameObjects.push_back(getPrefab("walls/stone_wall_1"));
        availableGameObjects.push_back(getPrefab("walls/stone_wall_2"));

        availableGameObjects.push_back(getPrefab("walls/stone_wall_3"));
        availableGameObjects.push_back(getPrefab("walls/empty_wall"));
        availableGameObjects.push_back(getPrefab("walls/empty_wall"));
        availableGameObjects.push_back(getPrefab("walls/empty_wall"));
        availableGameObjects.push_back(getPrefab("walls/stone_wall_3"));

        availableGameObjects.push_back(getPrefab("walls/stone_wall_3"));
        availableGameObjects.push_back(getPrefab("walls/empty_wall"));
        availableGameObjects.push_back(getPrefab("walls/stone_wall_4"));
        availableGameObjects.push_back(getPrefab("walls/empty_wall"));
        availableGameObjects.push_back(getPrefab("walls/stone_wall_3"));

        availableGameObjects.push_back(getPrefab("walls/stone_wall_3"));
        availableGameObjects.push_back(getPrefab("walls/empty_wall"));
        availableGameObjects.push_back(getPrefab("walls/stone_wall_5"));
        availableGameObjects.push_back(getPrefab("walls/empty_wall"));
        availableGameObjects.push_back(getPrefab("walls/stone_wall_3"));

        availableGameObjects.push_back(getPrefab("walls/stone_wall_6"));
        availableGameObjects.push_back(getPrefab("walls/stone_wall_7"));
        availableGameObjects.push_back(getPrefab("walls/empty_wall"));
        availableGameObjects.push_back(getPrefab("walls/stone_wall_8"));
        availableGameObjects.push_back(getPrefab("walls/stone_wall_9"));

        availableGameObjects.push_back(getPrefab("walls/stone_wall_5"));
        availableGameObjects.push_back(getPrefab("walls/stone_wall_5"));
        availableGameObjects.push_back(getPrefab("walls/empty_wall"));
        availableGameObjects.push_back(getPrefab("walls/stone_wall_5"));
        availableGameObjects.push_back(getPrefab("walls/stone_wall_5"));


        availableGameObjects.push_back(nullptr);
        availableGameObjects.push_back(nullptr);
        availableGameObjects.push_back(nullptr);
        availableGameObjects.push_back(nullptr);
        availableGameObjects.push_back(nullptr);

        availableGameObjects.push_back(getPrefab("walls/wooden_wall_0"));
        availableGameObjects.push_back(getPrefab("walls/wooden_wall_1"));
        availableGameObjects.push_back(getPrefab("walls/wooden_wall_1"));
        availableGameObjects.push_back(getPrefab("walls/wooden_wall_1"));
        availableGameObjects.push_back(getPrefab("walls/wooden_wall_2"));

        availableGameObjects.push_back(getPrefab("walls/wooden_wall_3"));
        availableGameObjects.push_back(getPrefab("walls/empty_wall"));
        availableGameObjects.push_back(getPrefab("walls/empty_wall"));
        availableGameObjects.push_back(getPrefab("walls/empty_wall"));
        availableGameObjects.push_back(getPrefab("walls/wooden_wall_3"));

        availableGameObjects.push_back(getPrefab("walls/wooden_wall_3"));
        availableGameObjects.push_back(getPrefab("walls/empty_wall"));
        availableGameObjects.push_back(getPrefab("walls/wooden_wall_4"));
        availableGameObjects.push_back(getPrefab("walls/empty_wall"));
        availableGameObjects.push_back(getPrefab("walls/wooden_wall_3"));

        availableGameObjects.push_back(getPrefab("walls/wooden_wall_3"));
        availableGameObjects.push_back(getPrefab("walls/empty_wall"));
        availableGameObjects.push_back(getPrefab("walls/wooden_wall_5"));
        availableGameObjects.push_back(getPrefab("walls/empty_wall"));
        availableGameObjects.push_back(getPrefab("walls/wooden_wall_3"));

        availableGameObjects.push_back(getPrefab("walls/wooden_wall_6"));
        availableGameObjects.push_back(getPrefab("walls/wooden_wall_7"));
        availableGameObjects.push_back(getPrefab("walls/empty_wall"));
        availableGameObjects.push_back(getPrefab("walls/wooden_wall_8"));
        availableGameObjects.push_back(getPrefab("walls/wooden_wall_9"));

        availableGameObjects.push_back(getPrefab("walls/wooden_wall_5"));
        availableGameObjects.push_back(getPrefab("walls/wooden_wall_5"));
        availableGameObjects.push_back(getPrefab("walls/empty_wall"));
        availableGameObjects.push_back(getPrefab("walls/wooden_wall_5"));
        availableGameObjects.push_back(getPrefab("walls/wooden_wall_5"));

    }

    void setMonstersObjectsToPalette() {
        availableGameObjects.clear();

        for (auto& p : prefabs) {
            if (p->type == GameObjectType::Monster) {
                availableGameObjects.push_back(p);
            }
        }
    }

    void setPathsObjectsToPalette() {
        availableGameObjects.clear();

        for (auto& p : prefabs) {
            if (p->type == GameObjectType::Path) {
                availableGameObjects.push_back(p);
            }
        }
    }

    void setItemsObjectsToPalette() {
        availableGameObjects.clear();

        for (auto& i : items) {
            availableGameObjects.push_back(getPrefab(i->name));
        }

    }

    void setNaturesObjectsToPalette() {
        availableGameObjects.clear();

        for (auto& p : prefabs) {
            if (p->type == GameObjectType::Nature) {
                availableGameObjects.push_back(p);
            }
        }
    }

    void loadPalette() {
        for (int i = 0; i < paletteButtons.size(); i++) {

            int index = i + scroll * size.x;

            GameObject* object;
            (index < availableGameObjects.size())? object = availableGameObjects[index] : object = nullptr;
            paletteButtons[i]->setGameObject(object);

            if(object!=nullptr)
                if (object->type == GameObjectType::Terrain || object->type == GameObjectType::Floor) {
                    // object is a Terrain or Floor
                    auto button = paletteButtons[i];
                    paletteButtons[i]->func = [this, button]() {
                        prefabToPaint = button->object;
                        selectedPaletteButton = button;

                        if (tool == toolType::Cursor || tool == toolType::AddGameObject) {
                            tool = toolType::Brush;
                            selectedToolButton = btnToolsBrush;
                        }
                            
                        };
                }
                else {
                    // object is not Terrain or Floor
                    auto button = paletteButtons[i];
                    paletteButtons[i]->func = [this, button]() {
                        prefabToPaint = button->object;
                        selectedPaletteButton = button;

                        tool = toolType::AddGameObject;
                        selectedToolButton = btnToolsEmpty;
                        };
                }

                

                
        }
    }

    void createNavButtons() {

        deleteNavButtons();

        scroll = 0;

        sf::Vector2f pos;
        pos.x = screenWidth / 2.0f - 160;

        pos.y = screenHeight / 2.0f - 37.0f - float(size.y) * 64.0f - 37.0f/2.0f;
        buttonUp = new ButtonWithImage(getTexture("GUI/wideArrowUp2"), pos);
        buttonUp->func = [this]() {
            scrollUp();
            loadPalette();
            };

        pos.y = screenHeight / 2.0f - 37.0f/2.0f;
        buttonDown = new ButtonWithImage(getTexture("GUI/wideArrowDown2"), pos);
        buttonDown->func = [this]() {
            scrollDown();
            loadPalette();
            };

    }

    void createToolsButtons() {
        // delete old Tools Buttons
        deleteToolsButtons();

        cout << "create Tools Buttons\n";
        btnToolsEmpty = new ButtonWithImage();
        btnToolsEmpty->setTexture(getTexture("GUI/toolButtons/toolbutton"));

        btnToolsCursor = new ButtonWithImage();
        btnToolsCursor->setTexture(getTexture("GUI/toolButtons/toolbutton-cursor"));
        btnToolsCursor->func = [this]() {
            selectedToolButton = btnToolsCursor;
            tool = toolType::Cursor;
            selectedPaletteButton = nullptr;
            prefabToPaint = nullptr;
        };


        btnToolsBrush = new ButtonWithImage();
        btnToolsBrush->setTexture(getTexture("GUI/toolButtons/toolbutton-brush"));
        btnToolsBrush->func = [this]() {
            selectedToolButton = btnToolsBrush;
            tool = toolType::Brush;
            if (prefabToPaint == nullptr) {
                prefabToPaint = availableGameObjects[1];
                selectedPaletteButton = paletteButtons[1];
            }
        };


        btnToolsRectBrush = new ButtonWithImage();
        btnToolsRectBrush->setTexture(getTexture("GUI/toolButtons/toolbutton-rect_brush"));
        btnToolsRectBrush->func = [this]() {
            selectedToolButton = btnToolsRectBrush;
            tool = toolType::RectBrush;
            if (prefabToPaint == nullptr) {
                prefabToPaint = availableGameObjects[1];
                selectedPaletteButton = paletteButtons[1];
            }
        };


        btnToolsIncrease = new ButtonWithImage();
        btnToolsIncrease->setTexture(getTexture("GUI/toolButtons/toolbutton-increase"));
        btnToolsIncrease->func = [this]() {
            if (selectedToolButton == btnToolsBrush || selectedToolButton == btnToolsRectBrush || selectedToolButton == btnToolsEraser) {
                if (brushSize < 5) {
                    brushSize++;
                    setBrushSize(brushSize);

                    coutBrush();
                    //cout << "\n\n";
                }

            }
        };


        btnToolsDecrease = new ButtonWithImage();
        btnToolsDecrease->setTexture(getTexture("GUI/toolButtons/toolbutton-decrease"));
        btnToolsDecrease->func = [this]() {
            if (selectedToolButton == btnToolsBrush || selectedToolButton == btnToolsRectBrush || selectedToolButton == btnToolsEraser) {
                if (brushSize > 0) {
                    brushSize--;
                    setBrushSize(brushSize);

                    //coutBrush();
                    //cout << "\n\n";
                }


            }
        };


        btnToolsRectangle = new ButtonWithImage();
        btnToolsRectangle->setTexture(getTexture("GUI/toolButtons/toolbutton-rectangle"));
        btnToolsRectangle->func = [this]() {
            selectedToolButton = btnToolsRectangle;
            tool = toolType::Rectangle;
            if (prefabToPaint == nullptr) {
                prefabToPaint = availableGameObjects[1];
                selectedPaletteButton = paletteButtons[1];
            }
        };


        btnToolsElipse = new ButtonWithImage();
        btnToolsElipse->setTexture(getTexture("GUI/toolButtons/toolbutton-elipse"));
        btnToolsElipse->func = [this]() {
            selectedToolButton = btnToolsElipse;
            tool = toolType::Elipse;
            if (prefabToPaint == nullptr) {
                prefabToPaint = availableGameObjects[1];
                selectedPaletteButton = paletteButtons[1];
            }
        };


        btnToolsFill = new ButtonWithImage();
        btnToolsFill->setTexture(getTexture("GUI/toolButtons/toolbutton-fill"));
        btnToolsFill->func = [this]() {
            selectedToolButton = btnToolsFill;
            tool = toolType::Fill;
        };


        btnToolsEraser = new ButtonWithImage();
        btnToolsEraser->setTexture(getTexture("GUI/toolButtons/toolbutton-eraser"));
        btnToolsEraser->func = [this]() {
            selectedToolButton = btnToolsEraser;
            selectedPaletteButton = nullptr;
            prefabToPaint = nullptr;
            tool = toolType::Eraser;
            if (prefabToPaint == nullptr) {
                prefabToPaint = availableGameObjects[1];
                selectedPaletteButton = paletteButtons[1];
            }
        };

        sf::Vector2f sp;    // start position
        sp.x = screenWidth / 2.0f - 10*32 + 16;
        sp.y = -screenHeight/2.0f + 2*52 + 16 + 30;

        toolsButtons.push_back(new ButtonWithImage(btnToolsCursor, sf::Vector2f(sp.x, sp.y)));
        toolsButtons.push_back(new ButtonWithImage(btnToolsBrush, sf::Vector2f(sp.x + 32, sp.y)));
        toolsButtons.push_back(new ButtonWithImage(btnToolsRectBrush, sf::Vector2f(sp.x + 64, sp.y)));
        toolsButtons.push_back(new ButtonWithImage(btnToolsIncrease, sf::Vector2f(sp.x + 96, sp.y)));
        toolsButtons.push_back(new ButtonWithImage(btnToolsDecrease, sf::Vector2f(sp.x + 128, sp.y)));
        toolsButtons.push_back(new ButtonWithImage(btnToolsRectangle, sf::Vector2f(sp.x + 160, sp.y)));
        toolsButtons.push_back(new ButtonWithImage(btnToolsElipse, sf::Vector2f(sp.x + 192, sp.y)));
        //tools.push_back(new Button(btnToolsFill, sf::Vector2f(sp.x + 280, sp.y)));    / /TO-DO
        toolsButtons.push_back(new ButtonWithImage(btnToolsEmpty, sf::Vector2f(sp.x + 224, sp.y)));
        toolsButtons.push_back(new ButtonWithImage(btnToolsEmpty, sf::Vector2f(sp.x + 256, sp.y)));
        toolsButtons.push_back(new ButtonWithImage(btnToolsEmpty, sf::Vector2f(sp.x + 288, sp.y)));

        toolsButtons.push_back(new ButtonWithImage(btnToolsEmpty, sf::Vector2f(sp.x, sp.y + 32)));
        toolsButtons.push_back(new ButtonWithImage(btnToolsEmpty, sf::Vector2f(sp.x + 32, sp.y + 32)));
        toolsButtons.push_back(new ButtonWithImage(btnToolsEmpty, sf::Vector2f(sp.x + 64, sp.y + 32)));
        toolsButtons.push_back(new ButtonWithImage(btnToolsEmpty, sf::Vector2f(sp.x + 96, sp.y + 32)));
        toolsButtons.push_back(new ButtonWithImage(btnToolsEmpty, sf::Vector2f(sp.x + 128, sp.y + 32)));
        toolsButtons.push_back(new ButtonWithImage(btnToolsEmpty, sf::Vector2f(sp.x + 160, sp.y + 32)));
        toolsButtons.push_back(new ButtonWithImage(btnToolsEmpty, sf::Vector2f(sp.x + 192, sp.y + 32)));
        toolsButtons.push_back(new ButtonWithImage(btnToolsEmpty, sf::Vector2f(sp.x + 224, sp.y + 32)));
        toolsButtons.push_back(new ButtonWithImage(btnToolsEmpty, sf::Vector2f(sp.x + 256, sp.y + 32)));
        toolsButtons.push_back(new ButtonWithImage(btnToolsEmpty, sf::Vector2f(sp.x + 288, sp.y + 32)));

        brushSize = 0;
        setBrushSize(brushSize);
    }

    void createGroupButtons() {

        deleteGroupButtons();

        // create Group Buttons
        btnGroupEmpty = new ButtonWithImage();
        btnGroupEmpty->setTexture(getTexture("GUI/menuButtons/menuButton"));

        btnGroupTerrain = new ButtonWithImage();
        btnGroupTerrain->setTexture(getTexture("GUI/menuButtons/menuButton-terrain"));
        btnGroupTerrain->func = [this]() {
            selectedGroupButton = btnGroupTerrain;
            tool = toolType::Cursor;
            selectedPaletteButton = nullptr;
            prefabToPaint = nullptr;
            createPaletteButtons(5,7);
            createNavButtons();
            createToolsButtons();
            setTerrainObjectsToPalette();
            loadPalette();
            };

        btnGroupFloors = new ButtonWithImage();
        btnGroupFloors->setTexture(getTexture("GUI/menuButtons/menuButton-floors"));
        btnGroupFloors->func = [this]() {
            selectedGroupButton = btnGroupFloors;
            selectedPaletteButton = nullptr;
            prefabToPaint = nullptr;
            createPaletteButtons(5,7);
            createNavButtons();
            createToolsButtons();
            setFloorsObjectsToPalette();
            loadPalette();
            };

        btnGroupFurnitures = new ButtonWithImage();
        btnGroupFurnitures->setTexture(getTexture("GUI/menuButtons/menuButton-furnitures"));
        btnGroupFurnitures->func = [this]() {
            selectedGroupButton = btnGroupFurnitures;
            tool = toolType::Cursor;
            selectedPaletteButton = nullptr;
            prefabToPaint = nullptr;
            createPaletteButtons(5,8);
            createNavButtons();
            deleteToolsButtons();
            setFurnituresObjectsToPalette();
            loadPalette();
            };

        btnGroupWalls = new ButtonWithImage();
        btnGroupWalls->setTexture(getTexture("GUI/menuButtons/menuButton-walls"));
        btnGroupWalls->func = [this]() {
            selectedGroupButton = btnGroupWalls;
            tool = toolType::Cursor;
            selectedPaletteButton = nullptr;
            prefabToPaint = nullptr;
            createPaletteButtons(5,8);
            createNavButtons();
            deleteToolsButtons();
            setWallsObjectsToPalette();
            loadPalette();
            };

        btnGroupMonsters = new ButtonWithImage();
        btnGroupMonsters->setTexture(getTexture("GUI/menuButtons/menuButton-monsters"));
        btnGroupMonsters->func = [this]() {
            selectedGroupButton = btnGroupMonsters;
            tool = toolType::Cursor;
            selectedPaletteButton = nullptr;
            prefabToPaint = nullptr;
            createPaletteButtons(5,8);
            createNavButtons();
            deleteToolsButtons();
            setMonstersObjectsToPalette();
            loadPalette();
            };

        btnGroupPaths = new ButtonWithImage();
        btnGroupPaths->setTexture(getTexture("GUI/menuButtons/menuButton-paths"));
        btnGroupPaths->func = [this]() {
            selectedGroupButton = btnGroupPaths;
            tool = toolType::Cursor;
            selectedPaletteButton = nullptr;
            prefabToPaint = nullptr;
            createPaletteButtons(5,8);
            createNavButtons();
            deleteToolsButtons();
            setPathsObjectsToPalette();
            loadPalette();
            };

        btnGroupItems = new ButtonWithImage();
        btnGroupItems->setTexture(getTexture("GUI/menuButtons/menuButton-items"));
        btnGroupItems->func = [this]() {
            selectedGroupButton = btnGroupItems;
            tool = toolType::Cursor;
            selectedPaletteButton = nullptr;
            prefabToPaint = nullptr;
            createPaletteButtons(5,8);
            createNavButtons();
            deleteToolsButtons();
            setItemsObjectsToPalette();
            loadPalette();
            };

        btnGroupNatures = new ButtonWithImage();
        btnGroupNatures->setTexture(getTexture("GUI/menuButtons/menuButton-natures"));
        btnGroupNatures->func = [this]() {
            tool = toolType::Cursor;
            selectedGroupButton = btnGroupNatures;
            selectedPaletteButton = nullptr;
            prefabToPaint = nullptr;
            createPaletteButtons(5,8);
            createNavButtons();
            deleteToolsButtons();
            setNaturesObjectsToPalette();
            loadPalette();
            };

        // create Group Buttons Menu
        groupButtons.resize(10);

        if (type == PaletteType::MapEditor) {
            groupButtons[0] = btnGroupTerrain;
            groupButtons[1] = btnGroupNatures;
            groupButtons[2] = btnGroupPaths;
            groupButtons[3] = btnGroupMonsters;
            groupButtons[4] = btnGroupItems;
            groupButtons[5] = new ButtonWithImage(btnGroupEmpty);
            groupButtons[6] = new ButtonWithImage(btnGroupEmpty);
            groupButtons[7] = new ButtonWithImage(btnGroupEmpty);
            groupButtons[8] = new ButtonWithImage(btnGroupEmpty);
            groupButtons[9] = new ButtonWithImage(btnGroupEmpty);
        }
        else if (type == PaletteType::BuildingEditor) {
            groupButtons[0] = btnGroupFloors;
            groupButtons[1] = btnGroupFurnitures;
            groupButtons[2] = btnGroupWalls;
            groupButtons[3] = btnGroupItems;
            groupButtons[4] = new ButtonWithImage(btnGroupEmpty);
            groupButtons[5] = new ButtonWithImage(btnGroupEmpty);
            groupButtons[6] = new ButtonWithImage(btnGroupEmpty);
            groupButtons[7] = new ButtonWithImage(btnGroupEmpty);
            groupButtons[8] = new ButtonWithImage(btnGroupEmpty);
            groupButtons[9] = new ButtonWithImage(btnGroupEmpty);
        }

        for (auto i = 0; i < 10; i++) {
            sf::Vector2f position;
            position.x = screenWidth / 2.0f - (4 - i % 5) * 64 - 32;
            position.y = -screenHeight / 2.0f + i / 5 * 52 + 26 + 30;
            groupButtons[i]->setPosition(position);
        }
    }

    void scrollUp() {
        if(scroll > 0)
            scroll -= 1;
    }

    void scrollDown() {

        short maxScroll = availableGameObjects.size() - size.x * size.y;
        if (maxScroll < 0)
            maxScroll = 0;

        if(scroll*size.x < maxScroll)
            scroll += 1;
    }

    void unclickButtons() {
        for (auto& tool : toolsButtons)
            tool->unclick();

        for (auto& btn : groupButtons)
            btn->unclick();

        for (auto& btn : paletteButtons)
            btn->unclick();

        buttonUp->unclick();
        buttonDown->unclick();
    }

    void hoverButtons() {
        for (auto& tool : toolsButtons)
            tool->hover();

        for (auto& btn : groupButtons)
            btn->hover();

        for (auto& btn : paletteButtons)
            btn->hover();

        buttonUp->hover();
        buttonDown->hover();
    }

    void clickButtons() {

        for (auto& tool : toolsButtons)
            tool->click();

        for (auto& btn : groupButtons)
            btn->click();

        for (auto& btn : paletteButtons)
            btn->click();

        buttonUp->click();
        buttonDown->click();

    }

    void update(float dt) {
        for (auto& tool : toolsButtons)
            tool->update(dt);

        for (auto& btn : groupButtons)
            btn->update(dt);

        for (auto& btn : paletteButtons) 
            btn->update(dt);
            
        buttonUp->update(dt);
        buttonDown->update(dt);
    }

    void draw() {

        if (selectedGroupButton == btnGroupTerrain || selectedGroupButton == btnGroupFloors) {
            for (auto& tool : toolsButtons)
                tool->draw();
        }

        for (auto& btn : groupButtons)
            btn->draw();

        for (auto& btn : paletteButtons) {
            btn->draw();
        }

        buttonUp->draw();
        buttonDown->draw();
    }
};

Palette* palette = nullptr;

#endif