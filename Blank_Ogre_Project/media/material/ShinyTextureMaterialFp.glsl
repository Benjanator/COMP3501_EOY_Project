#version 400

// Attributes passed from the vertex shader
in vec3 position_interp;
in vec3 normal_interp;
in vec4 colour_interp;
in vec2 uv_interp;
in vec3 light_pos[2];

out vec4 fragColor;

// Attributes passed with the material file
uniform vec4 ambient_colour;
uniform vec4 diffuse_colour;
uniform vec4 specular_colour;
uniform vec4 diffuse_colour_2;
uniform vec4 specular_colour_2;
uniform float ambient_amount;
uniform float phong_exponent;
uniform sampler2D diffuse_map;

uniform int choice;

void blinnPhong();
void phong();
void toonShading_1();
void toonShading_2();

void blinnPhong()
{
	 // Blinn–Phong shading

    vec3 N, // Interpolated normal for fragment
	     L, // Light-source direction
		 V, // View direction
		 H; // Half-way vector

	// Compute Lambertian lighting
    N = normalize(normal_interp);

	L = (light_pos[0] - position_interp);
	L = normalize(L);

	float lambertian_amount = max(dot(N, L), 0.0);
	
	// Compute specular term for Blinn–Phong shading
	V = - position_interp; // Eye position is (0, 0, 0)
    V = normalize(V);

    H = 0.5*(V + L);
    H = normalize(H);

    float spec_angle_cos = max(dot(N, H), 0.0);
	float specular_amount = pow(spec_angle_cos, phong_exponent);
	    
	// Retrieve texture value
	vec4 pixel = texture(diffuse_map, uv_interp);

	// Use texture in determining fragment colour
	//gl_FragColor = pixel;
	//gl_FragColor = (ambient_amount + lambertian_amount)*pixel + specular_amount*specular_colour;
	fragColor = (ambient_amount + lambertian_amount)*pixel + specular_amount*specular_colour;
	//gl_FragColor = (ambient_amount + lambertian_amount + specular_amount)*pixel;
}

void phong()
{
	// Phong shading

	vec4 diffu = vec4(0.0);
	vec4 spec = vec4(0.0);

	vec3 V, //view direction
		 L, //Light-source direction
		 N, //surface normal
		 R; //reflection direction

	N = normalize(normal_interp);
	V = normalize(-position_interp);

	vec4 total = vec4(0.0);

	for(int i = 0; i < 2; i++){
		L = normalize(light_pos[i] - position_interp);

		R = -L + 2 * max(dot(L, N), 0.0) * N;
		R = normalize(R);
		
		float Id = ambient_amount + max(dot(N, L), 0.0);
		float Is = pow(max(dot(V, R),0.0), phong_exponent); 

		if(i == 0){
			//total += Id*diffuse_colour + Is*specular_colour;
			diffu += Id*diffuse_colour;
			spec += Is*specular_colour;
			//diffu += Id;
			//spec += Is;
		}
		else{
			//total += Id*diffuse_colour_2 + Is*specular_colour_2;
			diffu += Id*diffuse_colour_2;
			spec += Is*specular_colour_2;
			//diffu += Id;
			//spec += Is;
		}
	}

	vec4 pixel = texture(diffuse_map, uv_interp);

	//fragColor = total * pixel;
	fragColor = diffu*pixel + 5.0*spec;
	//fragColor = pixel + 5.0*spec;
}

void toonShading_1()
{
	vec3 V,
		 L,
		 N,
		 R;

	N = normalize(normal_interp);

	V = normalize(-position_interp);

	
		L = normalize(light_pos[0] - position_interp);

		R = (-L) + (2 * (max(dot(L, N), 0.0)) * N);
		R = normalize(R);

		
		float intensity = dot(L, N);

		//float intensity;
		vec4 pixel = vec4(0.0, 0.0, 0.0, 0.0);


	float thresh = dot(V, N);

	if(intensity > 0.95){
		pixel = vec4(1.0, 0.5, 0.5, 1.0);
	}
	else if(intensity > 0.5){
		pixel = vec4(0.6, 0.3, 0.3, 1.0);
	}
	else if(intensity > 0.25){
		pixel = vec4(0.4, 0.2, 0.2, 1.0);
	}
	else{
		pixel = vec4(0.2, 0.1, 0.1, 1.0);
	}

	if(thresh > 0.99){
		pixel = vec4(1.0, 1.0, 1.0, 1.0);
	}
	else if(thresh > 0.45 && thresh < 0.55){
		pixel = vec4(0.1, 0.9, 0.9, 1.0);
	}
	else if(thresh < 0.25){
		pixel = vec4(0.0, 0.0, 0.0, 1.0);
	}

	//gl_FragColor = pixel;
	//vec4 pixel_f = texture(diffuse_map, uv_interp);
	fragColor = pixel ;//* pixel_f;
}

void toonShading_2()
{
	vec3 V,
		 L,
		 N,
		 R;

	N = normalize(normal_interp);

	V = normalize(-position_interp);

	L = normalize(light_pos[0] - position_interp);

	R = (-L) + (2 * (max(dot(L, N), 0.0)) * N);
	R = normalize(R);

	//float intensity;
	vec4 pixel = vec4(0.0, 0.0, 0.0, 0.0);

	float intensity = dot(L, N);

	float thresh = dot(V, N);

	if(intensity > 0.98){
		pixel = vec4(1.0, 0.5, 0.65, 1.0);
	}
	else if(intensity > 0.90){
		pixel = vec4(0.9, 0.6, 0.2, 1.0);
	}
	else if(intensity > 0.80){
		pixel = vec4(0.9, 0.5, 0.25, 1.0);
	}
	else if(intensity > 0.70){
		pixel = vec4(0.8, 0.55, 0.3, 1.0);
	}
	else if(intensity > 0.60){
		pixel = vec4(0.9, 0.6, 0.2, 1.0);
	}
	else if(intensity > 0.5){
		pixel = vec4(0.6, 0.3, 0.3, 1.0);
	}
	else if(intensity > 0.25){
		pixel = vec4(0.4, 0.2, 0.2, 1.0);
	}
	else{
		pixel = vec4(0.2, 0.1, 0.1, 1.0);
	}

	if(thresh < 0.25){
		pixel = vec4(0.0, 0.0, 0.0, 1.0);
	}

	//gl_FragColor = pixel;
	fragColor = pixel;
}

void main() 
{
   /*if(choice == 1){
		blinnPhong();
	}
	else if(choice == 2){
		toonShading_1();
	}
	else if(choice == 3){
		toonShading_2();
	}
	else{
		phong();
	}*/
	blinnPhong();
}