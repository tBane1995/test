#ifndef TerrainAndFloors_hpp
#define TerrainAndFloors_hpp

float tileSide = 16.0f;

enum class terrainType { grass, sands, water, gravel, beach };
enum class floorType { floor_0, floor_1, floor_2, floor_3 };

class TerrainPrefab : public GameObject {
public:
	Texture* texture;
	terrainType ttype;

	TerrainPrefab(string name, terrainType ttype) : GameObject(name) {
		type = GameObjectType::Terrain;
		texture = getTexture(name);
		this->ttype = ttype;

		collider->shape->setPosition(position);
	}

	virtual ~TerrainPrefab() { 
		
	}

	virtual void update(float dt) {
		sf::Vector2f position;
		position.x = int(worldMousePosition.x) / int(tileSide) * int(tileSide);
		position.y = int(worldMousePosition.y) / int(tileSide) * int(tileSide);
	}

	virtual void draw() {
		window->draw(*collider->shape);
	}
	
};

class FloorPrefab : public GameObject {
public:
	Texture* texture;
	floorType ftype;

	FloorPrefab(string name, floorType ftype) : GameObject(name) {
		type = GameObjectType::Floor;
		texture = getTexture(name);
		this->ftype = ftype;
	}

	virtual ~FloorPrefab() { 
		
	}

	virtual void update(float dt) {
		sf::Vector2f position;
		position.x = int(worldMousePosition.x) / int(tileSide) * int(tileSide);
		position.y = int(worldMousePosition.y) / int(tileSide) * int(tileSide);

		collider->shape->setPosition(position);

	}

	virtual void draw() {
		window->draw(*collider->shape);
	}

};

class Terrain : public sf::Drawable, public sf::Transformable {
public:
	short width, height;
	sf::Vector2i coords;

	sf::VertexArray vertexes;
	sf::Texture tileset;

	sf::VertexArray outlines;

	std::vector < short > tiles;

	Terrain(short x, short y, short width, short height ) {

		coords.x = x;
		coords.y = y;

		this->width = width;
		this->height = height;

		tileset = sf::Texture();
		tileset = *getTexture("tiles/0_tileset")->texture;

		vertexes.setPrimitiveType(sf::Triangles);
		vertexes.resize(width * height * 6); // widthMap * heightMap * TwoTrianglesVertices

		tiles.resize(width * height);

		short coord_x, coord_y;

		// TERRAIN - GRASS
		for (short y = 0; y < height; y++)
			for (short x = 0; x < width; x++) {

				sf::Vertex* triangles = &vertexes[(y * width + x) * 6];

				coord_x = (coords.x + x);
				coord_y = (coords.y + y);

				triangles[0].position = sf::Vector2f(coord_x * tileSide, coord_y * tileSide);
				triangles[1].position = sf::Vector2f((coord_x + 1) * tileSide, coord_y * tileSide);
				triangles[2].position = sf::Vector2f(coord_x * tileSide, (coord_y + 1) * tileSide);
				triangles[3].position = sf::Vector2f(coord_x * tileSide, (coord_y + 1) * tileSide);
				triangles[4].position = sf::Vector2f((coord_x + 1) * tileSide, coord_y * tileSide);
				triangles[5].position = sf::Vector2f((coord_x + 1) * tileSide, (coord_y + 1) * tileSide);

				edit(x, y, 0);
			}

	}

	void edit(short x, short y, short value) {

		if (x < 0 || x >= width || y < 0 || y >= height)
			return;

		if (value > 4 || value < 0)
			return;

		tiles[y * width + x] = value;

		short global_x = coords.x + x;
		short global_y = coords.y + y;

		sf::Vertex* triangles = &vertexes[(y * width + x) * 6];

		short tu = (short(global_x * tileSide) % 64) + (value * 64);
		short tv = (short(global_y * tileSide) % 64);

		//cout << "tu: " << tu << ", tv: " << tv << "\n";

		triangles[0].texCoords = sf::Vector2f(tu, tv);
		triangles[1].texCoords = sf::Vector2f(tu + tileSide, tv);
		triangles[2].texCoords = sf::Vector2f(tu, tv + tileSide);
		triangles[3].texCoords = sf::Vector2f(tu, tv + tileSide);
		triangles[4].texCoords = sf::Vector2f(tu + tileSide, tv);
		triangles[5].texCoords = sf::Vector2f(tu + tileSide, tv + tileSide);
	}

