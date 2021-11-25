#include "Camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
Camera::Camera(glm::vec3 forward, glm::vec3 position,glm::vec3 up){
    this->vpn = forward;
    this->vup = up;
    this->vrp = position;
    this->camera = glm::lookAt(this->vpn, this->vrp, this->vup);
}