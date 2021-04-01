#shader fragment
#version 450

in vec3 f_col;
in vec2 f_tex;

uniform sampler2D u_tex;

out vec4 FragColor;

void main() {
	FragColor = texture(u_tex, f_tex) * vec4(f_col, 1.0);
}
