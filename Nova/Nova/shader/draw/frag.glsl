#shader fragment
#version 450

in GF {
	vec4 colour;
} geo;

out vec4 FragColor;

void main() {
	FragColor = geo.colour;
}
