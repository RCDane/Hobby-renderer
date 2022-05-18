#version 330

in vec3 o_position;
in vec2 o_texcoord;

out vec4 FragColor;

uniform sampler2D tex_sampler;

void main()
{   
	vec4 finalColor = texture(tex_sampler, o_texcoord);
	if (finalColor.a < 0.01f)
		discard;
	FragColor = vec4(finalColor.xyz, 1.0f);
}