#ifndef GameObjects_hpp
#define GameObjects_hpp

enum class GameObjectType { 
	GameObject, Nature, 
	Unit, Monster, Character, Player, 
	ItemOnMap, InventoryOnMap, 
	Path, Furniture, 
	Terrain, Floor, 
	Door, Wall, Building };

class Collider {
public:
	float width;
	float length;
	float height;
	bool isRectangular;
	sf::Shape* shape;

	Collider(float width, float length, float height, bool isRectangular) {
		this->width = width;
		this->length = length;
		this->height = height;
		this->isRectangular = isRectangular;

		if (isRectangular == true) {
			shape = new sf::RectangleShape(sf::Vector2f(width, length));
			shape->setFillColor(sf::Color(128, 64, 128, 96));
			shape->setOutlineColor(sf::Color(196, 64, 196, 128));
			shape->setOutlineThickness(4.0f);
			shape->setOrigin(width/2.0f, length /2.0f);
			shape->setScale(1, 1);
		}
		else {
			shape = new sf::CircleShape(width/2.0f);
			shape->setFillColor(sf::Color(128, 64, 128, 96));
			shape->setOutlineColor(sf::Color(196, 64, 196, 128));
			shape->setOutlineThickness(4.0f);
			shape->setOrigin(width/2.0f, width/2.0f);
			shape->setScale(1, length/width);
		}
	}

	Collider(Collider* col) {
		this->width = col->width;
		this->length = col->length;
		this->height = col->height;
		this->isRectangular = col->isRectangular;

		if (isRectangular == true) {
			shape = new sf::RectangleShape(sf::Vector2f(width, length));
			shape->setFillColor(col->shape->getFillColor());
			shape->setOutlineColor(col->shape->getOutlineColor());
			shape->setOutlineThickness(col->shape->getOutlineThickness());
			shape->setOrigin(col->shape->getOrigin());
			shape->setScale(col->shape->getScale());

		}
		else {
			shape = new sf::CircleShape(width/2.0f);
			shape->setFillColor(col->shape->getFillColor());
			shape->setOutlineColor(col->shape->getOutlineColor());
			shape->setOutlineThickness(col->shape->getOutlineThickness());
			shape->setOrigin(col->shape->getOrigin());
			shape->setScale(col->shape->getScale());
		}
	}

	~Collider() {
		delete shape;	// sf::Shape* shape
	}
};

class GameObject { 
public:
	string name;
	GameObjectType type;
	sf::Vector2f position;
	bool collisioning;	// check the collision
	
	bool mouseIsHover;	// mouse is on GameObject
	
	Collider* collider;
	sf::Text textname;
	
	bool isVisible;	// TO-DO
	bool toDeleteFromMainLists;	// TO-DO
	bool isSelected;


	GameObject(string name, float x, float y, float width, float length, float height, bool collisioning, bool isRectangular) {
		// CREATE PREFAB
		this->name = name;

		type = GameObjectType::GameObject;
		position.x = x;
		position.y = y;

		this->collisioning = collisioning;
		
		mouseIsHover = false;

		collider = new Collider(width, length, height, isRectangular);
		createTextname();
		
		toDeleteFromMainLists = false;
		isVisible = false;
		isSelected = false;
	}

	GameObject(GameObject* go, float x, float y) {
		// CREATE GAMEOBJECT FROM PREFAB
		this->name = go->name;
		type = GameObjectType::GameObject;
		position.x = x;
		position.y = y;

		this->collisioning = go->collisioning;
		
		mouseIsHover = false;
		collider = new Collider(go->collider);

		createTextname();

		toDeleteFromMainLists = false;
		isVisible = false;
		isSelected = false;
	}

	GameObject(string name) {
		// FOR TILES PALETTE (TERRAIN OR FLOOR) 
		this->name = name;
		position.x = 0;
		position.y = 0;

		collisioning = true;

		mouseIsHover = false;
		collider = new Collider(16,16,16, true);
		
		dynamic_cast<sf::RectangleShape*>(collider->shape)->setOrigin(sf::Vector2f(0, 0));
		dynamic_cast<sf::RectangleShape*>(collider->shape)->setSize(sf::Vector2f(16, 16));
		dynamic_cast<sf::RectangleShape*>(collider->shape)->setOutlineThickness(0);
		dynamic_cast<sf::RectangleShape*>(collider->shape)->setPosition(position);

		createTextname();

		toDeleteFromMainLists = false;
		isVisible = false;
		isSelected = false;
	}

	GameObject(string name, float x, float y) {
		// FOR BUILDINGS

		this->name = name;
		position.x = x;
		position.y = y;

		collisioning = false;

		mouseIsHover = false;
		createTextname();

		toDeleteFromMainLists = false;
		isVisible = false;
		isSelected = false;
	}

	virtual ~GameObject() { 

		delete collider;
	}

	virtual void setPosition(sf::Vector2f position) {
		this->position = position;

		if (collider != nullptr)
			textname.setPosition(position.x, position.y - collider->height - 35);
		else
			textname.setPosition(position.x, position.y);
	}

