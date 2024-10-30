#ifndef Character_hpp
#define Character_hpp

class Character : public Unit {
public:

	// EQUIPMENT
	Item* helmet;
	Item* armor;
	Item* pants;
	Item* leftHand;
	Item* rightHand;

	// HELMET - textures
	Texture* helmetIdleTextures[16];
	Texture* helmetRunTextures[16];
	Texture* helmetAttackTextures[16];

	// ARMOR - textures
	Texture* armorIdleTextures[16];
	Texture* armorRunTextures[16];
	Texture* armorAttackTextures[16];

	// PANTS - textures
	Texture* pantsIdleTextures[16];
	Texture* pantsRunTextures[16];
	Texture* pantsAttackTextures[16];

	// LEFT HAND - textures
	Texture* leftHandIdleTextures[16];
	Texture* leftHandRunTextures[16];
	Texture* leftHandAttackTextures[16];

	// RIGHT HAND - textures
	Texture* rightHandIdleTextures[16];
	Texture* rightHandRunTextures[16];
	Texture* rightHandAttackTextures[16];

	// SPRITES
	sf::Sprite helmetSprite;
	sf::Sprite armorSprite;
	sf::Sprite pantsSprite;
	sf::Sprite leftHandSprite;
	sf::Sprite rightHandSprite;
	
	Dialogue* dialogue;

	Texture* talkWithTexture;
	sf::Sprite talkWithSprite;
	bool showHand;


	Character(string name, string bodySet="sets/body/hero") : Unit(name, bodySet, 36, 18, 64) {
		
		type = GameObjectType::Character;
		
		helmet = nullptr;
		armor = nullptr;
		pants = nullptr;
		leftHand = nullptr;
		rightHand = nullptr;

		loadBody();
		loadHelmet();
		loadArmor();
		loadPants();
		loadLeftHand();
		loadRightHand();

		dialogue = nullptr;

		talkWithTexture = getTexture("GUI/talk");
		talkWithSprite = sf::Sprite();
		talkWithSprite.setTexture(*talkWithTexture->texture);
		talkWithSprite.setOrigin(talkWithTexture->cx, talkWithTexture->cy);
		showHand = false;

	}

	Character(GameObject* object, float x, float y) : Unit(object, x, y) {
		
		type = GameObjectType::Character;
				
		helmet = dynamic_cast <Character*>(object)->helmet;
		armor = dynamic_cast <Character*>(object)->armor;
		pants = dynamic_cast <Character*>(object)->pants;
		leftHand = dynamic_cast <Character*>(object)->leftHand;
		rightHand = dynamic_cast <Character*>(object)->rightHand;

		loadBody();
		loadHelmet();
		loadArmor();
		loadPants();
		loadLeftHand();
		loadRightHand();
		
		dialogue = dynamic_cast <Character*>(object)->dialogue;

		talkWithTexture = getTexture("GUI/talk");
		talkWithSprite = sf::Sprite();
		talkWithSprite.setTexture(*talkWithTexture->texture);
		talkWithSprite.setOrigin(talkWithTexture->cx, talkWithTexture->cy);
		showHand = false;
	}

	virtual ~Character() {
		
	}

	void loadBody() {
		for (short i = 0; i < 16; i++) {
			idleTextures[i] = nullptr;
			runTextures[i] = nullptr;
			attackTextures[i] = nullptr;

		}

		for (short i = 0; i < 4; i++) {

			idleTextures[i] = getTexture(bodySet + "/idleTop" + to_string(i));
			idleTextures[4 + i] = getTexture(bodySet + "/idleRight" + to_string(i));
			idleTextures[8 + i] = getTexture(bodySet + "/idleBottom" + to_string(i));
			idleTextures[12 + i] = getTexture(bodySet + "/idleLeft" + to_string(i));

			runTextures[i] = getTexture(bodySet + "/runTop" + to_string(i));
			runTextures[4 + i] = getTexture(bodySet + "/runRight" + to_string(i));
			runTextures[8 + i] = getTexture(bodySet + "/runBottom" + to_string(i));
			runTextures[12 + i] = getTexture(bodySet + "/runLeft" + to_string(i));

			attackTextures[i] = getTexture(bodySet + "/attackTop" + to_string(i));
			attackTextures[4 + i] = getTexture(bodySet + "/attackRight" + to_string(i));
			attackTextures[8 + i] = getTexture(bodySet + "/attackBottom" + to_string(i));
			attackTextures[12 + i] = getTexture(bodySet + "/attackLeft" + to_string(i));

		}

		sprite = sf::Sprite();
		sprite.setOrigin(32, 58);

	}


