#include "Material.h"
#include <gl/GL.h>
#include <string>
Material::Material(Shader* shader, Texture *diffuse, Texture *specular, float shininess){
    this->shader = shader;
    this->diffuse = diffuse;
    this->specular = specular;
    this->shininess = shininess;
}

void Material::BindParameters(){
    this->shader->setUniform1f("material.shininess", this->shininess);
    this->diffuse->bind(0);
    this->specular->bind(1);
}
Shader* Material::GetShader(){
    return this->shader;
}
void Material::PrepareShader(){
    this->shader->apply();
}