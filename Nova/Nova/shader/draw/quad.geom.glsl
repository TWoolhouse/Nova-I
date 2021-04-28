#shader geometry
#version 450

layout(points) in;
layout(triangle_strip, max_vertices = 4) out;

in VG {
	mat4 mat;
	vec4 colour;
} vertex[];

out GF {
	vec4 colour;
} frag;

void main() {
	frag.colour = vertex[0].colour;

	gl_Position = vertex[0].mat * vec4(-0.5,  0.5, 0.0, 1.0); // vertex[0].mat
	EmitVertex();
	gl_Position = vertex[0].mat * vec4( 0.5,  0.5, 0.0, 1.0); // vertex[0].mat
	EmitVertex();
	gl_Position = vertex[0].mat * vec4(-0.5, -0.5, 0.0, 1.0); // vertex[0].mat
	EmitVertex();
	gl_Position = vertex[0].mat * vec4( 0.5, -0.5, 0.0, 1.0); // vertex[0].mat
	EmitVertex();

	EndPrimitive();
}
