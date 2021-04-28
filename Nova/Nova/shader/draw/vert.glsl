#shader vertex
#version 450

layout(location = 0) in mat4 v_mat;
layout(location = 4) in vec4 v_colour;

out VG {
	mat4 mat;
	vec4 colour;
} geo;

void main() {
	geo.mat = v_mat;
	geo.colour = v_colour;
}
