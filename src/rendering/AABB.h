#include "glm/glm.hpp"
#include <rendering/Mesh.h>
#include <vector>

struct AABB {
public:
    AABB(std::vector<Vertex> vertices);
    glm::vec3 min;
    glm::vec3 max;  
    void Render(glm::vec3 position);
    
};



