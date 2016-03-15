#version 430

#include "../Common/Matrices.hlsl"

uniform Matrices matrices;
uniform mat4 heightMapScaleMatrix;

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec2 inTextureCoord;
layout(location = 2) in vec3 inNormal;

smooth out vec3 eyeSpacePosition;
smooth out vec3 normal;
smooth out vec3 worldPosition;
smooth out vec2 textureCoord;
smooth out vec4 shadowCoord;

void main()
{
	vec4 inPositionScaled = heightMapScaleMatrix * vec4(inPosition, 1.0);

	gl_Position = matrices.modelViewProjectionMatrix * inPositionScaled;
	eyeSpacePosition = (matrices.modelViewMatrix * vec4(inPosition, 1.0)).xyz;

	textureCoord = inTextureCoord;
	normal = inNormal;

	worldPosition = (matrices.modelMatrix * inPositionScaled).xyz;

	shadowCoord = matrices.shadowMatrix * inPositionScaled;
}