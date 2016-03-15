#version 430

#include "../Common/Utils.hlsl"

const int MAX_MOTION_SAMPLES = 64;

uniform mat4 inverseViewProjectionMatrix;
uniform mat4 previousViewProjectionMatrix;

uniform float motionScale = 1.0; // current fps / target fps
uniform int maxMotionBlurSamples = MAX_MOTION_SAMPLES;
uniform bool motionBlurEnabled = true;

vec4 MotionBlur(const in sampler2D inputTex, const in sampler2D depthTex)
{
	float depth = texture(depthTex, textureCoord).r;
	vec4 currentPosition = vec4(textureCoord * 2.0 - 1.0, depth, 1.0);
	currentPosition = inverseViewProjectionMatrix * currentPosition;
	vec4 previousPosition = previousViewProjectionMatrix * currentPosition;
	previousPosition.xyz /= previousPosition.w;
	previousPosition.xy = previousPosition.xy * 0.5 + 0.5;

	vec2 velocity = (previousPosition.xy - textureCoord) * motionScale;

	vec2 texelSize = 1.0 / vec2(textureSize(inputTex, 0));

	float tspeed = length(velocity / texelSize); // speed in pixels/second
	int countOfSamples = clamp(int(tspeed), 1, MAX_MOTION_SAMPLES);

	vec4 result = texture(inputTex, textureCoord);
	for (int i = 1; i < countOfSamples; ++i)
	{
		vec2 offset = textureCoord + velocity * (float(i) / float(countOfSamples - 1) - 0.5);
		result += texture(inputTex, offset);
	}
	return result / float(countOfSamples);
}