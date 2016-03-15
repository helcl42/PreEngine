#version 430

smooth in vec2 textureCoord;
smooth in vec3 normal;
smooth in vec3 worldPosition;
smooth in vec4 eyeSpacePosition;

layout(location = 0) out vec4 outputColor;

uniform sampler2D gSampler;
uniform sampler2D gLensColorSampler;
uniform int ghosts;
uniform float ghostDispersal;
uniform float haloWidth;
uniform float distortionCoef;

vec3 GetTextureDistortedColor(
	in sampler2D tex,
	in vec2 texcoord,
	in vec2 direction, // direction of distortion
	in vec3 distortion // per-channel distortion factor
	) 
{
	return vec3(
		texture(tex, texcoord + direction * distortion.r).r,
		texture(tex, texcoord + direction * distortion.g).g,
		texture(tex, texcoord + direction * distortion.b).b
		);
}

void main()
{
	vec2 texcoord = -textureCoord + vec2(1.0);
	vec2 texelSize = 1.0 / vec2(textureSize(gSampler, 0));

	// ghost vector to image centre:
	vec2 ghostVec = (vec2(0.5) - texcoord) * ghostDispersal;
	vec2 ghostVecNormalized = normalize(ghostVec);
	vec2 haloVec = ghostVecNormalized * haloWidth;
	vec3 distortion = vec3(-texelSize.x * distortionCoef, 0.0, texelSize.x * distortionCoef);

	// sample ghosts:  
	vec4 result = vec4(0.0);
	for (int i = 0; i < ghosts; ++i)
	{
		vec2 offset = fract(texcoord + ghostVec * float(i));
		
		float weight = length(vec2(0.5) - fract(texcoord + haloVec)) / length(vec2(0.5));
		weight = pow(1.0 - weight, 5.0);

		result += GetTextureDistortedColor(gSampler, offset, ghostVecNormalized, distortion) * weight;
	}

	// coloring
	result *= texture(gLensColorSampler, vec2(length(vec2(0.5) - texcoord) / length(vec2(0.5)), 0.0));

	// sample halo:
	float weight = length(vec2(0.5) - fract(texcoord + haloVec)) / length(vec2(0.5));
	weight = pow(1.0 - weight, 10.0);

	result += GetTextureDistortedColor(gSampler, fract(texcoord + haloVec), ghostVecNormalized, distortion) * weight;

	outputColor = result;
}

