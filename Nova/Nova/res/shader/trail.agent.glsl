#shader compute
#version 450

struct Agent {
	vec2 pos;
	vec2 vel;
	// vec2 acc;
};

// const uint SIZE = 1000000;

uniform float dt;
layout(local_size_x = 1024, local_size_y = 1, local_size_z = 1) in;
layout(rgba32f, binding = 0) uniform image2D output_image;
layout(binding = 1) buffer data {
	float steering;
	float scan_angle;
	float scan_dist;
	vec4 colour;
	Agent agents[];
};

void update(inout Agent agent) {
	vec2 img_size = vec2(imageSize(output_image));

	// Move to Centre
	// vec2 dir = (img_size / 2) - agent.pos;
	// float mag = sqrt(pow(dir.x, 2) + pow(dir.y, 2));
	// agent.vel = dir * speed / mag;

	agent.pos += agent.vel * dt;

	// Bounds checking
	if (agent.pos.x < 0 || agent.pos.x > img_size.x) {
		agent.pos.x = min(max(0, agent.pos.x), img_size.x);
		agent.vel.x = -agent.vel.x;
	} else if (agent.pos.y < 0 || agent.pos.y > img_size.y) {
		agent.pos.y = min(max(0, agent.pos.y), img_size.y);
		agent.vel.y = -agent.vel.y;
	}
}

mat2 rotate(float angle){
	float c = cos(angle);
	float s = sin(angle);
	return mat2(c, -s, s, c);
}

float get_sample(in ivec2 pos) {
	float avg = 0.0;
	for (int x = -2; x < 3; ++x) {
		for(int y = -2; y < 3; ++y){
			avg += imageLoad(output_image, pos).w;
		}
	}
	return avg / 9.0f;
}


void scan(inout Agent agent) {
	vec2 nvel = normalize(agent.vel);
	vec2 point_left = rotate(-scan_angle) * nvel * scan_dist + agent.pos;
	vec2 point_right = rotate(scan_angle) * nvel * scan_dist + agent.pos;
	vec2 point_centre = nvel * scan_dist + agent.pos;

	float weight_left = get_sample(ivec2(point_left));
	float weight_right = get_sample(ivec2(point_right));
	float weight_centre = get_sample(ivec2(point_centre));

	if (weight_centre > weight_right && weight_centre > weight_left) {
		;
	} else if (weight_right > weight_left) {
		agent.vel *= rotate(-scan_angle * steering * dt);
	} else if (weight_left > weight_right) {
		agent.vel *= rotate(scan_angle * steering * dt);
	}

}

void draw_circle(in ivec2 pos, in vec4 col) {
	imageStore(output_image, pos, col);
}

void draw_circle(in ivec2 pos, in vec4 col, in uint radius) {
	for (int x = -int(radius); x <= int(radius); ++x) {
		for (int y = -int(radius); y <= int(radius); ++y) {
			imageStore(output_image, pos + ivec2(x, y), col);
		}
	}
}

void main() {
	scan(agents[gl_GlobalInvocationID.x]);
	update(agents[gl_GlobalInvocationID.x]);
	ivec2 p_coords = ivec2(agents[gl_GlobalInvocationID.x].pos);
	draw_circle(p_coords, colour);
}
