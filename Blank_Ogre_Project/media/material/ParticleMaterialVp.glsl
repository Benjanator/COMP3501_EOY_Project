#version 400

// Attributes passed automatically by OGRE
in vec3 vertex;
in vec3 normal;
in vec4 colour;

// Attributes passed with the material file
uniform mat4 world_mat;
uniform mat4 view_mat;
uniform mat4 normal_mat;
uniform vec3 up_vec;
uniform float timer;
uniform vec3 object_colour;

// Attributes forwarded to the geometry shader
out vec3 vertex_colour;


void main()
{
    // Let time cycle every four seconds
	//float circtime = timer - 4.0 * floor(timer / 4);
	float circtime = timer;
	float t = circtime; // Our time parameter
	
	// Settings for the explosion
	// Could also define these in the material file to have multiple particle systems with different settings
    float grav = 0.005; // Gravity
    float slow = 10.6; // Allows to slow down the explosion, control the speed of the explosion
	
	// Let's first work in model space (apply only world matrix)
	vec4 position = world_mat * vec4(vertex, 1.0);
	vec4 norm = normal_mat * vec4(normal, 1.0);

    // Move point along normal and down with t*t (acceleration under gravity)
    position.x += norm.x*t*slow ;
    position.y += norm.y*t*slow ;
    position.z += norm.z*t*slow ;
	
	// Now apply view transformation
	gl_Position = view_mat * position;
	    
	// Define color of vertex
	//vertex_colour = colour.rgb; // Color define during the construction of the particles
	vertex_colour = object_colour; // Uniform color assigned in material file
}
