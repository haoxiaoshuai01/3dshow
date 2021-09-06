#version 330 core
out vec4 FragColor;

in vec3 fColor;
in vec2 TexCoord;
uniform sampler2D texture_diffuse1;

void main()
{
    vec4 color = texture(texture_diffuse1,TexCoord);   
	if(color.w < 0.1)
		discard;
	 FragColor = color;
}