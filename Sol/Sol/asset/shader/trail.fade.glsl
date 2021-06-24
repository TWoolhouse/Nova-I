#shader compute
#version 450

layout(local_size_x = 64, local_size_y = 18, local_size_z = 1) in;
layout(rgba32f, binding = 0) uniform volatile image2D output_image;
uniform float dt;
uniform float u_fade;
uniform float u_diffuse;

void main() {
	ivec2 img_size = imageSize(output_image);
	ivec2 p_coords = ivec2(gl_GlobalInvocationID.xy);

	vec4 original = imageLoad(output_image, p_coords);
	vec4 avg = vec4(0.0);
	for (int x = -1; x < 2; ++x) {
		for(int y = -1; y < 2; ++y){
			ivec2 pos = p_coords + ivec2(x, y);
			if (pos.x >= 0 && pos.x < img_size.x && pos.y >= 0 && pos.y < img_size.y) {
				avg += imageLoad(output_image, pos);
			} else {
				// imageStore(output_image, p_coords, vec4(1.0f));
			}
		}
	}

	vec4 diffused = mix(original, avg / 9.0f, u_diffuse * dt);
	vec4 evaporated = max(diffused - vec4(vec3(0.0), u_fade * dt), vec4(0.0));

	imageStore(output_image, p_coords, evaporated);
}
