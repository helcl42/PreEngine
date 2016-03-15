#version 430

struct DirectionalLight
{
	vec3 color;
	vec3 direction;
	float ambientIntensity;
	bool useAmbientOnly;
};

struct Material
{
	float specularIntensity;
	float specularPower;
};

const float PI = 3.14159265;
uniform bool useBlinnPhongLightModel = true;
uniform bool applyEnergyConservation = false;

vec4 GetAmbientLightColor(const DirectionalLight directionalLight);


vec4 GetAmbientLightColor(const DirectionalLight directionalLight)
{
	float res = clamp(directionalLight.ambientIntensity, 0.0, 1.0);
	return vec4(directionalLight.color * res, 1.0);
}
