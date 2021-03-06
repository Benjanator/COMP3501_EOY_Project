#version 400

// Attributes passed from the geometry shader
in vec4 frag_colour;
in vec2 tex_coord;

// Attributes passed with the material file
uniform vec3 object_colour;
uniform sampler2D tex_samp;


void main (void)
{
	// Get pixel from texture
	vec4 outval = texture(tex_samp, tex_coord);
	// Adjust specified object colour according to the grayscale texture value
    outval = vec4(outval.r*frag_colour.r, outval.g*frag_colour.g, outval.b*frag_colour.b, sqrt(sqrt(outval.r))*frag_colour.a);
    //outval = vec4(outval.r*frag_colour.r, outval.g*frag_colour.g, outval.b*frag_colour.b, 0.75);
	gl_FragColor = outval;
}