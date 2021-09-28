#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D screenTexture;

void main()
{
	FragColor = texture(screenTexture, TexCoords);
	//vec3 col = texture(screenTexture, TexCoords).rgb;
	//vec3 grayscale = vec3(0.5 * col.r , 0.5 * col.g , 0.5 * col.b);
	//FragColor = vec4(vec3(grayscale), 1.0);
}