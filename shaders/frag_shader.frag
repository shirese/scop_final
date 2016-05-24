#version 410 core

in vec3 vp_word;
in vec3 vn_cam;
in vec3 eye_dir_cam;
in vec3 light_dir_cam;

out vec4 frag_colour;

void main () {
	vec3 light_color = vec3(1, 1, 1);
	float light_pow = 50.0f;

	vec3 diffuse_color = vec3(0.4, 0.4, 0.5);
	vec3 ambient_color = vec3(0.1, 0.1, 0.1);
	vec3 spec_color = vec3(0.3, 0.3, 0.3);

	float dist = length( light_pos - vp_word);

	vec3 n = normalize( vn_cam );
	vec3 l = normalize( light_dir_cam );
	float cos_theta = clamp( dot( n, l ), 0, 1 );

	vec3 e = normalize( eye_dir_cam );
	vec3 r = reflect( -l, n );
	float cos_alpha = clamp( dot( e, r ), 0, 1 );

	frag_color = ambient_color + 
			diffuse_color * light_color * light_pow * cos_theta / (dist * dist) +
			spec_color * light_color * light_pow * pow( cos_alpha, 5 ) / (dist * dist);
	// o_frag_colour = vec4 (0.4, 0.4, 0.5, 1.0);
}