	void edit(sf::Vector2f worldMousePosition, int value) {

		short coord_x = (worldMousePosition.x - coords.x * 16) / 16;
		short coord_y = (worldMousePosition.y - coords.y * 16) / 16;

		if (coord_x < 0 || coord_x >= width || coord_y < 0 || coord_y >= height)
			return;

		if (value > 4 || value < 0)
			return;

		tiles[coord_y * width + coord_x] = short(value);

		sf::Vertex* triangles = &vertexes[(coord_y * width + coord_x) * 6];

		short tu = (short(coord_x * tileSide) % 64) + (value * 64);
		short tv = (short(coord_y * tileSide) % 64);

		//cout << "tu: " << tu << ", tv: " << tv << "\n";
		
		triangles[0].texCoords = sf::Vector2f(tu, tv);
		triangles[1].texCoords = sf::Vector2f(tu + tileSide, tv);
		triangles[2].texCoords = sf::Vector2f(tu, tv + tileSide);
		triangles[3].texCoords = sf::Vector2f(tu, tv + tileSide);
		triangles[4].texCoords = sf::Vector2f(tu + tileSide, tv);
		triangles[5].texCoords = sf::Vector2f(tu + tileSide, tv + tileSide);
	}

	void edit(sf::Vector2f worldMousePosition, TerrainPrefab* terrainPrefab) {

		if (terrainPrefab->name == "tiles/tile_0_grass")
			edit(worldMousePosition, 0);

		if (terrainPrefab->name == "tiles/tile_1_sands")
			edit(worldMousePosition, 1);

		if (terrainPrefab->name == "tiles/tile_2_water")
			edit(worldMousePosition, 2);

		if (terrainPrefab->name == "tiles/tile_3_gravel")
			edit(worldMousePosition, 3);

		if (terrainPrefab->name == "tiles/tile_4_beach")
			edit(worldMousePosition, 4);

	}

	void generateBorders( Terrain* topTerrain, Terrain* bottomTerrain, Terrain* leftTerrain, Terrain *rightTerrain) {

		outlines.clear();
		outlines.setPrimitiveType(sf::Quads);

		if (coords.x / 16 == 1 && coords.y / 16 == 1) {
			cout << "coords: " << coords.x / 16 << " " << coords.y / 16 << "\n";
			for (int i = 0; i < width; i++)
				cout << tiles[i] << " " << topTerrain->tiles[15*width+i] << "\n";
		}
		
		
		int x, y;
		int coord_x, coord_y;
		float lineThickness = 4.0f; // Grubość linii

		for (int i = 0; i < tiles.size(); i++) {
			
			x = i % width;
			y = i / width;

			coord_x = (coords.x + x) * tileSide;
			coord_y = (coords.y + y) * tileSide;
			
			short tileValue;

			if (y == 0) {
				(topTerrain != nullptr) ? tileValue = topTerrain->tiles[y * 15 + x] : tileValue = -1;
			}
			else
				tileValue = this->tiles[i - width];

			// GÓRNA KRAWĘDŹ
			if (this->tiles[i] != tileValue) {
				outlines.append(sf::Vertex(sf::Vector2f(coord_x, coord_y - lineThickness / 2), sf::Color::Black));
				outlines.append(sf::Vertex(sf::Vector2f(coord_x + tileSide, coord_y - lineThickness / 2), sf::Color::Black));
				outlines.append(sf::Vertex(sf::Vector2f(coord_x + tileSide, coord_y + lineThickness / 2), sf::Color::Black));
				outlines.append(sf::Vertex(sf::Vector2f(coord_x, coord_y + lineThickness / 2), sf::Color::Black));
			}

			if (y > 0 && y < 15 && x > 0 && x < 15) {

				

				// DOLNA KRAWĘDŹ
				if (tiles[i] != tiles[i+width]) {
					outlines.append(sf::Vertex(sf::Vector2f(coord_x, coord_y + tileSide - lineThickness / 2), sf::Color::Black));
					outlines.append(sf::Vertex(sf::Vector2f(coord_x + tileSide, coord_y + tileSide - lineThickness / 2), sf::Color::Black));
					outlines.append(sf::Vertex(sf::Vector2f(coord_x + tileSide, coord_y + tileSide + lineThickness / 2), sf::Color::Black));
					outlines.append(sf::Vertex(sf::Vector2f(coord_x, coord_y + tileSide + lineThickness / 2), sf::Color::Black));
				}

				// LEWA KRAWĘDŹ
				if (tiles[i] != tiles[i-1]) {
					outlines.append(sf::Vertex(sf::Vector2f(coord_x - lineThickness / 2, coord_y), sf::Color::Black));
					outlines.append(sf::Vertex(sf::Vector2f(coord_x + lineThickness / 2, coord_y), sf::Color::Black));
					outlines.append(sf::Vertex(sf::Vector2f(coord_x + lineThickness / 2, coord_y + tileSide), sf::Color::Black));
					outlines.append(sf::Vertex(sf::Vector2f(coord_x - lineThickness / 2, coord_y + tileSide), sf::Color::Black));
				}

				// PRAWA KRAWĘDŹ
				if (tiles[i] != tiles[i+1]) {
					outlines.append(sf::Vertex(sf::Vector2f(coord_x + tileSide - lineThickness / 2, coord_y), sf::Color::Black));
					outlines.append(sf::Vertex(sf::Vector2f(coord_x + tileSide + lineThickness / 2, coord_y), sf::Color::Black));
					outlines.append(sf::Vertex(sf::Vector2f(coord_x + tileSide + lineThickness / 2, coord_y + tileSide), sf::Color::Black));
					outlines.append(sf::Vertex(sf::Vector2f(coord_x + tileSide - lineThickness / 2, coord_y + tileSide), sf::Color::Black));
				}
			}

			
				


		}
	}

private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{

		// draw tiles - terrain
		states.transform *= getTransform();
		states.texture = &tileset;	// TO-DO
		target.draw(vertexes, states);
		target.draw(outlines, states);
	}
};

