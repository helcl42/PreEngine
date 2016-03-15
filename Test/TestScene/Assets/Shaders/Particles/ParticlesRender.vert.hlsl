#version 430

layout(location = 0) in vec3 position;
layout(location = 2) in vec3 color;
layout(location = 3) in float lifeTime;
layout(location = 4) in float size;
layout(location = 5) in int type;

out vec3 colorPass;
out float lifeTimePass;
out float sizePass;
out int typePass;


void main()
{
	gl_Position = vec4(position, 1.0);
	colorPass = color;
	lifeTimePass = lifeTime;
	sizePass = size;
	typePass = type;
}