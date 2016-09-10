#version 430

smooth in vec2 texCoord;
smooth in vec3 worldPosition;
smooth in vec3 eyeSpacePosition;

layout(location = 0) out vec4 outputColor;

uniform float alphaMin = 0.25;
uniform float alphaMultiplier = 1.5;

uniform sampler2D gSampler;
uniform vec4 color;

void main()
{
	vec4 textureColor = texture(gSampler, texCoord);

	float newAlpha = textureColor.a * alphaMultiplier;
	if (newAlpha < alphaMin) discard;

	if (newAlpha > 1.0) newAlpha = 1.0;

	vec4 mixedColor = textureColor * color;
	outputColor = vec4(mixedColor.xyz, newAlpha);
}