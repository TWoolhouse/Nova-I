#shader vertex
#version 450

layout(location = 0) in mat4 v_mat;
layout(location = 4) in vec4 v_colour;
layout(location = 5) in float texture;
layout(location = 6) in vec2 v_tex_pos[4];

out VG {
	mat4 mat;
	vec4 colour;
	flat int texture;
	vec2 tex_pos[4];
} geo;

void main() {
	geo.mat = v_mat;
	geo.colour = v_colour;
	geo.texture = int(texture);
	geo.tex_pos = v_tex_pos;
}
