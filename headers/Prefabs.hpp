#ifndef Prefabs_hpp
#define Prefabs_hpp

std::vector < GameObject* > prefabs;

GameObject* getPrefab(string name) {
    for (auto& go : prefabs) {
        if (go->name == name)
            return go;
    }

    std::cout << "error - get Prefab - Prefab: \"" << name << "\" not exists\n";
    return nullptr;
}

void loadPrefabs() {

    prefabs.clear();
 
    // TREES
    // name, radius, width, height
    prefabs.push_back(new Nature("natures/tree1", 36, 18, 145));
    prefabs.push_back(new Nature("natures/tree2", 44, 22, 185));
    prefabs.push_back(new Nature("natures/tree3", 36, 18, 145));
    prefabs.push_back(new Nature("natures/tree4", 40, 20, 185));

    prefabs.push_back(new Nature("natures/tree5", 36, 18, 145));
    prefabs.push_back(new Nature("natures/tree6", 50, 25, 185));
    prefabs.push_back(new Nature("natures/tree7", 36, 18, 145));
    prefabs.push_back(new Nature("natures/tree8", 50, 25, 185));
    prefabs.push_back(new Nature("natures/tree9", 50, 25, 185));


    prefabs.push_back(new Nature("natures/bush1", 110, 55, 75));

    // ROCKS
    // name, radius, width, height
    prefabs.push_back(new Nature("natures/rocks1", 90, 45, 65));
    prefabs.push_back(new Nature("natures/rocks2", 90, 45, 65));
    prefabs.push_back(new Nature("natures/rocks3", 90, 45, 57));

    // FURNITURES - TO-DO - heights
    prefabs.push_back(new Furniture("furnitures/table", 60, 26, 36));
    prefabs.push_back(new Furniture("furnitures/bench", 60, 26, 36));
    prefabs.push_back(new Furniture("furnitures/chest", 60, 26, 36));
    prefabs.push_back(new Furniture("furnitures/wardrobe", 64, 32, 60));
    prefabs.push_back(new Furniture("furnitures/bookshelf", 64, 32, 60));
    prefabs.push_back(new Furniture("furnitures/furnace", 60, 26, 60));
    prefabs.push_back(new Furniture("furnitures/bed", 64, 32, 60));
    prefabs.push_back(new Furniture("furnitures/chair", 16, 16, 24));
    prefabs.push_back(new Furniture("furnitures/barrel", 16, 16, 24));
    prefabs.push_back(new Furniture("furnitures/lectern", 24, 16, 40));

    // WALLS
    Wall* wall = new Wall("walls/empty_wall", 32, 32, 32);
    prefabs.push_back(wall);

    std::vector < string > walls_names;
    walls_names.push_back("walls/mud_wall");
    walls_names.push_back("walls/stone_wall");
    walls_names.push_back("walls/wooden_wall");

    for (auto& texture : textures) {
        for (auto& name : walls_names) {
            if (texture->name.find(name) != std::string::npos) {
                Wall* wall = new Wall(texture->name, 32, 32, 32);
                prefabs.push_back(wall);
                //cout << "created prefab: " << wall->name << "\n";
            }
        }
    }

    // PATHS
    prefabs.push_back(new Path("paths/stonepath1", 64, 32, 32));
    prefabs.push_back(new Path("paths/stonepath2", 64, 32, 32));

    // DOORS
    prefabs.push_back(new Door("doors/door_0"));

    // ITEMS
    for (auto& i : items) {
        prefabs.push_back(new ItemOnMap(i, 0, 0));
    }

    // CHARACTERS
    // name, bodySet

    Character* character = nullptr;

    character = new Character("characters/jack", "sets/body/man-blackhaired");
    character->dialogue = getDialogue(1);
    character->armor = getItem("items/skin jacket");
    character->pants = getItem("items/wool pants");
    character->helmet = getItem("items/wool helmet");
    character->rightHand = getItem("items/sword");
    character->leftHand = getItem("items/shield");
    prefabs.push_back(character);

    character = new Character("characters/john", "sets/body/boy-brownhaired");
    character->armor = getItem("items/wool shirt");
    character->pants = getItem("items/wool pants");
    character->helmet = getItem("items/wool helmet");
    prefabs.push_back(character);

    character = new Character("characters/peter", "sets/body/boy-brownhaired");
    character->armor = getItem("items/wool shirt");
    character->pants = getItem("items/wool pants");
    character->helmet = getItem("items/wool helmet");
    prefabs.push_back(character);

    character = new Character("characters/pit", "sets/body/boy-brownhaired");
    character->dialogue = getDialogue(5);
    character->armor = getItem("items/wool shirt");
    character->pants = getItem("items/wool pants");
    character->helmet = getItem("items/wool helmet");
    prefabs.push_back(character);


    // MONSTERS TO-DO - heights

    Monster* dziobak = new Monster("monsters/dziobak", 72, 36, 50, 10);
    dziobak->HP = 40;
    dziobak->HP_FULL = 40;
    dziobak->MP = 10;
    dziobak->MP_FULL = 10;
    dziobak->STRENGTH = 2;
    dziobak->DEXTERITY = 2;
    dziobak->INTELLIGENCE = 1;
    prefabs.push_back(dziobak);

    Monster* goblin = new Monster("monsters/goblin", 32, 16, 50, 20);
    goblin->HP = 80;
    goblin->HP_FULL = 80;
    goblin->MP = 10;
    goblin->MP_FULL = 10;
    goblin->STRENGTH = 8;
    goblin->DEXTERITY = 4;
    goblin->INTELLIGENCE = 2;
    prefabs.push_back(goblin);

    Monster* wilczur = new Monster("monsters/wilczur", 70, 35, 60, 50);
    wilczur->HP = 120;
    wilczur->HP_FULL = 120;
    wilczur->MP = 10;
    wilczur->MP_FULL = 10;
    wilczur->STRENGTH = 12;
    wilczur->DEXTERITY = 6;
    wilczur->INTELLIGENCE = 3;
    prefabs.push_back(wilczur);

    Monster* jaszczur = new Monster("monsters/jaszczur", 70, 35, 50, 80);
    jaszczur->HP = 160;
    jaszczur->HP_FULL = 160;
    jaszczur->MP = 10;
    jaszczur->MP_FULL = 10;
    jaszczur->STRENGTH = 16;
    jaszczur->DEXTERITY = 8;
    jaszczur->INTELLIGENCE = 4;
    prefabs.push_back(jaszczur);

    Monster* niedzwiedz = new Monster("monsters/niedzwiedz", 70, 35, 75, 80);
    niedzwiedz->HP = 160;
    niedzwiedz->HP_FULL = 160;
    niedzwiedz->MP = 10;
    niedzwiedz->MP_FULL = 10;
    niedzwiedz->STRENGTH = 16;
    niedzwiedz->DEXTERITY = 8;
    niedzwiedz->INTELLIGENCE = 4;
    prefabs.push_back(niedzwiedz);

    Monster* szpon = new Monster("monsters/szpon", 66, 32, 75, 100);
    szpon->HP = 200;
    szpon->HP_FULL = 200;
    szpon->MP = 10;
    szpon->MP_FULL = 10;
    szpon->STRENGTH = 20;
    szpon->DEXTERITY = 10;
    szpon->INTELLIGENCE = 5;
    prefabs.push_back(szpon);

    Monster* kolcorozec = new Monster("monsters/kolcorozec", 70, 35, 70, 140);
    kolcorozec->HP = 240;
    kolcorozec->HP_FULL = 240;
    kolcorozec->MP = 10;
    kolcorozec->MP_FULL = 10;
    kolcorozec->STRENGTH = 24;
    kolcorozec->DEXTERITY = 12;
    kolcorozec->INTELLIGENCE = 6;
    prefabs.push_back(kolcorozec);

    Monster* golem = new Monster("monsters/golem", 90, 60, 80, 180);
    golem->HP = 280;
    golem->HP_FULL = 280;
    golem->MP = 10;
    golem->MP_FULL = 10;
    golem->STRENGTH = 28;
    golem->DEXTERITY = 14;
    golem->INTELLIGENCE = 7;
    prefabs.push_back(golem);

    Monster* troll = new Monster("monsters/troll", 90, 60, 85, 240);
    troll->HP = 320;
    troll->HP_FULL = 320;
    troll->MP = 10;
    troll->MP_FULL = 10;
    troll->STRENGTH = 32;
    troll->DEXTERITY = 16;
    troll->INTELLIGENCE = 8;
    prefabs.push_back(troll);

    Monster* bies = new Monster("monsters/bies", 90, 60, 85, 300);
    bies->HP = 360;
    bies->HP_FULL = 360;
    bies->MP = 10;
    bies->MP_FULL = 10;
    bies->STRENGTH = 36;
    bies->DEXTERITY = 18;
    bies->INTELLIGENCE = 9;
    prefabs.push_back(bies);
}



#endif
