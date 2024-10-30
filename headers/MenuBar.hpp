#ifndef MenuBar_hpp
#define MenuBar_hpp

class OptionButton : public ButtonWithText {
public:
    CheckBox* checkbox;

    OptionButton(string text) : ButtonWithText(text) {

        this->position = position;
        checkbox = nullptr;
    }

    virtual void update(float dt) {
        ButtonWithText::update(dt);

        if (checkbox)
            checkbox->update(dt);
    }

    virtual void draw() {
        ButtonWithText::draw();
        if (checkbox)
            checkbox->draw();
    }
};

class MenuButton : public ButtonWithText {
public:
    std::vector < ButtonWithText* > options;
    bool isOpen;

    MenuButton(string text) : ButtonWithText(text) {
        isOpen = false;
        options.clear();
    }

    void addOption(ButtonWithText* btn) {

        options.push_back(btn);

        // width alignment
        float max_width = 0;

        for (auto& o : options) {
            float wdt = o->text.getLocalBounds().getSize().x + 2 * o->margin;
            
            if (dynamic_cast<OptionButton*>(o))
                wdt += o->rect.getSize().y;

            if (wdt > max_width)
                max_width = wdt;
        }

        // SET THE WIDTH FOR ANY BUTTON
        for (auto& o : options) {
            o->rect.setSize(sf::Vector2f(max_width, o->rect.getSize().y));
        }

        // positioning pos Y
        float pos_y = -screenHeight / 2;
        for (int i = 0; i < options.size(); i++) {
            float pos_y2 = rect.getSize().y;
            for (int j = 0; j < i; j++) {
                pos_y2 += options[j]->rect.getSize().y;
            }
            options[i]->setPosition(sf::Vector2f(position.x, pos_y + pos_y2));
        }

        // positioning checkboxes
        for (auto& o : options) {
            OptionButton* ob = dynamic_cast<OptionButton*>(o);
            if (ob != nullptr && ob->checkbox!=nullptr) {
                sf::Vector2f size = sf::Vector2f(o->rect.getSize().y, o->rect.getSize().y);
                sf::Vector2f pos2;
                pos2.x = position.x + max_width - size.x/2.0f;
                pos2.y = o->position.y + size.y/2.0f;
                ob->checkbox->edit(size, pos2);
            }
        }
        
    }

    virtual void update(float dt) {
        
        ButtonWithText::update(dt);


        
    }

    virtual void draw() {
        ButtonWithText::draw();

        if(isOpen)
            for (auto& o : options)
                o->draw();
    }
};

sf::Sprite logo;
sf::RectangleShape bar;

MenuButton* fileBtn;
MenuButton* renderBtn;
MenuButton* helpBtn;

ButtonWithText* newWorldBtn;
ButtonWithText* loadWorldBtn;
ButtonWithText* saveWorldBtn;

ButtonWithText* newBuildingBtn;
ButtonWithText* loadBuildingBtn;
ButtonWithText* saveBuildingBtn;

OptionButton* bordersBtn;
OptionButton* coordsBtn;
OptionButton* actionRangeBtn;
OptionButton* viewRangeBtn;
OptionButton* collidersBtn;
OptionButton* monsterBasesBtn;

ButtonWithText* instructionsMEBtn;
ButtonWithText* instructionsBEBtn;
ButtonWithText* aboutMEBtn;
ButtonWithText* aboutBEBtn;

std::vector < MenuButton* > menu;
MenuButton* clickedMenuButton;

