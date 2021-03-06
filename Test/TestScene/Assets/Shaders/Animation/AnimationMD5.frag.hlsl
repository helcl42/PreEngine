#version 430

smooth in vec2 textureCoord;
smooth in vec3 normal;
smooth in vec3 worldPosition;
smooth in vec4 eyeSpacePosition;
smooth in vec4 shadowCoord;

layout(location = 0) out vec4 outputColor;

#include "../Effects/Shadows.frag.hlsl"
#include "../Light/Light.frag.hlsl"

uniform DirectionalLight sunLight;
uniform Material activeMaterial;
uniform vec3 eyePosition;
uniform sampler2D gSampler;
uniform vec4 color;
uniform Shadows shadows;

subroutine void RenderPassType();
subroutine uniform RenderPassType RenderPass;

subroutine(RenderPassType)
void ShadeWithShadow()
{
	float shadow = GetVisibility(shadows, shadowCoord);

	vec4 textureColor = texture(gSampler, textureCoord);
	vec4 mixedColor = textureColor * color;
	vec3 normalizedNormal = normalize(normal);
	vec4 specularLightColor = GetSpecularLightColor(worldPosition, eyePosition, normalizedNormal, activeMaterial, sunLight);
	vec4 ambientLightColor = GetAmbientLightColor(sunLight);
	vec4 diffuseLightColor = GetDiffuseLightColor(worldPosition, normalizedNormal, sunLight);
	
	outputColor = mixedColor * ((diffuseLightColor + specularLightColor) * shadow + ambientLightColor);
}

subroutine(RenderPassType)
void RecordDepth()
{
	// Do nothing, depth will be written automatically
}

void main()
{
	RenderPass();
}