#version 430

smooth in vec2 textureCoord;
smooth in vec3 normal;
smooth in vec3 worldPosition;
smooth in vec4 eyeSpacePosition;
smooth in vec4 shadowCoord;
in vec3 lightDirectionTangentSpace;

layout(location = 0) out vec4 outputColor;

uniform vec3 eyePosition;

uniform sampler2D gSampler;
uniform vec4 color;

subroutine void RenderPassType();
subroutine uniform RenderPassType RenderPass;


subroutine(RenderPassType)
void ShadeWithShadow()
{
	vec4 textureColor = texture(gSampler, textureCoord);
	outputColor = textureColor * color;
}

subroutine(RenderPassType)
void RecordDepth()
{
	// Do nothing, depth will be written automatically
}

void main() 
{
	// This will call either ShadeWithShadow or RecordDepth
	RenderPass();
}

