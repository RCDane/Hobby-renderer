#include "Lights.h"
#include <string>
#include <iostream>
using namespace std;  
Lights::Lights(int amount){
   this->maxNumberOfLights = amount;
   this->numberOfLights = 0;
   lights = vector<Light>();
}

bool Lights::Add(Light light){
    if(numberOfLights + 1 > maxNumberOfLights){
        return false;
    }
    lights.push_back(light);
    numberOfLights++;
    return true;
}
void Lights::Bind(Shader *shader){
   for (int i = 0; i<numberOfLights; i++){
       string s = "pointLights["+to_string(i);
       shader->setUniform3fv(s+"].position", lights[i].position);
       shader->setUniform1f( s+"].constant", lights[i].constant);
       shader->setUniform1f( s+"].linear", lights[i].linear);
       shader->setUniform1f( s+"].quadratic", lights[i].quadratic);
    //    shader->setUniform3fv(s+"].ambient", lights[i].ambient);
       shader->setUniform3fv(s+"].diffuse", lights[i].diffuse);
       shader->setUniform3fv(s+"].specular", lights[i].specular);
   }
   shader->setUniform1i("lightCount",numberOfLights);
}