#ifndef HDR_SETTINGS_H
#define HDR_SETTINGS_H

namespace TestScene
{
	namespace Nodes
	{
		struct HDRSettings
		{
			bool isEnabled = true;

			float exposure = 0.358f;

			float white = 0.928f;

			float averageLuminance = 1.0;
		};
	}
}

#endif