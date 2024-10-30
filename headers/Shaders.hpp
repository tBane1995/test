#ifndef Shaders_hpp
#define Shaders_hpp

using namespace std;

class Shader {
public:
	string name;
	sf::Shader* shader;

	Shader(string pathfile) {

		name = "";
		
		short i = short(pathfile.size()) - 6;
		while (i >= 0)
			name = pathfile[i--] + name;

		shader = new sf::Shader();
		shader->loadFromFile("assets/" + pathfile, sf::Shader::Fragment);
		//cout << "load shader: " << pathfile << " as: " << name << endl;
	}

	Shader(string name, string vertex_pathfile, string fragment_pathfile) {

		this->name = name;
		shader = new sf::Shader();
		shader->loadFromFile("assets/" + vertex_pathfile, "assets/" + fragment_pathfile);
		//cout << "load shader: " << vertex_pathfile << ", " << fragment_pathfile << " as: " << name << endl;
	}
};

std::vector < Shader* > shaders;

void loadShader(string name, string vertex_pathfile, string fragment_pathfile) {
	shaders.push_back(new Shader(name, vertex_pathfile, fragment_pathfile));
}

void loadShader(string pathfile) {
	shaders.push_back(new Shader(pathfile));
}

void loadShaders() {

	loadShader("shaders/water.frag");
	loadShader("shaders/water2", "shaders/vertex.vert", "shaders/water2.frag");
	loadShader("shaders/circle.frag");
	loadShader("shaders/jagged_circle.frag");
	loadShader("shaders/circles.frag");
}

Shader* getShader(string name) {

	for (auto& s : shaders) {
		if (s->name == name) {
			return s;
		}
	}

	std::cout << "error - get Shader - Shader: \"" << name << "\" not exists\n";
	return nullptr;
}

void updateShaders() {
	for(auto & s : shaders)
		s->shader->setUniform("time", currentTime.asSeconds());

	// water shader
	Shader* s = getShader("shaders/water2");
	sf::Vector2f resolution(screenWidth, screenHeight);
	s->shader->setUniform("resolution", resolution);
}


#endif // !define Shaders_hpp
