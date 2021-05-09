#shader fragment
#version 450

in GF {
	vec4 colour;
	flat int texture;
	vec2 tex_pos;
} geo;

uniform sampler2D textures[64];

out vec4 FragColor;

void main() {
	FragColor = texture2D(textures[geo.texture], geo.tex_pos) * geo.colour;
}
