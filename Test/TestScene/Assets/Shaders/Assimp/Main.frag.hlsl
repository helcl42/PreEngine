#version 430

smooth in vec2 textureCoord;
smooth in vec3 normal;
smooth in vec3 worldPosition;
smooth in vec4 eyeSpacePosition;
smooth in vec4 shadowCoord;
in vec3 lightDirectionTangentSpace;

layout(location = 0) out vec4 outputColor;

#include "../Effects/Shadows.frag.hlsl"
#include "../Light/Light.frag.hlsl"

uniform Shadows shadows;
uniform DirectionalLight sunLight;
uniform bool bumpMapEnabled;
uniform Material activeMaterial;
uniform vec3 eyePosition;

uniform sampler2D gSampler;
uniform sampler2D gNormalMap;
uniform vec4 color;

subroutine void RenderPassType();
subroutine uniform RenderPassType RenderPass;


subroutine(RenderPassType)
void ShadeWithShadow()
{
	vec4 textureColor = texture(gSampler, textureCoord);
	vec4 mixedColor = textureColor * color;

	float shadow = GetVisibility(shadows, shadowCoord);

	vec3 normalizedNormal = normalize(normal);

	vec4 specularLightColor = GetSpecularLightColor(worldPosition, eyePosition, normalizedNormal, activeMaterial, sunLight);	

	if (bumpMapEnabled)
	{
		vec3 normalExtr = normalize(texture(gNormalMap, textureCoord).rgb * 2.0 - 1.0);
		float diffuseIntensity = max(0.0, dot(normalExtr, -lightDirectionTangentSpace));
		float mult = clamp(diffuseIntensity + sunLight.ambientIntensity, 0.0, 1.0);
		vec4 diffuseLightColor = vec4(sunLight.color * mult, 1.0);
		outputColor = mixedColor * (specularLightColor + diffuseLightColor) * shadow;
	}
	else
	{
		vec4 ambientLightColor = GetAmbientLightColor(sunLight);
		vec4 diffuseLightColor = GetDiffuseLightColor(worldPosition, normalizedNormal, sunLight);		
		outputColor = mixedColor * ((specularLightColor + diffuseLightColor) * shadow + ambientLightColor);
	}	

	//outputColor = vec4(shadow, shadow, shadow, 1.0);
}

subroutine(RenderPassType)
void RecordDepth()
{
	// Do nothing, depth will be written automatically
}

void main() 
{
	// This will call either ShadeWithShadow or RecordDepth
	RenderPass();
}

