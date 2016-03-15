#version 430

smooth in vec2 textureCoord;

layout(location = 0) out vec4 outputColor;

uniform sampler2D gSampler;
uniform vec4 color;

void main()
{
	vec4 textureColor = texture(gSampler, textureCoord);
	outputColor = textureColor * color;
}