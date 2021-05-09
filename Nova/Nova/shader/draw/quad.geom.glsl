#shader geometry
#version 450

layout(points) in;
layout(triangle_strip, max_vertices = 4) out;

in VG {
	mat4 mat;
	vec4 colour;
	flat int texture;
	vec2 tex_pos[4];
} vertex[];

out GF {
	vec4 colour;
	flat int texture;
	vec2 tex_pos;
} frag;

void main() {
	frag.colour = vertex[0].colour;
	frag.texture = vertex[0].texture;

	frag.tex_pos = vertex[0].tex_pos[2];
	gl_Position = vertex[0].mat * vec4(-0.5,  0.5, 0.0, 1.0);
	EmitVertex();

	frag.tex_pos = vertex[0].tex_pos[3];
	gl_Position = vertex[0].mat * vec4( 0.5,  0.5, 0.0, 1.0);
	EmitVertex();

	frag.tex_pos = vertex[0].tex_pos[0];
	gl_Position = vertex[0].mat * vec4(-0.5, -0.5, 0.0, 1.0);
	EmitVertex();

	frag.tex_pos = vertex[0].tex_pos[1];
	gl_Position = vertex[0].mat * vec4( 0.5, -0.5, 0.0, 1.0);
	EmitVertex();

	EndPrimitive();
}
