#version 430

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec2 inTextureCoord;
layout(location = 2) in vec3 inNormal;

#include "../Common/Matrices.hlsl"

uniform Matrices matrices;

smooth out vec2 textureCoord;
smooth out vec3 normal;
smooth out vec3 worldPosition;
smooth out vec4 eyeSpacePosition;

void main()
{
	textureCoord = inTextureCoord;
	normal = normalize(mat3(matrices.normalMatrix) * inNormal);
	worldPosition = (matrices.modelMatrix * vec4(inPosition, 1.0)).xyz;
	eyeSpacePosition = matrices.modelViewMatrix * vec4(inPosition, 1.0);
	gl_Position = matrices.modelViewProjectionMatrix * vec4(inPosition, 1.0);
}