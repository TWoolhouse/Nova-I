#shader fragment
#version 450

layout(binding = 0) buffer test {
	int mult;
	float data[100];
};

in VF {
	vec3 colour;
	vec2 texture_pos;
} vertex ;

uniform sampler2D u_tex;

out vec4 FragColor;

void main() {
	FragColor = texture(u_tex, vertex.texture_pos) * vec4(vertex.colour, 1.0) * data[int(vertex.colour.z * 100 + mult)];
}
