#include "glm/glm.hpp"
#include <rendering/Mesh.h>
#include <vector>

struct AABB {
private:
    bool points_set;
    void build_AABB();
    std::vector<glm::vec3> verts;
public:
    AABB(std::vector<Vertex> vertices, glm::mat4 model);
    glm::vec3 min;
    glm::vec3 max;  
    void Render(glm::mat4 model, glm::mat4 view, glm::mat4 projection);
};



