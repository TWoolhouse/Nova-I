#shader fragment
#version 450

in vec3 f_col;

out vec4 FragColor;

void main() {
	FragColor = vec4(f_col, 1.0);
}
