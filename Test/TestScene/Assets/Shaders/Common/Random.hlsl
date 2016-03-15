#version 430

float RandomZeroOne(const vec4 seedInput);

int RandomIntFromTo(const vec4 seedInput, int from, int to);


float RandomZeroOne(const vec4 seedInput)
{
	vec3 seed = vec3(seedInput.xyz);
	uint n = floatBitsToUint(seed.y * 214013.0 + seed.x * 2531011.0 + seed.z * 141251.0);
	n = n * (n * n * 15731u + 789221u);
	n = (n >> 9u) | 0x3F800000u;

	float res = 2.0 - uintBitsToFloat(n);
	seed = vec3(seed.x + 147158.0 * res, seed.y * res + 415161.0 * res, seed.z + 324154.0 * res);
	return res;
}

int RandomIntFromTo(const vec4 seedInput, int from, int to)
{
	vec3 seed = vec3(seedInput.xyz);
	uint n = floatBitsToUint(seed.y * 214013.0 + seed.x * 2531011.0 + seed.z * 141251.0);
	n = n * (n * n * 15731u + 789221u);
	n = (n >> 9u) | 0x3F800000u;

	float res = 2.0 - uintBitsToFloat(n);
	seed = vec3(seed.x + 147158.0 * res, seed.y * res + 415161.0 * res, seed.z + 324154.0 * res);

	return (int(to * res) % to) + from;
}