void createMenuBar() {

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////

    sf::Vector2f barSize = sf::Vector2f(screenWidth, 30.0f);
    bar = sf::RectangleShape(barSize);
    bar.setPosition(cam->position.x - screenWidth / 2, cam->position.y - screenHeight / 2);
    bar.setFillColor(sf::Color(32, 32, 32));

    logo = sf::Sprite();
    logo.setTexture(*getTexture("GUI/icons/MapEditor_small_ico")->texture);
    logo.setPosition(-screenWidth / 2.0f + cam->position.x, -screenHeight/2.0f + cam->position.y);

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////

    sf::Vector2f position;

    fileBtn = new MenuButton("FILE");
    position.x = -screenWidth / 2 + logo.getLocalBounds().getSize().x;
    position.y = -screenHeight / 2;
    fileBtn->setPosition(position);
    fileBtn->func = []() {
        if (clickedMenuButton != nullptr)
            clickedMenuButton->isOpen = false;

        if (!fileBtn->isOpen) {
            fileBtn->isOpen = true;
            clickedMenuButton = fileBtn;
        }
        else
            fileBtn->isOpen = false;
        };

    renderBtn = new MenuButton("RENDER");
    position.x = -screenWidth / 2 + logo.getLocalBounds().getSize().x + fileBtn->rect.getLocalBounds().width;
    position.y = -screenHeight / 2;
    renderBtn->setPosition(position);
    renderBtn->func = []() {
        if (clickedMenuButton != nullptr)
            clickedMenuButton->isOpen = false;

        if (!renderBtn->isOpen) {
            renderBtn->isOpen = true;
            clickedMenuButton = renderBtn;
        }
        else
            renderBtn->isOpen = false;
        };

    helpBtn = new MenuButton("HELP");
    position.x = -screenWidth / 2 + logo.getLocalBounds().getSize().x + fileBtn->rect.getLocalBounds().width + renderBtn->rect.getLocalBounds().width;
    position.y = -screenHeight / 2;
    helpBtn->setPosition(position);
    helpBtn->func = []() {
        if (clickedMenuButton != nullptr)
            clickedMenuButton->isOpen = false;

        if (!helpBtn->isOpen) {
            helpBtn->isOpen = true;
            clickedMenuButton = helpBtn;
        }
        else
            helpBtn->isOpen = false;
        };


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////

    newWorldBtn = new ButtonWithText("New Map");
    newWorldBtn->func = []() {
        mapa = new Mapa();
        };

    loadWorldBtn = new ButtonWithText("Load Map");
    loadWorldBtn->func = []() {
        
        clickedMenuButton->isOpen = false;
        clickedMenuButton = nullptr;
        loadDialogBox = new OpenDialogBox("Load Map");
        };

    saveWorldBtn = new ButtonWithText("Save Map");
    saveWorldBtn->func = []() {
        // TO-DO
        mapa->save();
        };

    newBuildingBtn = new ButtonWithText("New Building");
    newBuildingBtn->func = []() {
        createNewBuilding();
        };

    loadBuildingBtn = new ButtonWithText("Load Building");
    loadBuildingBtn->func = []() {
        clickedMenuButton->isOpen = false;
        clickedMenuButton = nullptr;
        loadDialogBox = new OpenDialogBox("Load Building");
        };

    saveBuildingBtn = new ButtonWithText("Save Building");
    saveBuildingBtn->func = []() {
        saveBuildingToFile();
        };

    bordersBtn = new OptionButton("Map Borders");
    bordersBtn->checkbox = new CheckBox();
    bordersBtn->checkbox->value = renderBorders;
    bordersBtn->func = []() {
        (renderBorders) ? renderBorders = false : renderBorders = true;
        bordersBtn->checkbox->value = renderBorders;
        };

    coordsBtn = new OptionButton("Map Coords");
    coordsBtn->checkbox = new CheckBox();
    coordsBtn->checkbox->value = renderCoords;
    coordsBtn->func = []() {
        (renderCoords) ? renderCoords = false : renderCoords = true;
        coordsBtn->checkbox->value = renderCoords;
        };

    actionRangeBtn = new OptionButton("Action Range");
    actionRangeBtn->checkbox = new CheckBox();
    actionRangeBtn->checkbox->value = renderActionRange;
    actionRangeBtn->func = []() {
        (renderActionRange) ? renderActionRange = false : renderActionRange = true;
        actionRangeBtn->checkbox->value = renderActionRange;
        };

    viewRangeBtn = new OptionButton("View Range");
    viewRangeBtn->checkbox = new CheckBox();
    viewRangeBtn->checkbox->value = renderViewRange;
    viewRangeBtn->func = []() {
        (renderViewRange) ? renderViewRange = false : renderViewRange = true;
        viewRangeBtn->checkbox->value = renderViewRange;
        };

    collidersBtn = new OptionButton("Colliders");
    collidersBtn->checkbox = new CheckBox();
    collidersBtn->checkbox->value = renderColliders;
    collidersBtn->func = []() {
        (renderColliders) ? renderColliders = false : renderColliders = true;
        collidersBtn->checkbox->value = renderColliders;
        };

    monsterBasesBtn = new OptionButton("Monsters Bases");
    monsterBasesBtn->checkbox = new CheckBox();
    monsterBasesBtn->checkbox->value = renderMonsterBases;
    monsterBasesBtn->func = []() {
        (renderMonsterBases) ? renderMonsterBases = false : renderMonsterBases = true;
        monsterBasesBtn->checkbox->value = renderMonsterBases;
        };

    instructionsMEBtn = new ButtonWithText("Instructions");
    aboutMEBtn = new ButtonWithText("About");

    instructionsBEBtn = new ButtonWithText("Instructions");
    aboutBEBtn = new ButtonWithText("About");

    
}

void createMapEditorMenuBar() {
       
    createMenuBar();

    menu.clear();
    menu.push_back(fileBtn);
    menu.push_back(renderBtn);
    menu.push_back(helpBtn);

    menu[0]->addOption(newWorldBtn);
    menu[0]->addOption(loadWorldBtn);
    menu[0]->addOption(saveWorldBtn);

    menu[1]->addOption(bordersBtn);
    menu[1]->addOption(coordsBtn);
    menu[1]->addOption(actionRangeBtn);
    menu[1]->addOption(viewRangeBtn);
    menu[1]->addOption(collidersBtn);
    menu[1]->addOption(monsterBasesBtn);

    menu[2]->addOption(instructionsMEBtn);
    menu[2]->addOption(aboutMEBtn);

    clickedMenuButton = nullptr;
}

void createBuildingEditorMenuBar() {

    createMenuBar();

    menu.clear();
    menu.push_back(fileBtn);
    menu.push_back(renderBtn);
    menu.push_back(helpBtn);

    menu[0]->addOption(newBuildingBtn);
    menu[0]->addOption(loadBuildingBtn);
    menu[0]->addOption(saveBuildingBtn);

    menu[1]->addOption(collidersBtn);

    menu[2]->addOption(instructionsBEBtn);
    menu[2]->addOption(aboutBEBtn);

    clickedMenuButton = nullptr;
}

void updateMenuBar() {

	bar.setPosition( -screenWidth / 2.0f + cam->position.x, -screenHeight / 2.0f + cam->position.y);
    logo.setPosition(-screenWidth / 2.0f + cam->position.x, -screenHeight / 2.0f + cam->position.y);

    for (auto& m : menu)
        m->update(dt);

    if (clickedMenuButton) {

        for (auto& o : clickedMenuButton->options)
            o->update(dt);
            
    }
}

void drawMenuBar() {

	window->draw(bar);
    window->draw(logo);

    for (auto& m : menu)
        m->draw();

    

}

#endif