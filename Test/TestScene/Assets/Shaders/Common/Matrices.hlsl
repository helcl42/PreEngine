#version 430

struct Matrices
{
	mat4 projectionMatrix;
	mat4 modelMatrix;
	mat4 viewMatrix;
	mat4 normalMatrix;
	mat4 shadowMatrix;

	mat4 modelViewMatrix;
	mat4 modelViewProjectionMatrix;
	mat4 previousModelViewProjectionMatrix;
};