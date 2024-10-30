﻿#ifndef Monsters_hpp
#define Monsters_hpp

class Monster : public Unit {
public:

	bool isAlive;
	sf::Vector2f base;
	sf::Time deathTime;
	short EXPERIENCE;
	std::vector < Point > path;
	std::vector < sf::CircleShape > pathpoints;

	Monster(string name, float width, float length, float height, short EXP) : Unit(name, name, width, length, height) {
		type = GameObjectType::Monster;
		direction = 2;
		isAlive = true;
		base = position;	
		this->EXPERIENCE = EXP;
		
		path.clear();
		pathpoints.clear();

		loadTextures();
		

	}

	Monster(GameObject* object, float x, float y) : Unit(object, x, y) {
		type = GameObjectType::Monster;
		direction = 2;
		isAlive = true;
		base = position;
		this->EXPERIENCE = dynamic_cast<Monster*>(object)->EXPERIENCE;

		path.clear();
		pathpoints.clear();

		loadTextures();
	}

	virtual ~Monster() {

	}

	void loadTextures() {

		for (short i = 0; i < 4; i++) {

			attackTextures[i] = getTexture(name + "/attackTop" + to_string(i));
			attackTextures[4 + i] = getTexture(name + "/attackRight" + to_string(i));
			attackTextures[8 + i] = getTexture(name + "/attackBottom" + to_string(i));
			attackTextures[12 + i] = getTexture(name + "/attackLeft" + to_string(i));

			idleTextures[i] = getTexture(name + "/idleTop" + to_string(i));
			idleTextures[4 + i] = getTexture(name + "/idleRight" + to_string(i));
			idleTextures[8 + i] = getTexture(name + "/idleBottom" + to_string(i));
			idleTextures[12 + i] = getTexture(name + "/idleLeft" + to_string(i));

			runTextures[i] = getTexture(name + "/runTop" + to_string(i));
			runTextures[4 + i] = getTexture(name + "/runRight" + to_string(i));
			runTextures[8 + i] = getTexture(name + "/runBottom" + to_string(i));
			runTextures[12 + i] = getTexture(name + "/runLeft" + to_string(i));

		}

		sprite = sf::Sprite();
		sprite.setOrigin(idleTextures[0]->cx, idleTextures[0]->cy);
	}

	void dropLoot() {

		Inventory* loot = new Inventory();
		// TO-DO
		if (name == "monsters/wilczur") {
			loot->addItem("items/raw meat");
			loot->addItem("items/tooth", 1);
			loot->addItem("items/wolf skin");
		}
		
		if (name == "monsters/dziobak") {
			loot->addItem("items/raw meat", 2);
		}

		if (name == "monsters/goblin") {
			loot->addItem("items/wooden club", 1);
		}

		if (name == "monsters/troll") {
			
		}

		if (name == "monsters/bies") {

		}

		if (name == "monsters/kolcorozec") {
			loot->addItem("items/tooth", 1);
			loot->addItem("items/spike", 1);
		}

		if (loot->items.size() > 0) {
			InventoryOnMap* bag = new InventoryOnMap(loot, position.x, position.y);
			bag->isVisible = true;
			gameObjects.push_back(bag);
			inventoriesOnMap.push_back(bag);
		}

	}

	void loadTheTarget() {
		do {
			target.x = base.x + (rand() % 32 - 16)*16;
			target.y = base.y + (rand() % 32 - 16)*16;
		} while (collisionPrediction(this, target.x - position.x, target.y - position.y));

		//cout << "Load the target: ["<<target.x<<","<<target.y<<"]\n";
	}

	void loadThePath() {

		Point goal = Point(target.x, target.y);

		path = aStar(this, goal);
		//cout << "position: [" << position.x << "," << position.y << "]\n";
		//cout << "path(" << path.size() << ") : ";
		/*
		for (auto& p : path)
			cout <<"["<<p.x << "," << p.y << "] ";

		cout << "\n";
		*/
	}

