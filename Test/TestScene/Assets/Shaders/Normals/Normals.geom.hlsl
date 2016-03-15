#version 430

layout(points) in;
layout(line_strip, max_vertices = 2) out;

in vec3 normalPass[];

#include "../Common/Matrices.hlsl"

uniform Matrices matrices;

uniform float normalLength;


void main()
{
	vec3 normal = (matrices.normalMatrix * vec4(normalPass[0] * normalLength, 1.0)).xyz;
	
	vec3 position = gl_in[0].gl_Position.xyz;

	gl_Position = matrices.modelViewProjectionMatrix * vec4(position, 1.0);
	EmitVertex();

	gl_Position = matrices.modelViewProjectionMatrix * vec4(position + normal, 1.0);
	EmitVertex();

	EndPrimitive();
}