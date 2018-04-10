#version 410 core

in vec2 UV;
in vec3 frag_color;

out vec3 color;

uniform sampler2D texture_sample;
uniform float alpha1;
uniform float alpha2;

void main () {
	color = (texture(texture_sample, UV).rgb * alpha2) + (frag_color * alpha1);
}
