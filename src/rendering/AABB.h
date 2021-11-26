#include "glm/glm.hpp"
#include <rendering/Mesh.h>
#include <vector>

struct AABB {

public:
    AABB(std::vector<Vertex> vertices, glm::mat4 model);
    glm::vec3 min;
    glm::vec3 max;  
    void Render(glm::mat4 model, glm::mat4 view, glm::mat4 projection);
};



