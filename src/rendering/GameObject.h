#include "Model.h"
#include "Material.h"
#include "glm/common.hpp"
#include "AABB.h"
#include "Model.h"
class Transform{
public:
    Transform(glm::vec3 position = glm::vec3(0.,0.,0.), glm::vec3 rotation= glm::vec3(0.,0.,0.), glm::vec3 = glm::vec3(1.,1.,1.));
    glm::mat4 GetTransform();
    glm::mat4 GetPosition();
    glm::mat4 GetRotation();
    glm::mat4 GetScale();
    glm::mat3 GetNormalMatrix();
    void SetPosition(glm::vec3 position);
    void setRotation(glm::vec3 rotation);
    
    void setScale(glm::vec3 scale);
private:
    glm::vec3 position, rotation, scale;
};

class GameObject {
private:
    AABB* aabb;
public:
    GameObject(Model* model,Material *material, glm::vec3 position = glm::vec3(0.,0.,0.), glm::vec3 rotation= glm::vec3(0.,0.,0.), glm::vec3 = glm::vec3(1.,1.,1.));
    void Render();
    void RenderAABB(glm::mat4 view, glm::mat4 projection);
    glm::mat4 GetTransform();
    glm::mat4 GetPosition();
    glm::mat4 GetRotation();
    glm::mat4 GetScale();
private:
    Transform transform;
    Material* material;
    Model* model;
};
