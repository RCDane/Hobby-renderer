#include "AABB.h"
#include "LineDrawer.h"
AABB::AABB(std::vector<Vertex> vertices, glm::mat4 model)
{
    int size = vertices.size();
    float xmin = 0.0;
    float xmax = 0.0;
    float ymin = 0.0;
    float ymax = 0.0; 
    float zmin = 0.0;
    float zmax = 0.0; 

    for (int i = 0; i < size; i++){
        glm::vec3 v = glm::vec4(vertices[i].Position,1.0f);
        xmin = xmin > v.x ? v.x : xmin;
        ymin = ymin > v.y ? v.y : ymin;
        zmin = zmin > v.z ? v.z : zmin;
        xmax = xmax < v.x ? v.x : xmax;
        ymax = ymax < v.y ? v.y : ymax;
        zmax = zmax < v.z ? v.z : zmax;
    }
    this->max = glm::vec3(xmax, ymax, zmax);
    this->min = glm::vec3(xmin,ymin,zmin);
}
const std::vector<glm::ivec2> edges ={
    glm::ivec2(0,1),
    glm::ivec2(0,3),
    glm::ivec2(0,4),
    glm::ivec2(2,1),
    glm::ivec2(2,3),
    glm::ivec2(2,7),
    glm::ivec2(6,3),
    glm::ivec2(6,4),
    glm::ivec2(6,7),
    glm::ivec2(5,1),
    glm::ivec2(5,4),
    glm::ivec2(5,7)
};
const std::vector<glm::vec3> positions = {
    glm::vec3(0.0,0.0,0.0),
    glm::vec3(1.0,0.0,0.0),
    glm::vec3(0.0,1.0,0.0),
    glm::vec3(1.0,1.0,0.0),
    glm::vec3(0.0,0.0,1.0),
    glm::vec3(1.0,0.0,1.0),
    glm::vec3(0.0,1.0,1.0),
    glm::vec3(1.0,1.0,1.0),
};
void AABB::Render(glm::mat4 model, glm::mat4 view, glm::mat4 projection){
    std::vector<glm::vec3> vbuffer;
    glm::vec3 min = this->min; 
    glm::vec3 maxDiff = this->max - min;
    for (int i = 0; i<edges.size(); i++){
        vbuffer.emplace_back(min + positions[edges[i].x]* maxDiff);
        vbuffer.emplace_back(min + positions[edges[i].y]* maxDiff);
    }
    LineDrawer line = LineDrawer();
    line.DrawLines(vbuffer, model,view, projection);

    vbuffer.clear();
}