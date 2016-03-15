#version 430

#include "../Common/Utils.hlsl"

const float VELOCITY_POWER= 3.0;
const int MAX_MOTION_SAMPLES = 64;

uniform sampler2D motionVelocitySampler;

uniform float motionScale = 1.0; // current fps / target fps
uniform int maxMotionBlurSamples = MAX_MOTION_SAMPLES;
uniform bool motionBlurEnabled = false;
uniform bool useFixedSampling = true;

vec2 EncodeVelocity(in vec2 velocity);

vec2 DecodeVelocity(in vec2 velocity);

vec4 MotionBlur(const in sampler2D inputTex);


vec4 MotionBlur(const in sampler2D inputTex)
{
	vec2 velocity = DecodeVelocity(texture(motionVelocitySampler, textureCoord).rg);
	velocity *= motionScale;

	//	compute number of blur samples to take:
	vec2 texelSize = 1.0 / vec2(textureSize(inputTex, 0));
	float speed = length(velocity / texelSize);
	int nSamples = clamp(int(speed), 1, maxMotionBlurSamples);
	vec4 result = vec4(0.0);

	if (useFixedSampling)
	{
		/*	This approach samples at 1-texel intervals along the velocity direction.
		This limits the maximum achievable blur to maxMotionBlurSamples, which
		under-blurs when speed > maxMotionBlurSamples. */
		velocity = normalize(velocity) * texelSize;
		float hlim = float(-nSamples) * 0.5 + 0.5;
		for (int i = 0; i < nSamples; ++i)
		{
			vec2 offset = velocity * (hlim + float(i));
			result += texture(inputTex, textureCoord + offset);
		}
	}
	else
	{
		/*	This approach samples at even intervals along the velocity direction. This
		ensures the proper amount of blur, but causes a degredation in blur
		quality (banding aretfacts) when when speed > maxMotionBlurSamples. */
		result = texture(inputTex, textureCoord);
		for (int i = 1; i < nSamples; ++i)
		{
			vec2 offset = velocity * (float(i) / float(nSamples - 1) - 0.5);
			result += texture(inputTex, textureCoord + offset);
		}
	}

	result /= float(nSamples);

	return result;
}

vec2 EncodeVelocity(in vec2 velocity)
{
	//vec2 result = pow(abs(velocity), 1 / 3.0) * sign(velocity) * 0.5 + 0.5;
	vec2 result = velocity * 0.5 + 0.5;
	result = PowV2(result, VELOCITY_POWER);
	return result;
}

vec2 DecodeVelocity(in vec2 velocity)
{
	vec2 result = PowV2(velocity, 1.0 / VELOCITY_POWER);
	result = result * 2.0 - 1.0;
	return result;
}