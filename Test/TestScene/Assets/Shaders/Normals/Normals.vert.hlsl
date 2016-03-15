#version 430

layout(location = 0) in vec3 inPosition;
layout(location = 2) in vec3 inNormal;

out vec3 normalPass;

void main()
{
	gl_Position = vec4(inPosition, 1.0);
	normalPass = inNormal;
}