#ifndef MapEditor_hpp
#define MapEditor_hpp

enum class mapEditorStates { start, editor };
mapEditorStates mapEditorState;

bool showStatistics = false;

void painterUpdate();
void painterDraw();
void addPrefabToLists();
void editTiles();
void MapEditorUnclickButtons();
void MapEditorHoverButtons();
void MapEditorEventLeftClick();
void MapEditorEventRightClick();

void MapEditor() {

    window->setTitle("Map Editor");

    // load the icon for windows
    sf::Image ico;
    ico.loadFromFile("assets/logo/MapEditorLogo.png");
    window->setIcon(64, 64, ico.getPixelsPtr());

    // create sf::View
    cam = new Camera();
    window->setView(cam->view);

    // start screen
    mapEditorState = mapEditorStates::start;

    sf::Text* welcomeText = new sf::Text("Map Editor", basicFont, 32);
    welcomeText->setFillColor(titleColor);
    welcomeText->setOrigin(welcomeText->getLocalBounds().width / 2.f, welcomeText->getLocalBounds().height / 2.f);
    welcomeText->setPosition(screenWidth / 2.0f, screenHeight / 2.0f - 50);

    sf::Text* pressText = new sf::Text("press Spacebar to start", basicFont, 16);
    pressText->setFillColor(titleColor);
    pressText->setOrigin(pressText->getLocalBounds().width / 2.f, pressText->getLocalBounds().height / 2.f);
    pressText->setPosition(screenWidth / 2.0f, screenHeight / 2.0f + 50);

    bool skip = false;
    while (window->isOpen() && skip == false) {
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                skip = true;
                break;
            }
        }
            window->setView(cam->view);
            welcomeText->setPosition(cam->position.x, cam->position.y - 50);
            pressText->setPosition(cam->position.x, cam->position.y + 50);

            window->clear(sf::Color::Black);
            window->draw(*welcomeText);
            window->draw(*pressText);
            window->display();
        
    }
    
    mapEditorState = mapEditorStates::editor;

    loadDialogBox = nullptr;

    prefabToPaint = nullptr;
    selectedGameObjects.clear();
    selection_state = false;

    createMapEditorMenuBar();
    palette = new Palette(PaletteType::MapEditor);

    mapa = new Mapa();
    mapa->load();

    //cam->setPosition(screenWidth/2.0f, screenHeight/2.0f);

    updateGameObjects();

    while (window->isOpen()) {

        prevTime = currentTime;
        currentTime = timeClock.getElapsedTime();
        dt = currentTime.asSeconds() - prevTime.asSeconds();

        mousePosition = sf::Mouse::getPosition(*window);	// Pobierz aktualną pozycję myszy względem bieżącego okna
        worldMousePosition = window->mapPixelToCoords(mousePosition);

        GUIwasHover = false;
        GUIwasClicked = false;

        if (loadDialogBox == nullptr) {
            if (clickedMenuButton == nullptr) {
                palette->unclickButtons();
                palette->hoverButtons();
            }

            MapEditorUnclickButtons();
            MapEditorHoverButtons();
        }

        // events
        sf::Event event;
        while (window->pollEvent(event)) {

            if (event.type == sf::Event::Closed) {
                window->close();
            }

            if (loadDialogBox) {
                loadDialogBox->update(event, dt);

                if (loadDialogBox->fileSelected) {
                    mapa->load(loadDialogBox->getPathfile());
                    delete loadDialogBox;
                    loadDialogBox = nullptr;
                }
            }

            if (event.type == sf::Event::MouseButtonReleased) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    
                    if (loadDialogBox == nullptr) {
                        
                        MapEditorEventLeftClick();

                        if (tool == toolType::Cursor || tool == toolType::Rectangle || tool == toolType::Elipse) {
                            selection_state = false;
                        }
                    }

                }

                if (event.mouseButton.button == sf::Mouse::Right) {
                    if (loadDialogBox == nullptr) {
                        MapEditorEventRightClick();
                    }
                }
            }
                
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {

                    if (loadDialogBox == nullptr) {
                        if (GUIwasHover != true) {
                            if (clickedMenuButton == nullptr) {
                                startMousePosition = sf::Mouse::getPosition(*window);
                                startWorldMousePosition = window->mapPixelToCoords(mousePosition);

                                if (tool == toolType::Cursor || tool == toolType::Rectangle || tool == toolType::Elipse) {
                                    selection_state = true;
                                }
                            }
                        }
                    }
                    
                }
            }

            if (event.type == sf::Event::KeyPressed) {
                    
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                    if (loadDialogBox == nullptr) {
                        window->close();
                        exit(0);
                    }
                    else {
                        delete loadDialogBox;
                        loadDialogBox = nullptr;
                    }
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::F5)) {
                    // TO-DO
                    if (loadDialogBox == nullptr) {
                        mapa->save();
                    }
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::F6)) {
                    mapa->load();
                    /*
                    if (loadDialogBox == nullptr) {
                        loadDialogBox = new OpenDialogBox("Load Map");
                    }
                    */
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                    // DO NOTHING
                }

            }
        } // events

        

        if (loadDialogBox == nullptr) {
            float moveSpeed = 300.0f * dt;
            // moving the view
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                cam->move(0.0f, -moveSpeed);

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                cam->move(0.0f, moveSpeed);

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                cam->move(-moveSpeed, 0.0f);

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                cam->move(moveSpeed, 0.0f);

            // drawing a terrain
            if (!GUIwasHover) {
                if (prefabToPaint != nullptr) {

                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                        if (clickedMenuButton == nullptr) {
                            if (tool == toolType::Brush || tool == toolType::RectBrush) {
                                if (prefabToPaint->type == GameObjectType::Terrain)
                                    editTiles();
                            }
                        }

                    }
                }

            }
        }


        // UPDATE ////////////////////////////////////////////////////////////////////////
        mapa->mapVisiblings();

        updateShaders();
        mapa->update();

        for (auto& go : gameObjects)
            if(visiblings(go))
                go->updateStatistic(dt);


        cam->update();
        updateGameObjects();
        sortGameObjects();

        if (loadDialogBox == nullptr) {
            updateMenuBar();
            palette->update(dt);
            painterUpdate();
        }
        

        // RENDER ////////////////////////////////////////////////////////////////////////////

        window->clear(sf::Color(64, 128, 64));
        window->setView(cam->view);

        mapa->draw();
        mapa->drawStatistics();

        for (auto& building : buildings) {
            window->draw(*building->floors);
            building->draw();
        }


        
        for (auto& go : gameObjects) {
            if (visiblings(go)) {
                if (go->mouseIsHover || go->isSelected) {
                    // Obiekt jest najechany kursorem lub zaznaczony - rysuj wszystkie statystyki
                    go->drawAllStatistics();
                }
                else {
                    // Obiekt nie jest najechany ani zaznaczony - rysuj tylko wymagane statystyki
                    go->drawStatistics();
                }
            }
        }

        drawGameObjects();
        painterDraw();
        drawMenuBar();
        palette->draw();
        if (loadDialogBox != nullptr)
            loadDialogBox->draw();
        window->display();
    }

    delete window;
}