	void loadHelmet() {

		for (short i = 0; i < 16; i++) {
			helmetIdleTextures[i] = nullptr;
			helmetRunTextures[i] = nullptr;
			helmetAttackTextures[i] = nullptr;

		}

		if (helmet != nullptr) {

			for (short i = 0; i < 4; i++) {
				helmetIdleTextures[i] = getTexture("sets/" + helmet->name + "/idleTop" + to_string(i));
				helmetIdleTextures[4 + i] = getTexture("sets/" + helmet->name + "/idleRight" + to_string(i));
				helmetIdleTextures[8 + i] = getTexture("sets/" + helmet->name + "/idleBottom" + to_string(i));
				helmetIdleTextures[12 + i] = getTexture("sets/" + helmet->name + "/idleLeft" + to_string(i));

				helmetRunTextures[i] = getTexture("sets/" + helmet->name + "/runTop" + to_string(i));
				helmetRunTextures[4 + i] = getTexture("sets/" + helmet->name + "/runRight" + to_string(i));
				helmetRunTextures[8 + i] = getTexture("sets/" + helmet->name + "/runBottom" + to_string(i));
				helmetRunTextures[12 + i] = getTexture("sets/" + helmet->name + "/runLeft" + to_string(i));

				helmetAttackTextures[i] = getTexture("sets/" + helmet->name + "/attackTop" + to_string(i));
				helmetAttackTextures[4 + i] = getTexture("sets/" + helmet->name + "/attackRight" + to_string(i));
				helmetAttackTextures[8 + i] = getTexture("sets/" + helmet->name + "/attackBottom" + to_string(i));
				helmetAttackTextures[12 + i] = getTexture("sets/" + helmet->name + "/attackLeft" + to_string(i));

			}
		}

		helmetSprite = sf::Sprite();
		helmetSprite.setOrigin(32, 58);

	}

	void loadArmor() {

		for (short i = 0; i < 16; i++) {
			armorIdleTextures[i] = nullptr;
			armorRunTextures[i] = nullptr;
			armorAttackTextures[i] = nullptr;

		}

		if (armor != nullptr) {

			for (short i = 0; i < 4; i++) {
				armorIdleTextures[i] = getTexture("sets/" + armor->name + "/idleTop" + to_string(i));
				armorIdleTextures[4 + i] = getTexture("sets/" + armor->name + "/idleRight" + to_string(i));
				armorIdleTextures[8 + i] = getTexture("sets/" + armor->name + "/idleBottom" + to_string(i));
				armorIdleTextures[12 + i] = getTexture("sets/" + armor->name + "/idleLeft" + to_string(i));

				armorRunTextures[i] = getTexture("sets/" + armor->name + "/runTop" + to_string(i));
				armorRunTextures[4 + i] = getTexture("sets/" + armor->name + "/runRight" + to_string(i));
				armorRunTextures[8 + i] = getTexture("sets/" + armor->name + "/runBottom" + to_string(i));
				armorRunTextures[12 + i] = getTexture("sets/" + armor->name + "/runLeft" + to_string(i));

				armorAttackTextures[i] = getTexture("sets/" + armor->name + "/attackTop" + to_string(i));
				armorAttackTextures[4 + i] = getTexture("sets/" + armor->name + "/attackRight" + to_string(i));
				armorAttackTextures[8 + i] = getTexture("sets/" + armor->name + "/attackBottom" + to_string(i));
				armorAttackTextures[12 + i] = getTexture("sets/" + armor->name + "/attackLeft" + to_string(i));

			}
		}

		armorSprite = sf::Sprite();
		armorSprite.setOrigin(32, 58);
	}

