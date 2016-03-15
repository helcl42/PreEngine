#version 430

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec2 inTextureCoord;
layout(location = 2) in vec3 inNormal;
layout(location = 3) in vec3 inNextPosition;
layout(location = 4) in vec3 inNextNormal;

smooth out vec3 normal;
smooth out vec2 textureCoord;
smooth out vec3 worldPosition;
smooth out vec4 eyeSpacePosition;
smooth out vec4 shadowCoord;

#include "../Common/Matrices.hlsl"

uniform Matrices matrices;

uniform float interpolation;

void main() 
{
	textureCoord = inTextureCoord;

	vec3 interpolatedPosition = inPosition;
	if (interpolation >= 0.0) interpolatedPosition += (inNextPosition - inPosition) * interpolation;

	eyeSpacePosition = matrices.modelViewMatrix * vec4(interpolatedPosition, 1.0);
	gl_Position = matrices.modelViewProjectionMatrix * vec4(interpolatedPosition, 1.0);

	vec3 interpolatedNormal = inNormal;
	if (interpolation >= 0.0) interpolatedNormal += (inNextNormal - inNormal) * interpolation;

	normal = (matrices.normalMatrix * vec4(interpolatedNormal, 1.0)).xyz;
	worldPosition = (matrices.modelMatrix * vec4(interpolatedPosition, 1.0)).xyz;

	shadowCoord = matrices.shadowMatrix * vec4(inPosition, 1.0);
}