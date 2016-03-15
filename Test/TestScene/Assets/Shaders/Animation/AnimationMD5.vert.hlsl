#version 430

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec2 inTextureCoord;
layout(location = 2) in vec3 inNormal;
layout(location = 3) in ivec4 BoneIDs;
layout(location = 4) in vec4 Weights;

#include "../Light/LightCommon.frag.hlsl"
#include "../Common/Matrices.hlsl"

const int MAX_BONES = 100;

uniform Matrices matrices;
uniform DirectionalLight sunLight;
uniform mat4 gBones[MAX_BONES];

smooth out vec2 textureCoord;
smooth out vec3 normal;
smooth out vec3 worldPosition;
smooth out vec4 eyeSpacePosition;
smooth out vec4 shadowCoord;

void main()
{
	mat4 BoneTransform = gBones[BoneIDs[0]] * Weights[0];
	BoneTransform += gBones[BoneIDs[1]] * Weights[1];
	BoneTransform += gBones[BoneIDs[2]] * Weights[2];
	BoneTransform += gBones[BoneIDs[3]] * Weights[3];

	vec4 positionL = BoneTransform * vec4(inPosition, 1.0);
	vec4 normalL = BoneTransform * vec4(inNormal, 0.0);

	textureCoord = inTextureCoord;
	eyeSpacePosition = matrices.modelViewMatrix * positionL;
	gl_Position = matrices.modelViewProjectionMatrix * positionL;
	shadowCoord = matrices.shadowMatrix * positionL;
	normal = normalize(mat3(matrices.normalMatrix) * normalL.xyz);
	worldPosition = (matrices.modelMatrix * positionL).xyz;
	shadowCoord = matrices.shadowMatrix * positionL;
}
