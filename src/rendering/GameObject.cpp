#include "GameObject.h"
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/matrix.hpp>
Transform::Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale ){
    this->position = position;
    this->rotation = rotation;
    this->scale = scale;
}

glm::mat4 Transform::GetTransform(){
    glm::mat4 model = glm::mat4(1.f);
    glm::mat4 scale = glm::scale(model,this->scale);
    glm::mat4 translation = glm::translate(scale, this->position);
    
    return translation;
}
void Transform::SetPosition(glm::vec3 position){
    this->position = position;
}
void Transform::setRotation(glm::vec3 rotation){
    this->rotation = rotation;
}


void Transform::setScale(glm::vec3 scale){
    this->scale = scale;
}

void  GameObject::Render(){
    this->material->BindParameters();
    Shader* s = this->material->GetShader();
    glm::mat4 m = this->transform.GetTransform();
    s->setUniformMatrix4fv("model", m);
    //  this->material->PrepareShader();
    this->model->Draw();
    
}

GameObject::GameObject(Model* model,Material* material,glm::vec3 position, glm::vec3 rotation, glm::vec3 scale){
    this->transform = Transform(position,rotation, scale);
    this->model = model;
    this->material = material;
}