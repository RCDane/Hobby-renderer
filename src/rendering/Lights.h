#include "glm/common.hpp"
#include <vector>
#include "Shader.h"

struct Light {
	glm::vec3 position;

	float constant;
	float linear;
	float quadratic;

	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
};
class Lights {
public:
   Lights(int amount);
   void Bind(Shader *shader);
   bool Add(Light light );
private:
   int numberOfLights;
   int maxNumberOfLights;
   std::vector<Light> lights;
};

