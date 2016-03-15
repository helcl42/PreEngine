#version 430

uniform sampler2D gSampler;

smooth in vec2 textureCoord;
flat in vec4 colorPart;

out vec4 FragColor;

void main()
{
	vec4 textureColor = texture(gSampler, textureCoord);
	FragColor = vec4(textureColor.xyz, 1.0) * colorPart;
}