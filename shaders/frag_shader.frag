#version 410 core

in vec3 vp_world;
// in vec3 vn_cam;
// in vec3 eye_dir_cam;
// in vec3 light_dir_cam;

// in vec2 uv;
in vec2 UV;
in vec3 frag_color;

out vec3 color;

uniform sampler2D texture_sample;
uniform float alpha1;
uniform float alpha2;
// uniform vec3 light;

void main () {
	// color = frag_color;
	// color = texture(texture_sample, uv).rgb;
	color = (texture(texture_sample, UV).rgb * alpha1) + (frag_color * alpha2);

	// vec3 light_color = vec3(1.0, 1.0, 1.0);
	// float light_pow = 50.0f;

	// vec3 diffuse = vec3(0.64f, 0.64f, 0.64f);
	// vec3 ambient_color = vec3(0.3, 0.3, 0.3) * diffuse;
	// vec3 spec_color = vec3(0.3, 0.3, 0.3);

	// float dist = length(light - vp_world);


	// vec3 n = normalize( vn_cam );
	// vec3 l = normalize( light_dir_cam );
	// float cos_theta = clamp( dot( n, l ), 0, 1 );

	// vec3 e = normalize( eye_dir_cam );
	// vec3 r = reflect( -l, n );
	// float cos_alpha = clamp( dot( e, r ), 0, 1 );

	// diffuse *= light_color * light_pow;
	// diffuse *= light_color * light_pow * cos_theta / (dist * dist);
	// spec_color *= light_color * light_pow;
	// spec_color *= light_color * light_pow * pow(cos_alpha, 5.0) / (dist * dist);
	// frag_color = ambient_color + diffuse + spec_color;

	// frag_color = ambient_color +
	// 		diffuse * light_color * light_pow * cos_theta / (dist * dist) +
	// 		spec_color * light_color * light_pow * pow( cos_alpha, 5 ) / (dist * dist);
	// o_frag_colour = vec4 (0.4, 0.4, 0.5, 1.0);
}
