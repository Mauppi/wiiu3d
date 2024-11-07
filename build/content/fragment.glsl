#version 330 core

// Interpolated values from the vertex shaders
in vec2 UV;

// Ouput data
out vec4 color;

// Values that stay constant for the whole mesh.
uniform sampler2D myTextureSampler;
uniform vec4 modulate;

void main(){

    // Output color = color of the texture at the specified UV
    vec4 colortemp = texture( myTextureSampler, UV ) * modulate;
    if (colortemp.a < 0.001)
        discard;
    
    color = colortemp;
}