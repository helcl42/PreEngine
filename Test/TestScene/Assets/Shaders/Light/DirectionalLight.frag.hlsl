#version 430

#include "LightCommon.frag.hlsl" 

vec4 GetDirectionalDiffuseLightColor(const DirectionalLight directionalLight, vec3 normal);

vec4 GetDirectionalSpecularLightColor(vec3 worldPosition, vec3 eyePosition, vec3 normal, const Material material, const DirectionalLight directionalLight);


vec4 GetDiffuseDirectionalLightColor(const DirectionalLight directionalLight, vec3 normal)
{
	vec3 n = normal;
	if (!gl_FrontFacing) n = -n;

	float diffuseIntensity = max(0.0, dot(n, -directionalLight.direction));
	float res = clamp(diffuseIntensity, 0.0, 1.0);	
	return vec4(directionalLight.color * res, 1.0);
}

vec4 GetSpecularDirectionalLightColor(vec3 worldPosition, vec3 eyePosition, vec3 normal, const Material material, const DirectionalLight directionalLight)
{
	vec4 result = vec4(0.0);
	vec3 n = normal;

	if (!gl_FrontFacing) n = -n;
	
	vec3 reflectedVector = normalize(reflect(directionalLight.direction, n));
	vec3 vertexToEyeVector = normalize(eyePosition - worldPosition);

	float specularFactor = dot(vertexToEyeVector, reflectedVector);
	if (specularFactor > 0.0)
	{
		specularFactor = pow(specularFactor, material.specularPower);
		result = vec4(directionalLight.color, 1.0) * material.specularIntensity * specularFactor;
	}

	return result;
}
