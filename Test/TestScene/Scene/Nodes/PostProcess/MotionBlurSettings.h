#ifndef MOTION_BLUR_SETTINGS_H
#define MOTION_BLUR_SETTINGS_H

namespace TestScene
{
	namespace Nodes
	{
		struct MotionBlurSettings
		{
			bool isEnabled = true;

			float motionScale = 1.0f;

			int maxMotionSamples = 64;
		};
	}
}

#endif