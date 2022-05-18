#version 430

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec3 texcoord;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoords;
	
uniform mat4 world;
uniform mat4 viewProj;
uniform mat3 normalMatrix;
	
void main()
{
    FragPos = vec3(world * vec4(position, 1.0f));
    Normal   = normalMatrix * normal;
    TexCoords = texcoord.xy;
	
    gl_Position = viewProj * world * vec4(position, 1.0f);
}