#version 330

// Input
in vec2 texcoord;

// Uniform properties
uniform sampler2D texture_1;
uniform sampler2D texture_2;
uniform bool mix_textures;
// TODO(student): Declare various other uniforms

// Output
layout(location = 0) out vec4 out_color;


void main()
{
    // TODO(student): Calculate the out_color using the texture2D() function.
    vec4 color = texture2D(texture_1, texcoord);
	out_color = color;
	
	
	if (out_color.a < 0.5f)
	{
		discard;
	}

}
