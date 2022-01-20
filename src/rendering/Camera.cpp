#include "Camera.h"
#define GLM_ENABLE_EXPERIMENTAL

#include <glm/glm.hpp>
#include <iostream>
#include <glm/gtx/string_cast.hpp>

#include <glm/gtc/matrix_transform.hpp>
Camera::Camera(glm::vec3 forward, glm::vec3 position,glm::vec3 up){
    this->vpn = forward;
    this->vup = up;
    this->vrp = position;
}

void Camera::MouseRotate(float xChange, float yChange, float deltaTime){
    glm::vec4 look_at_homo = glm::vec4(vpn, 1.0f);
    glm::vec4 cam_up_homo = glm::vec4(vup, 1.0f);
    glm::mat4 xRotation = glm::rotate(glm::mat4(1.0f), glm::degrees(-xChange)*deltaTime * 0.000005f,vup);
    glm::mat4 xyRoation = glm::rotate(xRotation, glm::degrees(-yChange)*deltaTime * 0.000005f, glm::cross(vpn, vup));
    look_at_homo = xyRoation * look_at_homo;
    vpn = glm::vec3(look_at_homo.x,look_at_homo.y,look_at_homo.z);
    vup = glm::vec3(cam_up_homo.x,cam_up_homo.y,cam_up_homo.z);
}
glm::vec3 Camera::GetPosition(){
    return vrp;
}
void Camera::MoveCamera(float forward, float right, float deltaTime){
    glm::vec3 cam_r = glm::cross(vpn, vup);
    if(forward == 0 && right == 0)
        return;
    
    glm::vec3 newDirection = cam_r * (float)right + vpn * (float)forward;
    
    newDirection = glm::normalize(newDirection);
    
    vrp += newDirection * deltaTime * 0.001f;
    


}

glm::mat4 Camera::GetCamera()
{
    

    return glm::lookAt(vrp, vrp + vpn, vup);
}