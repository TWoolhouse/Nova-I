#shader geometry
#version 450

layout(points) in;
layout(triangle_strip, max_vertices = 4) out;

in VG {
	vec2 size;
	vec4 colour;
} vertex[];

out GF {
	vec4 colour;
} frag;

void main() {
	frag.colour = vertex[0].colour;

	gl_Position = gl_in[0].gl_Position + vec4(vec2(-0.5, 0.5) * vertex[0].size, 0.0, 0.0);
	EmitVertex();
	gl_Position = gl_in[0].gl_Position + vec4(vec2(0.5, 0.5) * vertex[0].size, 0.0, 0.0);
	EmitVertex();
	gl_Position = gl_in[0].gl_Position + vec4(vec2(-0.5, -0.5) * vertex[0].size, 0.0, 0.0);
	EmitVertex();
	gl_Position = gl_in[0].gl_Position + vec4(vec2(0.5, -0.5) * vertex[0].size, 0.0, 0.0);
	EmitVertex();

	EndPrimitive();
}
