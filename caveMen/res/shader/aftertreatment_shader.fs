#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D screenTexture;

// 0 = normal 1 = light change  2Gaussian Blur
uniform int type;
vec3 Inversion()
{
	return vec3(1.0 - texture(screenTexture, TexCoords));
}
vec3 Grayscale()
{
	vec3 col = texture(screenTexture, TexCoords).rgb;
    float average = (col.r + col.g + col.b) / 3.0;
    return vec3(average, average, average);
}
vec3 Grayscale2()
{
	vec3 col = texture(screenTexture, TexCoords).rgb;
    float average = 0.2126 * col.r + 0.7152 * col.g + 0.0722 * col.b;
    return vec3(average, average, average);
}
vec3 convolution( float kernel[9])
{
	const float offset = 1.0 / 300.0;
	vec2 offsets[9] = vec2[](
        vec2(-offset,  offset), // 左上
        vec2( 0.0f,    offset), // 正上
        vec2( offset,  offset), // 右上
        vec2(-offset,  0.0f),   // 左
        vec2( 0.0f,    0.0f),   // 中
        vec2( offset,  0.0f),   // 右
        vec2(-offset, -offset), // 左下
        vec2( 0.0f,   -offset), // 正下
        vec2( offset, -offset)  // 右下
    );
    vec3 sampleTex[9];
    for(int i = 0; i < 9; i++)
    {
        sampleTex[i] = vec3(texture(screenTexture, TexCoords.xy + offsets[i]));
    }
    vec3 col = vec3(0.0);
    for(int i = 0; i < 9; i++)
        col += sampleTex[i] * kernel[i];

		return col;
}
vec3 GaussianBlur()
{

	float kernel[9] = float[](
		1.0 / 16, 2.0 / 16, 1.0 / 16,
		2.0 / 16, 4.0 / 16, 2.0 / 16,
		1.0 / 16, 2.0 / 16, 1.0 / 16  
	);

	return convolution(kernel);
}

vec3 Sharpen()
{
	float kernel[9] = float[](
			-1, -1, -1,
			-1,  9, -1,
			-1, -1, -1
		);

	return  convolution(kernel);
}

void main()
{
	
	vec3 middleValue;

	if(type == 3)
	{
		middleValue = Grayscale();
	}else if(type == 2)
	{
		middleValue = Inversion();

	}else if(type == 1)
	{
		middleValue = texture(screenTexture, TexCoords).rgb*0.5;
		
	}else if(type == 4)
	{
		middleValue = Grayscale2();
	}else if(type == 5)
	{
		middleValue = Sharpen();
	}else if(type == 6)
	{
		middleValue = GaussianBlur();
	}else
	{
		middleValue=  texture(screenTexture, TexCoords).rgb;
	}
	
	FragColor =vec4(middleValue,1.0);
}