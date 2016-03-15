#version 430

smooth in vec2 textureCoord;
smooth in vec3 normal;
smooth in vec3 worldPosition;
smooth in vec4 eyeSpacePosition;

layout(location = 0) out vec4 outputColor;

uniform sampler2D gSampler;
uniform vec4 scale;
uniform vec4 bias;

void main()
{
	vec4 textureColor = texture(gSampler, textureCoord);

	outputColor = max(vec4(0.0), textureColor + bias) * scale;
}

