#define GLM_ENABLE_EXPERIMENTAL

#include "GameObject.h"
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/matrix.hpp>
Transform::Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale ){
    this->position = position;
    this->rotation = rotation;
    this->scale = scale;
}

glm::mat4 Transform::GetPosition(){
    return glm::translate(glm::mat4(1.f), this->position);
}

glm::mat4 Transform::GetScale(){
    return glm::scale(glm::mat4(1.0f),scale);
}
glm::mat4 Transform::GetRotation(){
    return glm::mat4(0.0f);
}
glm::mat4 Transform::GetTransform(){
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 scale = glm::scale(model,this->scale);
    glm::mat4 translation = glm::translate(scale, this->position);
    
    return translation;
}

glm::mat3 Transform::GetNormalMatrix(){
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 scale = glm::scale(model,this->scale);
    glm::mat4 translation = glm::translate(scale, this->position);

    return glm::mat3(glm::inverse(glm::transpose(translation)));
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

glm::mat4 GameObject::GetPosition(){
    return this->transform.GetPosition();
}

glm::mat4 GameObject::GetScale(){
    return this->transform.GetScale();
}
void GameObject::RenderAABB(glm::mat4 view, glm::mat4 projection){
   
    this->aabb->Render(glm::mat4(1.0f),view,projection);
}
void  GameObject::Render(){
    this->material->BindParameters();
    Shader* s = this->material->GetShader();
    s->apply();
    glm::mat4 m = this->transform.GetTransform();
    s->setUniformMatrix4fv("model", m);
    s->setUniformMatrix3fv("normalMatrix", this->transform.GetNormalMatrix());
     this->material->PrepareShader();
    this->model->Draw();
    
}

GameObject::GameObject(Model* model,Material* material,glm::vec3 position, glm::vec3 rotation, glm::vec3 scale){
    this->transform = Transform(position,rotation, scale);
    this->model = model;
    this->aabb = new AABB(this->model->meshes[0].vertices,this->transform.GetScale()* this->transform.GetRotation());
    this->material = material;
}