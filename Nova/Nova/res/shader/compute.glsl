#shader compute
#version 450

// struct Agent {

// };

layout(local_size_x = 1, local_size_y = 1, local_size_z = 1) in;
layout(rgba32f, binding = 0) uniform image2D output_image;
layout(binding = 1) buffer test {
	float pray[100];
	vec3 lol;
};

// imageStore(output_image, pixel_coords, pixel); //vec4(gl_GlobalInvocationID.xy, 0.0, 1.0)

void main() {
	vec4 p_colour = vec4(lol, 1.0);
	ivec2 pixel_coords = ivec2(gl_GlobalInvocationID.xy);
	pray[gl_GlobalInvocationID.x] = float(gl_GlobalInvocationID.x);
	imageStore(output_image, pixel_coords, p_colour);
}
