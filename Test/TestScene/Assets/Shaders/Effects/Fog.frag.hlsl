#version 430

struct FogParameters
{
	vec4 color;
	float start;
	float end;
	float density;
	int type; // 0 = linear, 1 = exp, 2 = exp2
};

float GetFogFactor(const FogParameters params, float fogCoord);

float GetFogFactor(const FogParameters params, float fogCoord)
{
	float result = 0.0;
	if (params.type == 0)
	{
		result = (params.end - fogCoord) / (params.end - params.start);
	}
	else if (params.type == 1)
	{
		result = exp(-params.density * fogCoord);
	}
	else if (params.type == 2)
	{
		result = exp(-pow(params.density * fogCoord, 2.0));
	}
	return 1.0 - clamp(result, 0.0, 1.0);
}