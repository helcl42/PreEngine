#version 430

smooth in vec2 textureCoord;
smooth in vec3 normal;
smooth in vec3 worldPosition;
smooth in vec4 eyeSpacePosition;

layout(location = 0) out vec4 outputColor;

#define MAX_BLUR_RADIUS 4096

uniform sampler2D gSampler;
uniform int blurRadius = 16;
uniform vec2 blurDirection = vec2(1.0, 0.0); // (1,0)/(0,1) for x/y pass

vec4 GaussianBlur1D(
	in sampler2D srcTex,
	in vec2 srcTexelSize,
	in vec2 origin,
	in int radius,
	in vec2 direction
	) 
{
	int nSamples = clamp(radius, 1, int(MAX_BLUR_RADIUS)) / 2;

	if (nSamples == 0)
		return texture(srcTex, origin);

	const float SIGMA = float(blurRadius) / 8.0;
	float sig2 = SIGMA * SIGMA;
	const float TWO_PI = 6.2831853071795;
	const float E = 2.7182818284590;

	//	set up incremental counter:
	vec3 gaussInc;
	gaussInc.x = 1.0 / (sqrt(TWO_PI) * SIGMA);
	gaussInc.y = exp(-0.5 / sig2);
	gaussInc.z = gaussInc.y * gaussInc.y;

	//	accumulate results:
	vec4 result = texture(srcTex, origin) * gaussInc.x;
	for (int i = 1; i < nSamples; ++i) 
	{
		gaussInc.xy *= gaussInc.yz;

		vec2 offset = float(i) * direction * srcTexelSize;
		result += texture(srcTex, origin - offset) * gaussInc.x;
		result += texture(srcTex, origin + offset) * gaussInc.x;
	}

	return result;
}


void main()
{	
	vec2 texelSize = 1.0 / vec2(textureSize(gSampler, 0));

	vec4 result = GaussianBlur1D(gSampler, texelSize, textureCoord, blurRadius, blurDirection);
	outputColor = result;
}

