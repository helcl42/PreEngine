#version 430

#include "../Common/Random.hlsl"

vec2 poissonDisk[16] = vec2[](
	vec2(-0.94201624, -0.39906216),
	vec2(0.94558609, -0.76890725),
	vec2(-0.094184101, -0.92938870),
	vec2(0.34495938, 0.29387760),
	vec2(-0.91588581, 0.45771432),
	vec2(-0.81544232, -0.87912464),
	vec2(-0.38277543, 0.27676845),
	vec2(0.97484398, 0.75648379),
	vec2(0.44323325, -0.97511554),
	vec2(0.53742981, -0.47373420),
	vec2(-0.26496911, -0.41893023),
	vec2(0.79197514, 0.19090188),
	vec2(-0.24188840, 0.99706507),
	vec2(-0.81409955, 0.91437590),
	vec2(0.19984126, 0.78641367),
	vec2(0.14383161, -0.14100790)
	);

struct Shadows
{
	bool shadowsOn;
	bool useHardShadows;	
	//sampler2DShadow gShadowMap;
};

uniform sampler2DShadow gShadowMap;

float GetVisibility(const Shadows shadows, const vec4 shadowCoord);

float GetBias()
{
	float bias = 0.005;
	//vec3 lightPosition = normalize(vec3(Light.Position));
	//float cosTheta = clamp(dot(Normal, lightPosition), 0.0, 1.0);
	//bias *= tan(acos(cosTheta));
	return clamp(bias, 0, 0.01);
}

float GetHardShadowVisibility(const sampler2DShadow shadowMap, const vec4 biasedShadowCoord)
{
	//const float div = 1.0 / 6.0;
	//float sum = 0;
	//sum += textureProjOffset(shadowMap, shadowCoord, ivec2(-1, -1));
	//sum += textureProjOffset(shadowMap, shadowCoord, ivec2(-1, 0));
	//sum += textureProjOffset(shadowMap, shadowCoord, ivec2(-1, 1));
	//sum += textureProjOffset(shadowMap, shadowCoord, ivec2(0, 1));
	//sum += textureProjOffset(shadowMap, shadowCoord, ivec2(1, 1));
	//sum += textureProjOffset(shadowMap, shadowCoord, ivec2(1, 0));
	//sum += textureProjOffset(shadowMap, shadowCoord, ivec2(1, -1));
	//return sum * div;

	return textureProj(shadowMap, biasedShadowCoord);
}

float GetSoftShadowVisibility(const sampler2DShadow shadowMap, const vec4 biasedShadowCoord)
{
	const float poissonCorrector = 700.0;
	const int count = 4;
	float visibility = 1.0;
	for (int index = 0; index < count; index++)
	{
		int randomIndex = RandomIntFromTo(biasedShadowCoord, 0, count);
		vec4 shadowCoordSmooth = vec4(biasedShadowCoord.x + poissonDisk[randomIndex].x / poissonCorrector, biasedShadowCoord.y + poissonDisk[randomIndex].y / poissonCorrector, biasedShadowCoord.z, biasedShadowCoord.w);
		float sub = textureProj(shadowMap, shadowCoordSmooth.xyzw);
		visibility -= (1.0 / (count * 1.5)) * (1.0 - sub);
	}
	return visibility;
}

float GetVisibility(const Shadows shadows, const vec4 shadowCoord)
{
	float visibility = 1.0;

	if (shadows.shadowsOn)
	{
		float bias = GetBias();
		vec4 biasedShadowCoord = vec4(shadowCoord.xy, shadowCoord.z - bias, shadowCoord.w);
		if (shadows.useHardShadows)
		{
			visibility = GetHardShadowVisibility(gShadowMap, biasedShadowCoord);
		}
		else
		{
			visibility = GetSoftShadowVisibility(gShadowMap, biasedShadowCoord);
		}
	}

	return visibility;
}
