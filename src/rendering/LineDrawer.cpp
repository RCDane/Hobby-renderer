#include "LineDrawer.h"
#include "Shader.h"
#include "string"
#include "stdlib.h"
#include "gl/GL.h"
#include "vector"
#include "glm/common.hpp"
#include "Camera.h"
LineDrawer::LineDrawer() : shader("line.vert", "line.frag"){
    Shader program = Shader::BuildShader("line.vert", "line.frag");
    this->shader.apply();
    this->shader.setUniform3fv("color", glm::vec3(1.0,0.0,0.0));

    this->shader = program;
}

void LineDrawer::DrawLines(std::vector<glm::vec3> points,glm::mat4 model,glm::mat4 view,glm::mat4 projection){
    this->shader.apply();
    this->shader.setUniformMatrix4fv("model"     , model);
    this->shader.setUniformMatrix4fv("view"      , view);
    this->shader.setUniformMatrix4fv("projection", projection);
    
    unsigned int VBO;
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*points.size(), points.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0); 

    glBindVertexArray(VAO);
    glDrawArrays(GL_LINES, 0, points.size());
}