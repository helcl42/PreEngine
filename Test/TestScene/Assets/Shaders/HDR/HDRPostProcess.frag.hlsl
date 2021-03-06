#version 430

smooth in vec2 textureCoord;
smooth in vec3 normal;
smooth in vec3 worldPosition;
smooth in vec4 eyeSpacePosition;

layout(location = 0) out vec4 outputColor;

// XYZ/RGB conversion matrices from:
// http://www.brucelindbloom.com/index.html?Eqn_RGB_XYZ_Matrix.html

uniform mat3 rgb2xyz = mat3(
	0.4124564, 0.2126729, 0.0193339,
	0.3575761, 0.7151522, 0.1191920,
	0.1804375, 0.0721750, 0.9503041);

uniform mat3 xyz2rgb = mat3(
	3.2404542, -0.9692660, 0.0556434,
	-1.5371385, 1.8760108, -0.2040259,
	-0.4985314, 0.0415560, 1.0572252);

uniform float exposure = 0.805;
uniform float white = 0.928;
uniform float averageLuminance = 1.0;
uniform bool hdrEnabled = true;
uniform sampler2D inputTex;

vec4 GetHighDefinitionRangeColor(const in sampler2D inputTex, const in vec2 textureCoord)
{
	// Retrieve high-res color from texture
	vec4 color = texture(inputTex, textureCoord);

	// Convert to XYZ
	vec3 xyzCol = rgb2xyz * vec3(color);

	// Convert to xyY
	float xyzSum = xyzCol.x + xyzCol.y + xyzCol.z;
	vec3 xyYCol = vec3(xyzCol.x / xyzSum, xyzCol.y / xyzSum, xyzCol.y);

	// Apply the tone mapping operation to the luminance (xyYCol.z or xyzCol.y)
	float L = (exposure * xyYCol.z) / averageLuminance;
	L = (L * (1 + L / (white * white))) / (1 + L);

	// Using the new luminance, convert back to XYZ
	xyzCol.x = (L * xyYCol.x) / (xyYCol.y);
	xyzCol.y = L;
	xyzCol.z = (L * (1 - xyYCol.x - xyYCol.y)) / xyYCol.y;

	return vec4(xyz2rgb * xyzCol, 1.0);
}

void main()
{
	if (hdrEnabled)
		outputColor = GetHighDefinitionRangeColor(inputTex, textureCoord);
	else
		outputColor = texture(inputTex, textureCoord);
}