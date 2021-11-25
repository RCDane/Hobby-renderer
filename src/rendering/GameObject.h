#include "Model.h"
#include "Material.h"
#include "glm/common.hpp"
#include "Model.h"
class Transform{
public:
    Transform(glm::vec3 position = glm::vec3(0.,0.,0.), glm::vec3 rotation= glm::vec3(0.,0.,0.), glm::vec3 = glm::vec3(1.,1.,1.));
    glm::mat4 GetTransform();
    
    void SetPosition(glm::vec3 position);
    void setRotation(glm::vec3 rotation);
    void setScale(glm::vec3 scale);
private:
    glm::vec3 position, rotation, scale;
};

class GameObject {
public:
    GameObject(Model* model,Material *material, glm::vec3 position = glm::vec3(0.,0.,0.), glm::vec3 rotation= glm::vec3(0.,0.,0.), glm::vec3 = glm::vec3(1.,1.,1.));
    void Render();
private:
    Transform transform;
    Material* material;
    Model* model;
};
