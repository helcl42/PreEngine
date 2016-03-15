#version 430

#include "LightCommon.frag.hlsl" 

vec4 GetDiffuseLightColor(vec3 worldPosition, vec3 eyePosition, vec3 normal, const DirectionalLight directionalLight);

vec4 GetSpecularLightColor(vec3 worldPosition, vec3 eyePosition, vec3 normal, const Material material, const DirectionalLight directionalLight);


vec4 GetDiffuseLightColor(vec3 worldPosition, vec3 normal, const DirectionalLight directionalLight)
{
	vec3 n = normal;
	if (!gl_FrontFacing) n = -n;

	vec3 lightDirection = normalize(directionalLight.direction - worldPosition);
	float sDotN = clamp(max(dot(lightDirection, n), 0.0), 0.0, 1.0);

	return directionalLight.color * sDotN;
}

vec4 GetSpecularLightColor(vec3 worldPosition, vec3 eyePosition, vec3 normal, const Material material, const DirectionalLight directionalLight)
{
	vec3 n = normal;
	if (!gl_FrontFacing) n = -n;

	vec3 lightDirection = normalize(directionalLight.direction - worldPosition);
	vec3 viewDirection = normalize(eyePosition - worldPosition);

	float specularFactor = 0.0;
	float energyConservation = 1.0;
	if (useBlinnPhongLightModel)
	{
		if (applyEnergyConservation) energyConservation = (8.0 + material.specularPower) / (8.0 * PI);

		vec3 halfWayDirection = normalize(lightDirection + viewDirection);
		specularFactor = pow(max(dot(normal, halfWayDirection), 0.0), material.specularPower);
	}
	else
	{
		if (applyEnergyConservation) energyConservation = (2.0 + material.specularPower) / (2.0 * PI);

		vec3 reflectedDirection = reflect(-lightDirection, n);
		float sDotN = clamp(max(dot(lightDirection, n), 0.0), 0.0, 1.0);
		if (sDotN > 0.0)
		{
			specularFactor = pow(max(dot(reflectedDirection, viewDirection), 0.0), material.specularPower);
		}
		else
		{
			specularFactor = 0.0;
		}
	}
	return vec4(directionalLight.color, 1.0) * material.specularIntensity * specularFactor * energyConservation;
}