void editTiles() {

    for(auto& prefab : prefabsToPaint) {

        if (prefab->type == GameObjectType::Terrain) {
            
            TerrainPrefab* tp = dynamic_cast<TerrainPrefab*>(prefab);
            //cout << prefab->position.x << ", " << prefab->position.y << "\n";

            Chunk* chunk = mapa->getChunk(tp->position);
            if (chunk != nullptr) {

                // TO-DO
                if (tp->name == "tiles/tile_0_grass") {
                    chunk->terrain->edit(tp->position, 0);
                    chunk->water->edit(tp->position, false);
                }

                if (tp->name == "tiles/tile_1_sands") {
                    chunk->terrain->edit(tp->position, 1);
                    chunk->water->edit(tp->position, false);
                }
                    
                if (tp->name == "tiles/tile_2_water") {
                    chunk->terrain->edit(tp->position, 2);
                    chunk->water->edit(tp->position, true);
                }
                    
                if (tp->name == "tiles/tile_3_gravel") {
                    chunk->terrain->edit(tp->position, 3);
                    chunk->water->edit(tp->position, false);
                }

                if (tp->name == "tiles/tile_4_beach") {
                    chunk->terrain->edit(tp->position, 4);
                    chunk->water->edit(tp->position, false);
                }

                //
            }
        }
    }
    
    mapa->generateBorders();
    
}

