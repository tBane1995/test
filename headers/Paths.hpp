#ifndef Paths_hpp
#define Paths_hpp


class Path : public GameObject {
public:

	Texture* texture;
	sf::Sprite sprite;
	
	Path(string name, float width, float length, float height ) : GameObject(name, 0, 0, width, length, height, false, false) {
		type = GameObjectType::Path;
		this->texture = getTexture(name);
		sprite = sf::Sprite();
		sprite.setTexture(*texture->texture);
		sprite.setOrigin(texture->cx, texture->cy);
	}

	Path(GameObject* object, float x, float y) : GameObject(object, x, y) {
		type = GameObjectType::Path;
		this->texture = getTexture(name);
		sprite = sf::Sprite();
		sprite.setTexture(*getTexture(name)->texture);
		sprite.setOrigin(texture->cx, texture->cy);
		sprite.setPosition(position);
		
	}

	virtual ~Path() {
	
	}

	virtual void setPosition(sf::Vector2f position) {
		this->position = position;
		sprite.setPosition(position);
	}

	virtual void update(float dt) {

	}

	virtual void draw() {
		
		if(mouseIsHover)
			GameObject::draw();
	
		window->draw(sprite);
	}
};

std::vector < Path* > paths;

bool isPathOnPosition( float x, float y) {
	for (auto& path : paths) {
		if (pointInEllipse(x, y, path->position.x, path->position.y, path->collider->width/2.0f, path->collider->length / 2.0f))
			return true;
	}

	return false;
}

#endif