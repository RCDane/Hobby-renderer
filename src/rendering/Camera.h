#include "glm/glm.hpp"
class Camera {
public:
    Camera(glm::vec3 forward,glm::vec3 position, glm::vec3 up);
private:
    glm::vec3 vup;
    glm::vec3 vrp;
    glm::vec3 vpn;
    glm::mat4 camera;
};