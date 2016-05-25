#version 410 core

in vec3 vp_world;
in vec3 vn_cam;
in vec3 eye_dir_cam;
in vec3 light_dir_cam;

out vec3 frag_color;

uniform vec3 light;

void main () {
	vec3 light_color = vec3(1.0, 1.0, 1.0);
	float light_pow = 50.0f;

	vec3 diffuse_color = vec3(1, 1, 0);
	vec3 ambient_color = vec3(0.5, 0.5, 0.5) * diffuse_color;
	vec3 spec_color = vec3(0.3, 0.3, 0.3);

	float dist = length(light - vp_world);

	vec3 n = normalize( vn_cam );
	vec3 l = normalize( light_dir_cam );
	float cos_theta = clamp( dot( n, l ), 0, 1 );

	vec3 e = normalize( eye_dir_cam );
	vec3 r = reflect( -l, n );
	float cos_alpha = clamp( dot( e, r ), 0, 1 );

	diffuse_color *= light_color * light_pow * cos_theta / (dist * dist);
	spec_color *= light_color * light_pow * pow(cos_alpha, 5.0) / (dist * dist);
	frag_color = ambient_color + diffuse_color + spec_color;

	// frag_color = ambient_color + 
	// 		diffuse_color * light_color * light_pow * cos_theta / (dist * dist) +
	// 		spec_color * light_color * light_pow * pow( cos_alpha, 5 ) / (dist * dist);
	// o_frag_colour = vec4 (0.4, 0.4, 0.5, 1.0);
}
