#shader vertex
#version 450

layout(location = 0) in vec2 v_pos;
layout(location = 1) in vec3 v_col;
layout(location = 2) in vec2 v_tex;

out vec3 f_col;
out vec2 f_tex;

void main() {
	f_col = v_col;
	f_tex = v_tex;
	gl_Position = vec4(v_pos, 1.0, 1.0);
}