	void loadPants() {

		for (short i = 0; i < 16; i++) {
			pantsIdleTextures[i] = nullptr;
			pantsRunTextures[i] = nullptr;
			pantsAttackTextures[i] = nullptr;

		}

		if (pants != nullptr) {

			for (short i = 0; i < 4; i++) {
				pantsIdleTextures[i] = getTexture("sets/" + pants->name + "/idleTop" + to_string(i));
				pantsIdleTextures[4 + i] = getTexture("sets/" + pants->name + "/idleRight" + to_string(i));
				pantsIdleTextures[8 + i] = getTexture("sets/" + pants->name + "/idleBottom" + to_string(i));
				pantsIdleTextures[12 + i] = getTexture("sets/" + pants->name + "/idleLeft" + to_string(i));

				pantsRunTextures[i] = getTexture("sets/" + pants->name + "/runTop" + to_string(i));
				pantsRunTextures[4 + i] = getTexture("sets/" + pants->name + "/runRight" + to_string(i));
				pantsRunTextures[8 + i] = getTexture("sets/" + pants->name + "/runBottom" + to_string(i));
				pantsRunTextures[12 + i] = getTexture("sets/" + pants->name + "/runLeft" + to_string(i));

				pantsAttackTextures[i] = getTexture("sets/" + pants->name + "/attackTop" + to_string(i));
				pantsAttackTextures[4 + i] = getTexture("sets/" + pants->name + "/attackRight" + to_string(i));
				pantsAttackTextures[8 + i] = getTexture("sets/" + pants->name + "/attackBottom" + to_string(i));
				pantsAttackTextures[12 + i] = getTexture("sets/" + pants->name + "/attackLeft" + to_string(i));

			}
		}

		pantsSprite = sf::Sprite();
		pantsSprite.setOrigin(32, 58);

	}

	void loadLeftHand() {

		for (short i = 0; i < 16; i++) {
			leftHandIdleTextures[i] = nullptr;
			leftHandRunTextures[i] = nullptr;
			leftHandAttackTextures[i] = nullptr;

		}

		if (leftHand != nullptr) {

			for (short i = 0; i < 4; i++) {
				leftHandIdleTextures[i] = getTexture("sets/" + leftHand->name + "/idleTop" + to_string(i));
				leftHandIdleTextures[4 + i] = getTexture("sets/" + leftHand->name + "/idleRight" + to_string(i));
				leftHandIdleTextures[8 + i] = getTexture("sets/" + leftHand->name + "/idleBottom" + to_string(i));
				leftHandIdleTextures[12 + i] = getTexture("sets/" + leftHand->name + "/idleLeft" + to_string(i));

				leftHandRunTextures[i] = getTexture("sets/" + leftHand->name + "/runTop" + to_string(i));
				leftHandRunTextures[4 + i] = getTexture("sets/" + leftHand->name + "/runRight" + to_string(i));
				leftHandRunTextures[8 + i] = getTexture("sets/" + leftHand->name + "/runBottom" + to_string(i));
				leftHandRunTextures[12 + i] = getTexture("sets/" + leftHand->name + "/runLeft" + to_string(i));

				leftHandAttackTextures[i] = getTexture("sets/" + leftHand->name + "/attackTop" + to_string(i));
				leftHandAttackTextures[4 + i] = getTexture("sets/" + leftHand->name + "/attackRight" + to_string(i));
				leftHandAttackTextures[8 + i] = getTexture("sets/" + leftHand->name + "/attackBottom" + to_string(i));
				leftHandAttackTextures[12 + i] = getTexture("sets/" + leftHand->name + "/attackLeft" + to_string(i));

			}
		}

		leftHandSprite = sf::Sprite();
		leftHandSprite.setOrigin(32, 58);

	}

	void loadRightHand() {

		for (short i = 0; i < 16; i++) {
			rightHandIdleTextures[i] = nullptr;
			rightHandRunTextures[i] = nullptr;
			rightHandAttackTextures[i] = nullptr;

		}

		if (rightHand != nullptr) {

			for (short i = 0; i < 4; i++) {
				rightHandIdleTextures[i] = getTexture("sets/" + rightHand->name + "/idleTop" + to_string(i));
				rightHandIdleTextures[4 + i] = getTexture("sets/" + rightHand->name + "/idleRight" + to_string(i));
				rightHandIdleTextures[8 + i] = getTexture("sets/" + rightHand->name + "/idleBottom" + to_string(i));
				rightHandIdleTextures[12 + i] = getTexture("sets/" + rightHand->name + "/idleLeft" + to_string(i));

				rightHandRunTextures[i] = getTexture("sets/" + rightHand->name + "/runTop" + to_string(i));
				rightHandRunTextures[4 + i] = getTexture("sets/" + rightHand->name + "/runRight" + to_string(i));
				rightHandRunTextures[8 + i] = getTexture("sets/" + rightHand->name + "/runBottom" + to_string(i));
				rightHandRunTextures[12 + i] = getTexture("sets/" + rightHand->name + "/runLeft" + to_string(i));

				rightHandAttackTextures[i] = getTexture("sets/" + rightHand->name + "/attackTop" + to_string(i));
				rightHandAttackTextures[4 + i] = getTexture("sets/" + rightHand->name + "/attackRight" + to_string(i));
				rightHandAttackTextures[8 + i] = getTexture("sets/" + rightHand->name + "/attackBottom" + to_string(i));
				rightHandAttackTextures[12 + i] = getTexture("sets/" + rightHand->name + "/attackLeft" + to_string(i));

			}
		}

		rightHandSprite = sf::Sprite();
		rightHandSprite.setOrigin(32, 58);

	}


