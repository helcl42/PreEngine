#version 430

smooth in vec3 eyeSpacePosition;
smooth in vec3 normal;
smooth in vec3 worldPosition;
smooth in vec2 textureCoord;
smooth in vec4 shadowCoord;

uniform sampler2D gSampler[5];
uniform vec4 color;

#include "../Effects/Shadows.frag.hlsl"
#include "../Light/Light.frag.hlsl"

uniform Shadows shadows;
uniform DirectionalLight sunLight;
uniform Material activeMaterial;
uniform vec3 eyePosition;
uniform bool useSpecularLight;
uniform float renderHeight;
uniform float maxTextureU;
uniform float maxTextureV;

layout(location = 0) out vec4 outputColor;

void main()
{
	vec3 normalizedNormal = normalize(normal);

	vec4 textureColor = vec4(0.0);

	float scale = worldPosition.y / renderHeight;

	const float range1 = 0.15;
	const float range2 = 0.3;
	const float range3 = 0.65;
	const float range4 = 0.85;

	if (scale >= 0 && scale <= range1)
	{
		textureColor = texture(gSampler[0], textureCoord);
	}
	else if (scale <= range2)
	{
		scale -= range1;
		scale /= (range2 - range1);

		float scale2 = scale;
		scale = 1.0 - scale;

		textureColor += texture(gSampler[0], textureCoord) * scale;
		textureColor += texture(gSampler[1], textureCoord) * scale2;
	}
	else if (scale <= range3)
	{
		textureColor = texture(gSampler[1], textureCoord);
	}
	else if (scale <= range4)
	{
		scale -= range3;
		scale /= (range4 - range3);

		float scale2 = scale;
		scale = 1.0 - scale;

		textureColor += texture(gSampler[1], textureCoord) * scale;
		textureColor += texture(gSampler[2], textureCoord) * scale2;
	}
	else
	{
		textureColor = texture(gSampler[2], textureCoord);
	}

	vec2 pathCoord = vec2(textureCoord.x / maxTextureU, textureCoord.y / maxTextureV);
	vec4 pathIntesity = texture(gSampler[4], pathCoord);
	scale = pathIntesity.x;

	vec4 pathColor = texture(gSampler[3], textureCoord);
	vec4 finalTextureColor = scale * textureColor + (1 - scale) * pathColor;

	float shadow = GetVisibility(shadows, shadowCoord);
	
	vec4 ambientLightColor = GetAmbientLightColor(sunLight);
	vec4 diffuseLightColor = GetDiffuseLightColor(worldPosition, -normalizedNormal, sunLight);

	vec4 specularLightColor;
	if (useSpecularLight)
	{
		specularLightColor = GetSpecularLightColor(worldPosition, eyePosition, -normalizedNormal, activeMaterial, sunLight);		
	}
	else
	{
		specularLightColor = vec4(0.0, 0.0, 0.0, 1.0);
	}

	outputColor = finalTextureColor * color * ((diffuseLightColor + specularLightColor) * shadow + ambientLightColor);

	// Show shadow map only
	//outputColor = vec4(shadow, shadow, shadow, 1.0);
}
