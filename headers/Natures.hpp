#ifndef NatureObjects_hpp
#define NatureObjects_hpp

class Nature : public GameObject {
public:
	Texture* texture;
	sf::Sprite sprite;

	Nature(string name, float width, float length, float height) : GameObject(name, 0, 0, width, length, height, true, false) {
		type = GameObjectType::Nature;
		this->texture = getTexture(name);
		sprite = sf::Sprite();
		sprite.setTexture(*texture->texture);
		sprite.setOrigin(texture->cx, texture->cy);
	}

	Nature(GameObject* object, float x, float y) : GameObject(object, x, y) {
		type = GameObjectType::Nature;
		this->texture = getTexture(name);
		sprite = sf::Sprite();
		sprite.setTexture(*texture->texture);
		sprite.setOrigin(texture->cx, texture->cy);
		sprite.setPosition(position);
	}

	virtual ~Nature() {
	
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

std::vector < Nature* > natures;

#endif