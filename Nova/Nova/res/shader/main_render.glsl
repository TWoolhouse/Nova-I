#shader vertex
#version 450

layout(location = 0) in vec2 v_pos;
layout(location = 1) in vec2 v_tex;

out VF {
	vec2 texture_pos;
} frag ;

void main() {
	frag.texture_pos = v_tex;
	gl_Position = vec4(v_pos, 0.0, 1.0);
}

#shader fragment
#version 450

in VF {
	vec2 texture_pos;
} vertex ;

uniform sampler2D u_tex;

out vec4 FragColor;

void main() {
	FragColor = texture(u_tex, vertex.texture_pos);
}
