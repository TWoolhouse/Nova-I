#shader vertex
#version 450

layout(location = 0) in vec2 v_pos;
layout(location = 1) in vec2 v_size;
layout(location = 2) in vec4 v_colour;

out VG {
	vec2 size;
	vec4 colour;
} geo;

void main() {
	geo.size = v_size;
	geo.colour = v_colour;
	gl_Position = vec4(v_pos, 0.0, 1.0);
}
