#include "LineDrawer.h"
#include "string"
#include "stdlib.h"
#include "Shader.h"
#include "gl/GL.h"
#include "vector"
#include "glm/common.h"
LineDrawer::LineDrawer(std::string fragment_shader, std::string vertex_shader){
    Shader program = new Shader("line.vert", "line.frag");
    this->shader = program;
}

LineDrawer::DrawLines(std::vector<glm::vec3> points){
    
}