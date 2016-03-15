#version 430

uniform sampler2D gSampler;
uniform vec4 color;

in vec2 textureCoord;

out vec4 outputColor;

void main()
{
	vec4 texColor = texture(gSampler, textureCoord);
	outputColor = texColor.x * color;
}