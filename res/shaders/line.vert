#version 430

layout(location = 0) in vec3 position;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
int main()
{
    gl_Position = projection*view*model* position;
}
