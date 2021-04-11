#shader vertex
#version 450

layout(location = 0) in vec2 v_pos;
layout(location = 1) in vec3 v_col;
layout(location = 2) in vec2 v_tex;

out VF {
	vec3 colour;
	vec2 texture_pos;
} frag ;

void main() {
	frag.colour = v_col;
	frag.texture_pos = v_tex;
	gl_Position = vec4(v_pos, 1.0, 1.0);
}

#shader fragment
#version 450

in VF {
	vec3 colour;
	vec2 texture_pos;
} vertex ;

layout(binding = 0) buffer test {
	float mult;
};

uniform sampler2D u_tex;

out vec4 FragColor;

void main() {
	FragColor = texture(u_tex, vertex.texture_pos) * vec4(vertex.colour, 1.0) * mult;
}
