#version 430

layout(points) in;
layout(triangle_strip, max_vertices = 4) out;

in vec3 colorPass[];
in float lifeTimePass[];
in float sizePass[];
in int typePass[];

smooth out vec2 textureCoord;
flat out vec4 colorPart;

struct Matrices
{
	mat4 projectionMatrix;
	mat4 viewMatrix;
};

uniform Matrices matrices;
uniform vec3 quad1;
uniform vec3 quad2;

void main()
{
	if (typePass[0] != 0) // if not GENERATOR
	{
		vec3 oldPosition = gl_in[0].gl_Position.xyz;
		float size = sizePass[0];
		mat4 VP = matrices.projectionMatrix * matrices.viewMatrix;

		colorPart = vec4(colorPass[0], lifeTimePass[0]);

		vec3 posLeftBottom = oldPosition + (-quad1 - quad2) * size;
		gl_Position = VP * vec4(posLeftBottom, 1.0);
		textureCoord = vec2(0.0, 0.0);
		EmitVertex();

		vec3 posLeftTop = oldPosition + (-quad1 + quad2) * size;
		gl_Position = VP * vec4(posLeftTop, 1.0);
		textureCoord = vec2(0.0, 1.0);
		EmitVertex();

		vec3 posRightBottom = oldPosition + (quad1 - quad2) * size;
		gl_Position = VP * vec4(posRightBottom, 1.0);
		textureCoord = vec2(1.0, 0.0);
		EmitVertex();

		vec3 posRightTop = oldPosition + (quad1 + quad2) * size;
		gl_Position = VP * vec4(posRightTop, 1.0);
		textureCoord = vec2(1.0, 1.0);
		EmitVertex();

		EndPrimitive();
	}
}