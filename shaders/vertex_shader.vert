#version 410 core
layout(location = 0) in vec3 vp;
layout(location = 1) in vec3 vc;
layout(location = 2) in vec2 uv;

out vec3 frag_color;
out vec2 UV;

uniform float scale;
uniform mat4 mat_mvp;

void main () {
	gl_Position = mat_mvp * vec4(vp, 1.0);
	gl_Position.x *= scale;
	gl_Position.y *= scale;
	gl_Position.z *= scale;

	frag_color = vc;
	UV = uv;
}