	void followThePath(float dt) {

		float dist = 15.0f * 4.0f * dt;	// distance to move

		if (position == target) {
			
			//cout << "\nmonster: " << name << "\n";
			loadTheTarget();
			//sf::Time starttime = currentTime;
			loadThePath();
			//cout<<"time: " << (timeClock.getElapsedTime() - starttime).asSeconds() << "s\n";
		}
		else if (position.x != target.x && fabs(target.x - position.x) < dist) {
			position.x = target.x;
		}
		else if (position.y != target.y && fabs(target.y - position.y) < dist) {
			position.y = target.y;
		}
		else {
			if (path.size() > 0) {
				if (position.x == path[0].x && position.y == path[0].y) {
					path.erase(path.begin());
				}
				else if (position.x != path[0].x && fabs(path[0].x - position.x) < dist) {
					position.x = path[0].x;
				}
				else if (position.y != path[0].y && fabs(path[0].y - position.y) < dist) {
					position.y = path[0].y;
				}
				else if (path[0].x < position.x) {
					position.x -= dist;
					direction = 3;
				}
				else if (path[0].x > position.x) {
					position.x += dist;
					direction = 1;
				}
				else if (path[0].y < position.y) {
					position.y -= dist;
					direction = 0;
				}
				else if (path[0].y > position.y) {
					position.y += dist;
					direction = 2;
				}
			}
		}

	}

	void idle(float dt) {
		if (rand() % 300 == 0) {
			state = unitStates::run;
			target.x = base.x + rand() % 256 - 128;
			target.y = base.y + rand() % 256 - 128;
		}

		calculateCurrentFrame(dt);
		sprite.setTexture(*idleTextures[direction * 4 + frame]->texture);
	}

	void run(float dt) {

		if (path.size() == 0) {
			
			//cout << "\nmonster: " << name << "\n";
			loadTheTarget();
			//sf::Time starttime = currentTime;
			loadThePath();
			//cout << "time: " << (timeClock.getElapsedTime() - starttime).asSeconds() << "s\n";
		}

		followThePath(dt);

		calculateCurrentFrame(dt);
		sprite.setTexture(*runTextures[direction * 4 + frame]->texture);
	}

	virtual void update(float dt) {


		if (HP == 0 && isAlive == true) {
			
			// death
			dropLoot();
			player->gainEXP(EXPERIENCE);
			isAlive = false;
			collisioning = false;
			deathTime = currentTime;
		}
		else if (isAlive == false) {
			
			// resurrection
			if ( (currentTime-deathTime).asSeconds() > 20) {
				isAlive = true;
				collisioning = true;
				HP = HP_FULL;
				state = unitStates::idle;

				while (collisionPrediction(this, 0, 0)) {

					position.x = rand() % 256 - 128 + base.x;
					position.y = rand() % 256 - 128 + base.y;
				}
			}

		}
		
		if( isAlive == true) {

			if (playerInActionRange()) {
				state = unitStates::attack;
			}
			else if (playerInViewRange()) {
				target = player->position;
				state = unitStates::run;
			}

			if (state == unitStates::idle) {
				idle(dt);
			}
			else if (state == unitStates::run) {
				run(dt);
			}
			else if (state == unitStates::attack) {
				attack(dt);
			}

			if (cooldown > 0.0f)
				cooldown -= dt;

			sprite.setPosition(position);

			setLifeBar();
			createTextname();
		}

	}

	virtual void updateStatistic(float dt) {
		
		Unit::updateStatistic(dt);

		if (collisionPrediction(this, 0, 0))
			collider->shape->setFillColor(sf::Color::Red);
		else
			collider->shape->setFillColor(sf::Color(128, 64, 128, 96));
		
		viewRangeArea.setPosition(position);
		actionRangeArea.setPosition(position);

		// PATH

		pathpoints.clear();
		for (auto& p : path) {
			sf::CircleShape point = sf::CircleShape(4);
			point.setFillColor(sf::Color::Red);
			point.setOrigin(4, 4);
			point.setPosition(p.x, p.y);
			pathpoints.push_back(point);
		}
	}

	virtual void draw() {

		if (isAlive) {

			window->draw(sprite);
			window->draw(lifeBarBackground);
			window->draw(lifeBar);

			Unit::draw();
		}
	}

	virtual void drawStatistics() {
		

		if(renderViewRange)
			window->draw(viewRangeArea);
		
		if(renderActionRange)
			window->draw(actionRangeArea);
		
		if (renderMonsterBases) {
			for (auto& p : pathpoints)
				window->draw(p);

			sf::CircleShape meta(8);
			meta.setFillColor(sf::Color::Blue);
			meta.setOrigin(8, 8);
			meta.setPosition(target.x, target.y);
			window->draw(meta);
		}

		Unit::drawStatistics();
	}

	virtual void drawAllStatistics() {
		
		for (auto& p : pathpoints)
			window->draw(p);

		sf::CircleShape meta(8);
		meta.setFillColor(sf::Color::Blue);
		meta.setOrigin(8, 8);
		meta.setPosition(target.x, target.y);
		window->draw(meta);

		Unit::drawAllStatistics();
	}
};

std::vector < Monster* > monsters;
#endif