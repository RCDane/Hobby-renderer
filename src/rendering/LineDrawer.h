#include "Shader.h"
#include <vector>
class LineDrawer{
public:
    LineDrawer();
    void DrawLines(std::vector<glm::vec3> points,glm::mat4 model,glm::mat4 view,glm::mat4 projection);
private:
    Shader* shader;
};
