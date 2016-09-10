#version 430

const float PI = 3.1415927;

float Log10(in float x) 
{
	return log2(x) / log2(10);
}

vec2 PowV2(in vec2 b, in float e) 
{
	return vec2(pow(b.x, e), pow(b.y, e));
}

vec3 PowV3(in vec3 b, in float e) 
{
	return vec3(pow(b.x, e), pow(b.y, e), pow(b.z, e));
}

vec4 PowV4(in vec4 b, in float e) 
{
	return vec4(pow(b.x, e), pow(b.y, e), pow(b.z, e), pow(b.w, e));
}

float SquareLength(in vec2 v) 
{
	return v.x * v.x + v.y * v.y;
}

float SquareLength(in vec3 v)
{
	return v.x * v.x + v.y * v.y + v.z * v.z;
}

float SquareLength(in vec4 v)
{
	return v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w;
}

vec2 VecMax(in vec2 a, in vec2 b) 
{
	return SquareLength(a) > SquareLength(b) ? a : b;
}

vec3 VecMax(in vec3 a, in vec3 b) 
{
	return SquareLength(a) > SquareLength(b) ? a : b;
}

vec4 VecMax(in vec4 a, in vec4 b) 
{
	return SquareLength(a) > SquareLength(b) ? a : b;
}

float Luminance(in vec3 rgb) 
{
	const vec3 kLum = vec3(0.2126, 0.7152, 0.0722);
	return max(dot(rgb, kLum), 0.0001); // prevent zero result
}

float LinearizeDepth(in float depth, in float znear, in float zfar) 
{
	float zn = depth * 2.0 - 1.0; // convert back to ndc
	return 2.0 * znear * zfar / (zfar + znear - (zfar - znear) * zn);
}

vec4 Hejl(in vec4 color)
{
	vec4 x = max(vec4(0.0), color - vec4(0.004));
	return (x * (6.2 * x + 0.5)) / (x * (6.2 * x + 1.7) + 0.06);
}

vec4 GetGammaCorrectedColor(const in vec4 color, float gamma)
{
	return vec4(PowV3(color.rgb, 1.0 / gamma), 1.0);
}

vec3 seed;

float randZeroOne()
{
	uint n = floatBitsToUint(seed.y * 214013.0 + seed.x * 2531011.0 + seed.z * 141251.0);
	n = n * (n * n * 15731u + 789221u);
	n = (n >> 9u) | 0x3F800000u;

	float res = 2.0 - uintBitsToFloat(n);
	seed = vec3(seed.x + 147158.0 * res, seed.y * res + 415161.0 * res, seed.z + 324154.0 * res);
	return res;
}

int randomInt(int min, int max)
{
	float randomFloat = randZeroOne();
	return int(float(min) + randomFloat * float(max - min));
}

float toRadians(float degrees)
{
	return (PI / 180.0) * degrees;
}

float toDegrees(float rads)
{
	return (180.0 / PI) * rads;
}