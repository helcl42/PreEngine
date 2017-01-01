#ifndef LENS_FLARE_SETTINGS_H
#define LENS_FLARE_SETTINGS_H

#include "LensFlareMode.h"

namespace TestScene
{
	namespace Nodes
	{
		struct LensFlareSettings
		{
			bool isEnabled = true;

			LensFlareMode mode = LensFlareMode::WITH_HEJL_AND_STARBURST;

			float scale = 0.4f;

			float bias = 0.1f;

			int countOfGhosts = 6;

			float ghostDisperal = 0.25f;

			float haloWidth = 0.01f;

			float distortionCoefficient = 4.7f; //2.0

			int blurRadius = 40;

			bool showLensSource = false;
		};
	}
}

#endif