class Floors : public sf::Drawable, public sf::Transformable {
public:
	short width, height;
	sf::Vector2i coords;

	sf::VertexArray vertexes;
	sf::Texture floorset;

	std::vector < short > floors;

	Floors(short x, short y, short width, short height) {
		
		coords.x = x;
		coords.y = y;

		this->width = width;
		this->height = height;

		floorset = sf::Texture();
		floorset = *getTexture("floors/0_floorset")->texture;

		vertexes.setPrimitiveType(sf::Triangles);
		vertexes.resize(width * height * 6); // widthMap * heightMap * TwoTrianglesVertices

		floors.resize(width * height);

		short coord_x, coord_y;

		for (short y = 0; y < height; y++)
			for (short x = 0; x < width; x++) {

				sf::Vertex* triangles = &vertexes[(y * width + x) * 6];

				coord_x = (coords.x + x);
				coord_y = (coords.y + y);

				triangles[0].position = sf::Vector2f(coord_x * tileSide, coord_y * tileSide);
				triangles[1].position = sf::Vector2f((coord_x + 1) * tileSide, coord_y * tileSide);
				triangles[2].position = sf::Vector2f(coord_x * tileSide, (coord_y + 1) * tileSide);
				triangles[3].position = sf::Vector2f(coord_x * tileSide, (coord_y + 1) * tileSide);
				triangles[4].position = sf::Vector2f((coord_x + 1) * tileSide, coord_y * tileSide);
				triangles[5].position = sf::Vector2f((coord_x + 1) * tileSide, (coord_y + 1) * tileSide);

				edit(x, y, 0);
			}


	}

	void edit(short x, short y, short value) {

		if (x < 0 || x >= width || y < 0 || y >= height)
			return;

		if (value > 3 || value < 0)
			return;

		floors[y * width + x] = value;

		short global_x = coords.x + x;
		short global_y = coords.y + y;

		sf::Vertex* triangles = &vertexes[(y * width + x) * 6];

		short tu = (short(global_x * tileSide) % 64) + (value * 64);
		short tv = (short(global_y * tileSide) % 64);

		//cout << "tu: " << tu << ", tv: " << tv << "\n";

		triangles[0].texCoords = sf::Vector2f(tu, tv);
		triangles[1].texCoords = sf::Vector2f(tu + tileSide, tv);
		triangles[2].texCoords = sf::Vector2f(tu, tv + tileSide);
		triangles[3].texCoords = sf::Vector2f(tu, tv + tileSide);
		triangles[4].texCoords = sf::Vector2f(tu + tileSide, tv);
		triangles[5].texCoords = sf::Vector2f(tu + tileSide, tv + tileSide);
	}

	void edit(sf::Vector2f worldMousePosition, int value) {

		short coord_x = (worldMousePosition.x - coords.x * width) / 16;
		short coord_y = (worldMousePosition.y - coords.y * height) / 16;

		if (coord_x < 0 || coord_x >= width || coord_y < 0 || coord_y >= height)
			return;

		if (value > 3 || value < 0)
			return;

		floors[coord_y * width + coord_x] = value;

		sf::Vertex* triangles = &vertexes[(coord_y * width + coord_x) * 6];

		short tu = (short(coord_x * tileSide) % 64) + (value * 64);
		short tv = (short(coord_y * tileSide) % 64);

		//cout << "tu: " << tu << ", tv: " << tv << "\n";

		triangles[0].texCoords = sf::Vector2f(tu, tv);
		triangles[1].texCoords = sf::Vector2f(tu + tileSide, tv);
		triangles[2].texCoords = sf::Vector2f(tu, tv + tileSide);
		triangles[3].texCoords = sf::Vector2f(tu, tv + tileSide);
		triangles[4].texCoords = sf::Vector2f(tu + tileSide, tv);
		triangles[5].texCoords = sf::Vector2f(tu + tileSide, tv + tileSide);
	}

	void edit(sf::Vector2f worldMousePosition, FloorPrefab* floorPrefab) {

		if (floorPrefab->name == "floors/floor_0")
			edit(worldMousePosition, 0);

		if (floorPrefab->name == "floors/floor_1")
			edit(worldMousePosition, 1);

		if (floorPrefab->name == "floors/floor_2")
			edit(worldMousePosition, 2);

		if (floorPrefab->name == "floors/floor_3")
			edit(worldMousePosition, 3);
	}


private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{

		states.transform *= getTransform();
		states.texture = &floorset;	// TO-DO
		target.draw(vertexes, states);


	}
};

Terrain* terrain = nullptr;
#endif