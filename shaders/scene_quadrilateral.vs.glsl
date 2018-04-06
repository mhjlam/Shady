#version 450 core

in vec2 position;
in vec2 texcoord;
in vec3 color;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 Color;
out vec2 Texcoord;

void main()
{
	Color = color;
    Texcoord = texcoord;
    gl_Position = projection * view * model * vec4(position, 0.0, 1.0);
    //gl_Position = view * model * vec4(position, 0.0, 1.0);
}
