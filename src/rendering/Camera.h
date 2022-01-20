#include "glm/glm.hpp"
class Camera {
public:
    Camera(glm::vec3 forward,glm::vec3 position, glm::vec3 up);
    void MouseRotate(float xChange, float yChange, float deltaTime);
    void MoveCamera(float forward, float right, float deltaTime);
    glm::mat4 GetCamera();
    glm::vec3 GetPosition();
private:
    glm::vec3 vup;
    glm::vec3 vrp;
    glm::vec3 vpn;
    glm::mat4 camera;
};