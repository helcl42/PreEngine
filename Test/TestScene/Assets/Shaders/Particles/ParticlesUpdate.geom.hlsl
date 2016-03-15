#version 430

layout(points) in;
layout(points, max_vertices = 40) out;

in vec3 positionPass[];
in vec3 velocityPass[];
in vec3 colorPass[];
in float lifeTimePass[];
in float sizePass[];
in int typePass[];

out vec3 positionOut;
out vec3 velocityOut;
out vec3 colorOut;
out float lifeTimeOut;
out float sizeOut;
out int typeOut;

uniform vec3 genPosition;
uniform vec3 genGravity;
uniform vec3 genVelocityMin;
uniform vec3 genVelocityRange;
uniform vec3 genColor;
uniform float genSize;
uniform float genLifeTimeMin;
uniform float genLifeTimeRange;
uniform float deltaTime;
uniform int numberToGenerate;
uniform vec3 randomSeed;
vec3 seed;


float randZeroOne()
{
	uint n = floatBitsToUint(seed.y * 214013.0 + seed.x * 2531011.0 + seed.z * 141251.0);
	n = n * (n * n * 15731u + 789221u);
	n = (n >> 9u) | 0x3F800000u;

	float res = 2.0 - uintBitsToFloat(n);
	seed = vec3(seed.x + 147158.0 * res, seed.y * res + 415161.0 * res, seed.z + 324154.0 * res);
	return res;
}

void main()
{
	seed = randomSeed;

	positionOut = positionPass[0];
	velocityOut = velocityPass[0];
	if (typePass[0] != 0) // if it is not GENERATOR
	{
		positionOut += velocityOut * deltaTime;
		velocityOut += genGravity * deltaTime;
	}

	colorOut = colorPass[0];
	lifeTimeOut = lifeTimePass[0] - deltaTime;
	sizeOut = sizePass[0];
	typeOut = typePass[0];

	if (typeOut == 0)
	{
		EmitVertex(); 
		EndPrimitive();

		for (int i = 0; i < numberToGenerate; i++)
		{
			positionOut = genPosition;
			velocityOut = genVelocityMin + vec3(genVelocityRange.x * randZeroOne(), genVelocityRange.y * randZeroOne(), genVelocityRange.z * randZeroOne());
			colorOut = genColor;
			lifeTimeOut = genLifeTimeMin + genLifeTimeRange * randZeroOne();
			sizeOut = genSize;
			typeOut = 1;

			EmitVertex();
			EndPrimitive();
		}
	}
	else if (lifeTimeOut > 0.0)
	{
		EmitVertex();
		EndPrimitive();
	}
}