	void createTextname() {
		textname = sf::Text(getShortName(name), basicFont, 16);
		textname.setOrigin(textname.getGlobalBounds().width / 2.f, textname.getGlobalBounds().height / 2.f);
		textname.setFillColor(textColor);
		textname.setOutlineColor(sf::Color::Black);
		textname.setOutlineThickness(2.0f);
		
		if (collider != nullptr)
			textname.setPosition(position.x, position.y - collider->height - 35);
		else
			textname.setPosition(position.x, position.y);
	}

	virtual void mouseHovering() {

		if (collider->isRectangular == false) {

			if (pointInEllipse(worldMousePosition.x, worldMousePosition.y, position.x, position.y, collider->width/2.0f, collider->length / 2.0f))
				mouseIsHover = true;
			else
				mouseIsHover = false;
		}

		if (collider->isRectangular == true) {

			if (pointInRectangle(worldMousePosition.x, worldMousePosition.y, position.x, position.y, collider->width, collider->length))
				mouseIsHover = true;
			else
				mouseIsHover = false;
		}

		
	}

	virtual void update(float dt) { 
		createTextname();
		
	}

	virtual void updateStatistic(float dt) {

		collider->shape->setPosition(position);
		
	}

	virtual void draw() {

		window->draw(textname);
	}

	virtual void drawStatistics(){
		if(renderColliders)
			window->draw(*collider->shape);
	}

	virtual void drawAllStatistics() {
		window->draw(*collider->shape);
	}

};


std::vector < GameObject* > gameObjects;

class Point {
public:
	float x, y;
	Point()
		: x(0)
		, y(0)
	{ }
	Point(float x, float y)
		: x(x)
		, y(y)
	{ }

	bool operator ==(const Point& other) const {
		return x == other.x && y == other.y;
	}

	bool operator !=(const Point& other) const {
		return x != other.x || y != other.y;
	}

	bool operator <(const Point& other) const {
		return std::tie(x, y) < std::tie(other.x, other.y);
	}
};

bool collisionPrediction(GameObject* object, float dx, float dy)
{
	if (object->collisioning == false)
		return false;

	if (object->collider->isRectangular == false) {
		
		// object is elipse
		for (auto& go : gameObjects) {

			if (go != object && go->collisioning != false) {

				if (go->collider->isRectangular == false) {
					// elipse with elipse
					if ( intersectionTwoEllipses(object->position.x + dx, object->position.y + dy, object->collider->width/2.0f, object->collider->length / 2.f, go->position.x, go->position.y, go->collider->width/2.0f, go->collider->length / 2.f))
						return true;
				}

				if (go->collider->isRectangular == true) {
					// elipse with rectangle
					if ( intersectionRectangleWithElipse(go->position.x, go->position.y, go->collider->width, go->collider->length, object->position.x+dx, object->position.y+dy, object->collider->width/2.0f, object->collider->length / 2.0f))
						return true;

				}
			}
		}
	}

	if (object->collider->isRectangular == true) {
		
		// object is rectangle
		for (auto& go : gameObjects) {

			if (go != object && go->collisioning != false) {

				if (go->collider->isRectangular == false) {
					// rectangle with elipse
					if (intersectionRectangleWithElipse(object->position.x+dx, object->position.y+dy, object->collider->width, object->collider->length, go->position.x, go->position.y, go->collider->width/2.0f, go->collider->length/2.0f))
						return true;
				}

				if (go->collider->isRectangular == true) {
					// rectangle with rectangle
					if (intersectionTwoRectangles(object->position.x+dx, object->position.y+dy, object->collider->width, object->collider->length, go->position.x, go->position.y, go->collider->width, go->collider->length))
						return true;

				}
			}
		}
	}
	

	return false;
}

bool collisionPrediction(GameObject* object, Point p, float dx, float dy)
{
	if (object->collisioning == false)
		return false;

	if (object->collider->isRectangular == false) {

		// object is elipse
		for (auto& go : gameObjects) {

			if (go != object && go->collisioning != false) {

				if (go->collider->isRectangular == false) {
					// elipse with elipse
					if (intersectionTwoEllipses(p.x+dx, p.y+dy, object->collider->width / 2.0f, object->collider->length / 2.f, go->position.x, go->position.y, go->collider->width / 2.0f, go->collider->length / 2.f))
						return true;
				}

				if (go->collider->isRectangular == true) {
					// elipse with rectangle
					if (intersectionRectangleWithElipse(go->position.x, go->position.y, go->collider->width, go->collider->length, p.x+dx, p.y+dy, object->collider->width / 2.0f, object->collider->length / 2.0f))
						return true;

				}
			}
		}
	}

	if (object->collider->isRectangular == true) {

		// object is rectangle
		for (auto& go : gameObjects) {

			if (go != object && go->collisioning != false) {

				if (go->collider->isRectangular == false) {
					// rectangle with elipse
					if (intersectionRectangleWithElipse(p.x+dx, p.y+dy, object->collider->width, object->collider->length, go->position.x, go->position.y, go->collider->width / 2.0f, go->collider->length / 2.0f))
						return true;
				}

				if (go->collider->isRectangular == true) {
					// rectangle with rectangle
					if (intersectionTwoRectangles(p.x+dx, p.y+dy, object->collider->width, object->collider->length, go->position.x, go->position.y, go->collider->width, go->collider->length))
						return true;

				}
			}
		}
	}


	return false;
}


#endif