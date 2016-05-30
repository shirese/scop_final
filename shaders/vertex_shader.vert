#version 410 core
layout(location = 0) in vec3 vp;
layout(location = 1) in vec3 vc;
layout(location = 2) in vec2 uv;

out vec3 vp_world;
out vec3 frag_color;
out vec2 UV;
// out vec3 vn_cam;
// out vec3 eye_dir_cam;
// out vec3 light_dir_cam;

uniform mat4 mat_m;
uniform mat4 mat_v;
uniform mat4 mat_mvp;

// uniform vec3 light;

void main () {
	gl_Position = mat_mvp * vec4(vp, 1.0);

	vp_world = (mat_m * vec4(vp, 1.0)).xyz;

	frag_color = vc;
	// uv = (gl_Position.xy / gl_Position.w) * 0.5 + 0.5;
	UV = uv;

	// vec3 vp_cam = (mat_v * mat_m * vec4(vp, 1.0)).xyz;
	// eye_dir_cam = vec3(0.0, 0.0, 0.0) - vp_cam;

	// vec3 light_pos_cam = (mat_v * vec4(light, 1.0)).xyz;
	// light_dir_cam = light_pos_cam * eye_dir_cam;

	// vn_cam = ( mat_v * mat_m * vec4(vn, 0.0)).xyz;

}
