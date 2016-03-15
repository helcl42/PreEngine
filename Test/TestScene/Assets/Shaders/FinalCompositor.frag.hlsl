#version 430

smooth in vec2 textureCoord;
smooth in vec3 normal;
smooth in vec3 worldPosition;
smooth in vec4 eyeSpacePosition;

layout(location = 0) out vec4 outputColor;

#include "Effects/MotionBlur2.hlsl"

uniform sampler2D sourceSampler;
uniform sampler2D nonSunSourceSampler;
uniform sampler2D lensSampler;
uniform sampler2D lensDirtSampler;
uniform sampler2D depthSampler;

uniform int mode;
uniform bool showLensSource;

uniform sampler2D lensStarSampler;
uniform mat4 lensStarMatrix;
uniform float gamma = 2.2;

void main()
{
	vec4 lensMod = texture(lensDirtSampler, textureCoord);
	vec4 lensSourceColor = texture(sourceSampler, textureCoord);

	vec4 nonLensSourceColor;
	vec4 tempColor = texture(nonSunSourceSampler, textureCoord);
	if (motionBlurEnabled)
	{
		nonLensSourceColor = MotionBlur(nonSunSourceSampler, depthSampler);
	}
	else
	{
		nonLensSourceColor = tempColor;
	}

	vec4 lensResultColor = vec4(0.0);
	if (mode == 2)
	{
		vec2 lensStarTextureCoord = (lensStarMatrix * vec4(textureCoord, 0.0, 1.0)).xy;
		lensMod += texture(lensStarSampler, lensStarTextureCoord);
		lensResultColor = Hejl(texture(lensSampler, textureCoord) * lensMod);		
	}
	else if (mode == 1)
	{
		lensResultColor = Hejl(texture(lensSampler, textureCoord) * lensMod);
	}
	else
	{
		lensResultColor = texture(lensSampler, textureCoord);		
	}		

	vec4 resultColor;
	if (showLensSource)
	{
		resultColor = lensResultColor + nonLensSourceColor + lensSourceColor;
	}
	else
	{
		resultColor = lensResultColor + nonLensSourceColor;
	}

	//outputColor = GetGammaCorrectedColor(resultColor, gamma);
	outputColor = resultColor;
}

