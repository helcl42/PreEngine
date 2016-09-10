#version 430

layout(points) in;
layout(triangle_strip) out;
layout(max_vertices = 12) out;

#include "../Common/Matrices.hlsl"
#include "../Common/Utils.hlsl"

smooth out vec2 texCoord;
smooth out vec3 worldPosition;
smooth out vec4 eyeSpacePosition;

uniform Matrices matrices;
uniform float timeElapsed;
uniform float grassPatchSize = 5.0;
uniform float windStrength = 4.0;
uniform vec3 windDirection = vec3(1.0, 0.0, 1.0);

mat4 rotationMatrix(vec3 axis, float angle)
{
	axis = normalize(axis);
	float s = sin(angle);
	float c = cos(angle);
	float oc = 1.0 - c;

	return mat4(
		oc * axis.x * axis.x + c, oc * axis.x * axis.y - axis.z * s, oc * axis.z * axis.x + axis.y * s, 0.0,
		oc * axis.x * axis.y + axis.z * s, oc * axis.y * axis.y + c, oc * axis.y * axis.z - axis.x * s, 0.0,
		oc * axis.z * axis.x - axis.y * s, oc * axis.y * axis.z + axis.x * s, oc * axis.z * axis.z + c, 0.0,
		0.0, 0.0, 0.0, 1.0
	);
}

void main()
{
	vec3 grassFieldPosition = gl_in[0].gl_Position.xyz;

	vec3 baseDirections[3];
	baseDirections[0] = vec3(1.0, 0.0, 0.0);
	baseDirections[1] = vec3(cos(toRadians(45.0)), 0.0, sin(toRadians(45.0)));
	baseDirections[2] = vec3(cos(toRadians(-45.0)), 0.0, sin(toRadians(-45.0)));

	for (int i = 0; i < 3; i++)
	{
		vec3 baseDirectionRotated = (rotationMatrix(vec3(0, 1, 0), sin(timeElapsed * 0.7) * 0.1) * vec4(baseDirections[i], 1.0)).xyz;

		seed = grassFieldPosition * float(i);

		int grassPatchIndex = randomInt( 0, 3);
		float grassPatchHeight = 3.5 + randZeroOne() * 2.0;
		float TCStartX = float(grassPatchIndex) * 0.25;
		float TCEndX = TCStartX + 0.25;

		float windPower = 0.5 + sin(grassFieldPosition.x / 30 + grassFieldPosition.z / 30 + timeElapsed * (1.2 + windStrength / 20.0));
		if (windPower < 0.0) windPower = windPower * 0.2;
		else windPower = windPower * 0.3;
		windPower *= windStrength;

		// Grass patch top left vertex
		vec3 topLeftVertex = grassFieldPosition - baseDirectionRotated * grassPatchSize * 0.5 + windDirection * windPower;
		topLeftVertex.y += grassPatchHeight;
		gl_Position = matrices.modelViewProjectionMatrix * vec4(topLeftVertex, 1.0);
		texCoord = vec2(TCStartX, 1.0);
		worldPosition = topLeftVertex;
		eyeSpacePosition = matrices.modelViewMatrix * vec4(topLeftVertex, 1.0);
		EmitVertex();

		// Grass patch bottom left vertex
		vec3 bottomLeftVertex = grassFieldPosition - baseDirections[i] * grassPatchSize * 0.5;
		gl_Position = matrices.modelViewProjectionMatrix * vec4(bottomLeftVertex, 1.0);
		texCoord = vec2(TCStartX, 0.0);
		worldPosition = bottomLeftVertex;
		eyeSpacePosition = matrices.modelViewMatrix * vec4(bottomLeftVertex, 1.0);
		EmitVertex();

		// Grass patch top right vertex
		vec3 topRightVertex = grassFieldPosition + baseDirectionRotated * grassPatchSize * 0.5 + windDirection * windPower;
		topRightVertex.y += grassPatchHeight;
		gl_Position = matrices.modelViewProjectionMatrix * vec4(topRightVertex, 1.0);
		texCoord = vec2(TCEndX, 1.0);
		worldPosition = topRightVertex;
		eyeSpacePosition = matrices.modelViewMatrix * vec4(topRightVertex, 1.0);
		EmitVertex();
	
		// Grass patch bottom right vertex
		vec3 bottomRightVertex = grassFieldPosition + baseDirections[i] * grassPatchSize * 0.5;
		gl_Position = matrices.modelViewProjectionMatrix * vec4(bottomRightVertex, 1.0);
		texCoord = vec2(TCEndX, 0.0);
		worldPosition = bottomRightVertex;
		eyeSpacePosition = matrices.modelViewMatrix * vec4(bottomRightVertex, 1.0);
		EmitVertex();

		EndPrimitive();
	}
}