void MapEditorUnclickButtons() {

    for (auto& m : menu) {
        m->unclick();

        if (m->isOpen) {
            for (auto& o : m->options)
                o->unclick();
        }
    }

}

void MapEditorHoverButtons() {

    for (auto& m : menu) {
        m->hover();

        if (m->isOpen) {
            for (auto& o : m->options)
                o->hover();
        }
    }

}

void MapEditorEventLeftClick() {

    if (clickedMenuButton != nullptr) {
        bool clickOnMenu = false;

        for (auto& m : menu) {

            if (m->click())
                clickOnMenu = true;

            if (m->isOpen) {
                for (auto& o : m->options)
                    if (o->click())
                        clickOnMenu = true;
            }
        }

        if (clickOnMenu == false) {
            clickedMenuButton->isOpen = false;
            clickedMenuButton = nullptr;
        }
            
    }
    else {

        for (auto& m : menu) {
            if (m->click())
                tool = toolType::Cursor;
        }

        palette->clickButtons();

        if (!GUIwasHover) {

            if (tool == toolType::Cursor) {

                float x = selectArea.getPosition().x;
                float y = selectArea.getPosition().y;
                float w = selectArea.getSize().x;
                float h = selectArea.getSize().y;

                if (w < 16) w = 16;
                if (h < 16) h = 16;

                selectGameObjects(x, y, w, h);

            }

            if (!prefabsToPaint.empty()) {

                if (tool == toolType::AddGameObject) {
                    addPrefabsToMapAndLists();
                }

                if (tool == toolType::Rectangle || tool == toolType::Elipse) {
                    editTiles();
                }
            }

        }
    }   // CLICKED MENU BUTTON
}

void MapEditorEventRightClick() {
    
    if (clickedMenuButton != nullptr) {
        clickedMenuButton->isOpen = false;
        clickedMenuButton = nullptr;

    }else if (prefabToPaint == nullptr) {

        if (!selectedGameObjects.empty()) {
            selectGameObjects(0, 0, 0, 0);
            return;
        }

        bool was_delete = false;

        ////////////////////////////////////////////////////////
        
        for (auto it = buildings.begin(); it != buildings.end(); ) {
            Building* b = *it;

            if (b->mouseIsHover == true) {

                sf::Vector2f pos;
                pos.x = b->position.x;
                pos.y = b->position.y;

                Chunk* chunk = mapa->getChunk(pos);  // erase
                if (chunk != nullptr) {
                    cout << "chunk selected\n";
                    deleteGameObjectFromMainLists(b);
                    chunk->removeGameObject(b);
                    delete b;
                    was_delete = true;
                    break;
                }
                    


                
            }
            else
                ++it;
        }
       
        if (was_delete == false) {
            for (auto it = gameObjects.begin(); it != gameObjects.end(); ) {
                GameObject* go = *it;

                if (go->type != GameObjectType::Building && go->mouseIsHover == true) {

                    Chunk* chunk = mapa->getChunk(go->position);  
                    if (chunk != nullptr) {
                        deleteGameObjectFromMainLists(go);  // erase
                        chunk->removeGameObject(go);    // erase
                        delete go;      // delete
                        was_delete = true;
                        break;
                    }
                }
                else
                    ++it;
            }
        }


        

    }
    else {
        palette->selectedPaletteButton = nullptr;
        palette->selectedToolButton = palette->btnToolsCursor;
        tool = toolType::Cursor;
        prefabToPaint = nullptr;

    }
}
#endif