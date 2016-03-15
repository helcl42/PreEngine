#version 430

smooth in vec2 textureCoord;
smooth in vec3 normal;
smooth in vec3 worldPosition;
smooth in vec4 eyeSpacePosition;

layout(location = 0) out vec4 outputColor;

uniform bool hdrEnabled = true;
uniform sampler2D inputTex;

vec4 GetFragmentLuminance(const in sampler2D inputTex, const in vec2 textureCoord)
{
	const float delta = 1e-6;
	vec3 color = texture(inputTex, textureCoord).xyz;
	float luminance = dot(color, vec3(0.2125, 0.7154, 0.0721));
	float logLuminance = log(delta + luminance);
	return vec4(logLuminance, logLuminance, 0.0, 0.0);
}

void main()
{
	if (hdrEnabled)
		outputColor = GetFragmentLuminance(inputTex, textureCoord);
	else
		outputColor = texture(inputTex, textureCoord);
}