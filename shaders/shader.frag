#version 330

uniform vec2 resolution;
uniform vec2 mouse;

out vec4 color;

void main()
{
	vec2 v = (mouse.xy / resolution.xy);
	color = vec4(gl_FragCoord.xy / resolution.xy, (v.x + v.y) * 0.5, 1.0f);
}
