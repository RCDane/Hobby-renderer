#version 430

out vec4

uniform vec3 color;
int main(){
	fragColor = vec4(color, 1.0f);
}