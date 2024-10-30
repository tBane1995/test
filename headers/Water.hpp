#ifndef Water_hpp
#define Water_hpp

class Water : public sf::Drawable, public sf::Transformable {
public:
	int width, height;
	sf::Vector2i coords;
	sf::VertexArray vertexes;
	Texture* noiseTexture;

	std::vector < std::vector < bool > > waters;

	Water(int x, int y, int width, int height) {

		coords.x = x;
		coords.y = y;

		this->width = width;
		this->height = height;

		// resize the array of water
		waters.resize(height);
		for (auto& water : waters)
			water.resize(width);

		// all the water is false
		for (int y = 0; y < height; y++)
			for (int x = 0; x < width; x++) {
				waters[y][x] = false;
			}

		noiseTexture = getTexture("noise");


	}

	void edit(int x, int y, bool haveWater) {
		waters[y][x] = haveWater;
	}

	void edit(sf::Vector2f worldMousePosition, bool haveWater) {

		short coord_x = (worldMousePosition.x - coords.x * 16) / 16;
		short coord_y = (worldMousePosition.y - coords.y * 16) / 16;

		if (coord_x < 0 || coord_x >= width || coord_y < 0 || coord_y >= height)
			return;

		waters[coord_y][coord_x] = haveWater;

	}

	void update() {

		vertexes.clear();
		vertexes.setPrimitiveType(sf::Triangles);
		for (int y = 0; y < height; y++)
			for (int x = 0; x < width; x++) {

				if (waters[y][x] == true) {

					sf::Vertex tile[6];

					int coord_x = (coords.x + x);
					int coord_y = (coords.y + y);

					tile[0].position = sf::Vector2f(coord_x * tileSide, coord_y * tileSide);
					tile[1].position = sf::Vector2f((coord_x + 1) * tileSide, coord_y * tileSide);
					tile[2].position = sf::Vector2f(coord_x * tileSide, (coord_y + 1) * tileSide);
					tile[3].position = sf::Vector2f(coord_x * tileSide, (coord_y + 1) * tileSide);
					tile[4].position = sf::Vector2f((coord_x + 1) * tileSide, coord_y * tileSide);
					tile[5].position = sf::Vector2f((coord_x + 1) * tileSide, (coord_y + 1) * tileSide);

					int tu = (int(coord_x * tileSide) % noiseTexture->texture->getSize().x);
					int tv = (int(coord_y * tileSide) % noiseTexture->texture->getSize().y);

					tile[0].texCoords = sf::Vector2f(tu, tv);
					tile[1].texCoords = sf::Vector2f(tu + tileSide, tv);
					tile[2].texCoords = sf::Vector2f(tu, tv + tileSide);
					tile[3].texCoords = sf::Vector2f(tu, tv + tileSide);
					tile[4].texCoords = sf::Vector2f(tu + tileSide, tv);
					tile[5].texCoords = sf::Vector2f(tu + tileSide, tv + tileSide);

					for (int i = 0; i < 6; i++)
						vertexes.append(tile[i]);

				}


			}
	}

private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{

		states.transform *= getTransform();
		states.texture = &(*noiseTexture->texture);
		states.shader = &(*getShader("shaders/water2")->shader);
		target.draw(vertexes, states);


	}
};

#endif