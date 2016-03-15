#version 430

smooth in vec2 textureCoord;
smooth in vec3 normal;
smooth in vec3 worldPosition;
smooth in vec4 eyeSpacePosition;
smooth in vec4 shadowCoord;

#include "Shadows.frag.hlsl"

uniform Shadows shadows;

subroutine void RenderPassType();
subroutine uniform RenderPassType RenderPass;

subroutine(RenderPassType)
void ShadeWithShadow()
{	
}

subroutine(RenderPassType)
void RecordDepth()
{
	// Do nothing, depth will be written automatically
}

void main()
{
	float shadow = GetVisibility(shadows, shadowCoord);
	// This will call either ShadeWithShadow or RecordDepth
	RenderPass();
}

