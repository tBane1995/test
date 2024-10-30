#ifndef Walls_hpp
#define Walls_hpp

class Wall : public GameObject {
public:
	Texture* texture;
	sf::Sprite sprite;

	Wall(string name, float width, float length, float height) : GameObject(name, 0, 0, width, length, height, true, true) {
		type = GameObjectType::Wall;
		this->texture = getTexture(name);
		sprite = sf::Sprite();
		sprite.setTexture(*texture->texture);
		sprite.setOrigin(texture->cx, texture->cy);
	}

	Wall(GameObject* object, float x, float y) : GameObject(object, x, y) {
		type = GameObjectType::Wall;
		this->texture = getTexture(name);
		sprite = sf::Sprite();
		sprite.setTexture(*texture->texture);
		sprite.setOrigin(texture->cx, texture->cy);
		sprite.setPosition(position);
	}

	virtual ~Wall() {

	}

	virtual void setPosition(sf::Vector2f position) {
		this->position = position;
		sprite.setPosition(position);
	}

	virtual void update(float dt) {
		
	}

	virtual void draw() {
		if (mouseIsHover)
			GameObject::draw();

		window->draw(sprite);
	}
};

std::vector < Wall* > walls;

#endif