	virtual void update(float dt) {
		calculateCurrentFrame(dt);
		GameObject::update(dt);
		textname.setPosition(position.x, position.y - collider->height - 10);

		sprite.setTexture(*idleTextures[direction * 4 + frame]->texture);
		sprite.setPosition(position);

		if (helmet != nullptr) {
			helmetSprite.setTexture(*helmetIdleTextures[direction * 4 + frame]->texture);
			helmetSprite.setPosition(position);

		}

		if (armor != nullptr) {
			armorSprite.setTexture(*armorIdleTextures[direction * 4 + frame]->texture);
			armorSprite.setPosition(position);
		}

		if (pants != nullptr) {
			pantsSprite.setTexture(*pantsIdleTextures[direction * 4 + frame]->texture);
			pantsSprite.setPosition(position);
		}

		if (rightHand != nullptr) {
			rightHandSprite.setTexture(*rightHandIdleTextures[direction * 4 + frame]->texture);
			rightHandSprite.setPosition(position);
		}

		if (leftHand != nullptr) {
			leftHandSprite.setTexture(*leftHandIdleTextures[direction * 4 + frame]->texture);
			leftHandSprite.setPosition(position);
		}

		viewRangeArea.setPosition(position);
		actionRangeArea.setPosition(position);

		setLifeBar();

		showHand = false;
		talkWithSprite.setPosition(position.x, position.y - 90);

		if (dialogue != nullptr) {
			if (player != nullptr) {

				float x1, y1, rx1, ry1;
				float x2, y2, rx2, ry2;

				x1 = player->position.x;
				y1 = player->position.y;
				rx1 = (player->collider->width / 2.0f + player->actionRange);
				ry1 = (player->collider->length + player->actionRange) / 2.0f;

				x2 = position.x;
				y2 = position.y;
				rx2 = (collider->width / 2.0f + ACTION_RANGE);
				ry2 = (collider->length + ACTION_RANGE) / 2.0f;

				if (intersectionTwoEllipses(x1, y1, rx1, ry1, x2, y2, rx2, ry2)) {
					showHand = true;
				}
			}

		}

	}

	virtual void draw() {

		if (direction == 0) {
			// TOP
			window->draw(rightHandSprite);
			window->draw(leftHandSprite);
			window->draw(sprite);
			window->draw(helmetSprite);
			window->draw(pantsSprite);
			window->draw(armorSprite);

		}

		if (direction == 1) {
			// RIGHT

			window->draw(leftHandSprite);
			window->draw(sprite);
			window->draw(helmetSprite);
			window->draw(pantsSprite);
			window->draw(armorSprite);
			window->draw(rightHandSprite);
		}

		if (direction == 2) {
			// BOTTOM
			window->draw(sprite);
			window->draw(helmetSprite);
			window->draw(pantsSprite);
			window->draw(armorSprite);
			window->draw(leftHandSprite);
			window->draw(rightHandSprite);
		}

		if (direction == 3) {
			// LEFT
			window->draw(rightHandSprite);
			window->draw(sprite);
			window->draw(helmetSprite);
			window->draw(pantsSprite);
			window->draw(armorSprite);
			window->draw(leftHandSprite);

		}
		
		if (showHand == true)
			window->draw(talkWithSprite);
		
		GameObject::draw();
		//window->draw(lifeBarBackground);
		//window->draw(lifeBar);
	}
};

std::vector < Character* > characters;


#endif