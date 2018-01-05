#version 400 core

in vec3 Color;
in vec2 Texcoord;

out vec4 color;

void main()
{
	color = /* texture(tex, Texcoord) * */ vec4(Color, 1.0);
}
