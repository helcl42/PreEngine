#version 430

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec2 inTextureCoord;
layout(location = 2) in vec3 inNormal;

smooth out vec2 textureCoord;

struct Matrices
{
	mat4 projectionMatrix;
	mat4 modelMatrix;
	mat4 viewMatrix;
	mat4 normalMatrix;
};

uniform Matrices matrices;

void main()
{
	mat4 MV = matrices.viewMatrix * matrices.modelMatrix;
	mat4 MVP = matrices.projectionMatrix * matrices.viewMatrix * matrices.modelMatrix;

	textureCoord = inTextureCoord;
	gl_Position = MVP * vec4(inPosition, 1.0);
}