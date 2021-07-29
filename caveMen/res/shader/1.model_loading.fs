#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

// texture samplers
uniform sampler2D texture_diffuse1;
//uniform sampler2D texture_specular1;

void main()
{
	// linearly interpolate between both textures (80% container, 20% awesomeface)
	FragColor = texture(texture_diffuse1, TexCoords);
}